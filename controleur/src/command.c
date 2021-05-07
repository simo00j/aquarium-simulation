#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "command.h"
#include "utils.h"
#include "config.h"
#include "server.h"

extern server *controller;

void command__from_client(connection *c, aquarium *aq)
{
	char *tmp_buffer = malloc(sizeof(BUFFER_MAX_SIZE));
	strcpy(tmp_buffer, c->command_buffer);
	char *parsed_command[COMMAND__MAX_SIZE];
	util__parser(parsed_command, c->command_buffer, " ");
	int tokens_len = util__count_tokens(parsed_command);

	if (tokens_len == 2 && !strcmp(parsed_command[0], "ping"))
	{
		if (atoi(parsed_command[1]) == config__get_port())
		{
			sprintf(c->answer_buffer, "pong %d\n", config__get_port());
		}
		else
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "getFishes"))
	{
		//TODO: implemet the reponse to this request
		sprintf(c->answer_buffer, "list [PoissonRouge at 90x4,10x4,0] [PoissonClown at 20x80,12x6,0]\n");
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "hello"))
	{
		c->associated_view = aquarium__get_free_view(aq);
		if (c->associated_view)
		{
            c->associated_view->taken = 1;
			sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
		}
		else
		{
			sprintf(c->answer_buffer, "no greeting\n");
		}
	}
	else if (tokens_len == 4 && !strcmp(parsed_command[0], "hello") && !strcmp(parsed_command[1], "in") && !strcmp(parsed_command[2], "as"))
	{
		c->associated_view = aquarium__get_view(aq, parsed_command[3]);
		if (c->associated_view && c->associated_view->taken == 0)
		{
            c->associated_view->taken = 1;
			sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
		}
		else
		{
			c->associated_view = aquarium__get_free_view(aq);
			if (c->associated_view)
			{
                c->associated_view->taken = 1;
				sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
			}
			else
			{
				sprintf(c->answer_buffer, "no greeting\n");
			}
		}
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "status"))
	{
		fish *f;
		sprintf(c->answer_buffer, "\t->OK : Connecté au contrôleur, %d poissons trouvés\n", aquarium__count_fish_in_view(aq, c->associated_view));
		STAILQ_FOREACH(f, &(aq->fish_list), next)
		{
			if (frame__includes_snippet(c->associated_view->frame, f->frame))
			{
				sprintf(c->answer_buffer, "%s\tFish %s at %dx%d,%dx%d %s\n", c->answer_buffer, f->name, f->frame->x, f->frame->y, f->frame->width, f->frame->height, f->is_started ? "started" : "notStarted");
			}
		}
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "ls"))
	{
		pthread_t t;
		pthread_create(&t, NULL, connection__ls, (void *)c);
	}
	else if (tokens_len == 6 && !strcmp(parsed_command[0], "addFish"))
	{
		frame *frame = malloc(sizeof(frame));
		char name[FISH_NAME_MAX_SIZE];
		sscanf(tmp_buffer, "addFish %s at %dx%d, %dx%d, RandomWayPoint", name, &(frame->x), &(frame->y), &(frame->width), &(frame->height));
		fish *f = fish__create(name, frame);
		f->frame->x = c->associated_view->frame->x * (1 + f->frame->x) / 100;
		f->frame->y = c->associated_view->frame->y * (1 + f->frame->y) / 100;
		int err = aquarium__add_fish(aq, f);
		if (err == -1)
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
		else
		{
			sprintf(c->answer_buffer, "OK\n");
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "delFish"))
	{
		int err = aquarium__del_fish(aq, parsed_command[1]);
		if (err == -1)
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
		else
		{
			sprintf(c->answer_buffer, "OK\n");
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "startFish"))
	{
		fish *f = aquarium__get_fish(aq, parsed_command[1]);
		if (f)
		{
			f->is_started = 1;
			sprintf(c->answer_buffer, "OK\n");
		}
		else
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "log") && !strcmp(parsed_command[1], "out"))
	{
		c->status = DISCONNECTED;
		sprintf(c->answer_buffer, "bye\n");
	}
	else
	{
		sprintf(c->answer_buffer, "NOK\n");
	}
}

void *connection__ls(void *conn)
{
	connection *c = (connection *)conn;
	while (c->status == CONNECTED)
	{
		fish *f;
		sprintf(c->answer_buffer, "list");
		STAILQ_FOREACH(f, &(controller->aquarium->fish_list), next)
		{
			if (f->is_started && frame__includes_snippet(c->associated_view->frame, f->frame))
			{
				sprintf(c->answer_buffer, "%s [%s at %dx%d,%dx%d,%d]", c->answer_buffer, f->name, f->frame->x, f->frame->y, f->frame->width, f->frame->height, 5);
			}
		}
		sprintf(c->answer_buffer, "%s\n", c->answer_buffer);
		write(c->socket_fd, c->answer_buffer, strlen(c->answer_buffer));
		sleep(1);
	}
	pthread_exit(NULL);
}

void command__from_server(char *command_buffer, char *answer_buffer)
{
	char *parsed_command[COMMAND__MAX_SIZE];
	util__parser(parsed_command, command_buffer, " ");
	int tokens_len = util__count_tokens(parsed_command);

	//TODO: implemets the commands related to the controller. This must not be very complicated
	(void)tokens_len;
	(void)answer_buffer;
}

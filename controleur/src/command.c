#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "command.h"
#include "utils.h"
#include "config.h"
#include "server.h"
#include "debug.h"
#include "frame.h"

extern server *controller;

void command__from_client(connection *c, aquarium *aq)
{
	char *tmp_buffer = malloc(sizeof(char) * COMMAND__MAX_SIZE);
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
		if(c->associated_view == NULL) {
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
		else {
            sprintf(c->answer_buffer, "NOK\n");
		}
	}
	else if (tokens_len == 4 && !strcmp(parsed_command[0], "hello") && !strcmp(parsed_command[1], "in") && !strcmp(parsed_command[2], "as"))
	{
        if (c->associated_view == NULL) {
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
        else {
            sprintf(c->answer_buffer, "NOK\n");
        }
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "status"))
	{
		fish *f;
		sprintf(c->answer_buffer, "\t->OK : Connecté au contrôleur, %d poissons trouvés", aquarium__count_fish_in_view(aq, c->associated_view));
		STAILQ_FOREACH(f, &(aq->fish_list), next)
		{
			if (frame__includes_snippet(c->associated_view->frame, f->frame))
			{
			    frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
				sprintf(c->answer_buffer, "%s\n\tFish %s at %dx%d,%dx%d %s\n", c->answer_buffer, f->name, relative_frame->x, relative_frame->y, relative_frame->width, relative_frame->height, f->is_started ? "started" : "notStarted");
			}
		}
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "getFishesContinuously"))
	{
		pthread_t t;
		pthread_create(&t, NULL, connection__get_fish_continuously, (void *)c);
	}
	else if (tokens_len == 6 && !strcmp(parsed_command[0], "addFish"))
	{
		frame *f = malloc(sizeof(frame));
		char name[FISH_NAME_MAX_SIZE];
		sscanf(tmp_buffer, "addFish %s at %dx%d, %dx%d, RandomWayPoint", name, &(f->x), &(f->y), &(f->width), &(f->height));
        frame *absolute_frame = frame__get_absolute(f, c->associated_view->frame);
		fish *new_fish = fish__create(name, absolute_frame);
        DEBUG_OUT("adding fish %s with frame %s\n", name, frame__to_str(f));
        free(f);
		int err = aquarium__add_fish(aq, new_fish);
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

void *connection__get_fish_continuously(void *conn)
{
	connection *c = (connection *)conn;
    fish *f;
	while (c->status == CONNECTED && controller->status == CONNECTED)
	{
		sprintf(c->answer_buffer, "list ");
		STAILQ_FOREACH(f, &(controller->aquarium->fish_list), next)
		{
            DEBUG_OUT("connection__get_fish_continuously : viewer frame : %s\n", frame__to_str(c->associated_view->frame));
            DEBUG_OUT("connection__get_fish_continuously : fish frame : %s\n", frame__to_str(f->frame));
            DEBUG_OUT("connection__get_fish_continuously : testing inclusion\n");
			if (f->is_started && frame__includes_snippet(c->associated_view->frame, f->frame))
			{
                DEBUG_OUT("connection__get_fish_continuously : test succes\n");
			    frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
				sprintf(c->answer_buffer, "%s [%s at %dx%d,%dx%d,%d]", c->answer_buffer, f->name, relative_frame->x, relative_frame->y,relative_frame->width, relative_frame->height, 5);
				free(relative_frame);
			}
		}
		sprintf(c->answer_buffer, "%s\n", c->answer_buffer);
		write(c->socket_fd, c->answer_buffer, strlen(c->answer_buffer));
		sleep(5);
	}
	pthread_exit(NULL);
}

void command__from_server(char *command_buffer, char *answer_buffer, aquarium *aq)
{
	char *parsed_command[COMMAND__MAX_SIZE];
	util__parser(parsed_command, command_buffer, " ");
	int tokens_len = util__count_tokens(parsed_command);

	if (tokens_len == 2 && !strcmp(parsed_command[0], "load"))
	{	
		char * path = (char*) malloc(50);
		strcpy(path, "data/");
		strcat(path, parsed_command[1]);
		strcat(path, ".txt");
		FILE *f = fopen(path, "r");
		if(f != NULL)
		{
			aquarium__load(aq, f);
			sprintf(answer_buffer,"\t-> Aquarium loaded ! ( %d display view)", aquarium__count_views(aq));
			fclose(f);
		}
		else 
		{
			sprintf(answer_buffer,"\t->NOK");

		}
		free(path);
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "show"))
	{
		view * v;
		sprintf(answer_buffer, "%dx%d", aq->frame->width, aq->frame->height);
		STAILQ_FOREACH(v, &(aq->views_list), next)
		{
			sprintf(answer_buffer, "%s\n%s %dx%d+%d+%d", answer_buffer, v->name, v->frame->x, v->frame->y, v->frame->width, v->frame->height);
		}
	}
	else if (tokens_len == 4 && !strcmp(parsed_command[0], "add"))
	{
		frame *frame = frame__from_str(parsed_command[3]);
		view *v = view__create(parsed_command[2], frame);
		if(aquarium__add_view(aq, v) == -1)
		{
			sprintf(answer_buffer, "\t->NOK");
		}
		else
		{
			sprintf(answer_buffer, "\t-> view added");
		}
	}
	else if (tokens_len == 3 && !strcmp(parsed_command[0], "del"))
	{
		if(aquarium__del_view(aq, parsed_command[2])==-1)
		{
			sprintf(answer_buffer, "\t->NOK");
		}
		else
		{
			sprintf(answer_buffer,"\t-> view %s deleted", parsed_command[2]);
		}	
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "save"))
	{
		aquarium__save(aq, "tst/saved_aq.txt");
		sprintf(answer_buffer,"\t-> Aquarium saved ! ( %d display view)", aquarium__count_views(aq));
	}
	else
	{
		sprintf(answer_buffer,"\t->NOK");
	}
}

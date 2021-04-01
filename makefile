CFLAGS   = -Wall -Wextra 
THREAD_FLAGS = -pthread
CTL_PATH = Controleur/Src/
TEST_CTL_PATH = Controleur/Tst/
CC = gcc
RM = rm

BIN = server test_server

.PHONY: all
all: $(BIN)

server: launch_server.o server.o 
	${CC} -o server launch_server.o server.o ${THREAD_FLAGS}

launch_server.o: 
	${CC} -o launch_server.o -c ${CTL_PATH}launch_server.c ${CFLAGS}

server.o:
	${CC} -o server.o -c ${CTL_PATH}server.c ${CFLAGS}

test_server: fake_client.o test_server.o
	${CC} -o test_server fake_client.o test_server.o ${CFLAGS}

fake_client.o:
	${CC} -o fake_client.o -c ${TEST_CTL_PATH}fake_client.c ${CFLAGS}

test_server.o:
	${CC} -o test_server.o -c ${TEST_CTL_PATH}test_server.c ${CFLAGS}

launch_server: server
	./server 45321

launch_test_server: test_server
	./test_server localhost 45321

clean:
	rm *.o $(BIN)

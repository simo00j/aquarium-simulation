CFLAGS   = -Wall -Wextra 
THREAD_FLAGS = -pthread
CTL_PATH = Controleur/Src/
TEST_CTL_PATH = Controleur/Tst/

BIN = server test_server

.PHONY: all
all: $(BIN)

server: launch_server.o server.o message.o control.o
	gcc -o server launch_server.o server.o message.o control.o ${THREAD_FLAGS}

launch_server.o: 
	gcc -o launch_server.o -c ${CTL_PATH}launch_server.c ${CFLAGS}

message.o:
	gcc -o message.o -c ${CTL_PATH}message.c ${CFLAGS}

server.o:
	gcc -o server.o -c ${CTL_PATH}server.c ${CFLAGS}

control.o:
	gcc -o control.o -c ${CTL_PATH}control.c ${CFLAGS}


test_server: fake_client.o test_server.o
	gcc -o test_server fake_client.o test_server.o ${CFLAGS}

fake_client.o:
	gcc -o fake_client.o -c ${TEST_CTL_PATH}fake_client.c ${CFLAGS}

test_server.o:
	gcc -o test_server.o -c ${TEST_CTL_PATH}test_server.c ${CFLAGS}

launch_server: clean server
	./server 45321

launch_test_server: test_server
	./test_server localhost 45321

clean:
	rm -f *.o *.out $(BIN)

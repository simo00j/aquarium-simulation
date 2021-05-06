CFLAGS   = -Wall -Wextra 
THREAD_FLAGS = -pthread
SRC_PATH = src/
TEST_PATH = tst/
BUILD_PATH = build/

BIN = server test_server aqua_test 

.PHONY: all
all: $(BIN)

server: launch_server.o server.o message.o control_client.o control_server.o command.o config.o util.o fish.o aquarium.o
	gcc -o server ${BUILD_PATH}launch_server.o ${BUILD_PATH}server.o ${BUILD_PATH}message.o ${BUILD_PATH}control_client.o ${BUILD_PATH}control_server.o ${BUILD_PATH}command.o ${BUILD_PATH}config.o ${BUILD_PATH}util.o ${BUILD_PATH}fish.o ${BUILD_PATH}aquarium.o ${THREAD_FLAGS}

%.o: ${SRC_PATH}%.c build
	gcc -o ${BUILD_PATH}$@ -c $< ${CFLAGS}

build:
	mkdir ${BUILD_PATH}

test_server: fake_client.o test_server.o
	gcc -o test_server ${BUILD_PATH}fake_client.o ${BUILD_PATH}test_server.o ${CFLAGS}

aqua_test: aqua_test.o fish.o aquarium.o
	gcc -o aqua_test ${BUILD_PATH}aqua_test.o ${BUILD_PATH}fish.o ${BUILD_PATH}aquarium.o

%.o: ${TEST_PATH}%.c build
	gcc -o ${BUILD_PATH}$@ -c $< ${CFLAGS}



launch_server: clean server
	./server 

launch_test_server: test_server
	./test_server 

clean:
	rm -f *.o *.out $(BIN) ${BUILD_PATH}*

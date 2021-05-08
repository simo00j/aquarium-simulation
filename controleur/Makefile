CC = gcc
CFLAGS   = -Wall -Wextra
LIBS = -pthread
SRC_PATH = src/
TEST_PATH = tst/
BUILD_PATH = build/

BIN = server

.PHONY: all
all: $(BIN)

server: server.o frame.o connection.o view.o command.o config.o utils.o fish.o aquarium.o
	$(CC) -o server $(BUILD_PATH)server.o $(BUILD_PATH)connection.o $(BUILD_PATH)frame.o $(BUILD_PATH)command.o $(BUILD_PATH)view.o $(BUILD_PATH)config.o $(BUILD_PATH)utils.o $(BUILD_PATH)fish.o $(BUILD_PATH)aquarium.o $(LIBS)

%.o: $(SRC_PATH)%.c $(SRC_PATH)%.h build
	$(CC) -o $(BUILD_PATH)$@ -c $< $(CFLAGS)

build:
	mkdir $(BUILD_PATH)

test_server: fake_client.o test_server.o
	$(CC) -o test_server $(BUILD_PATH)fake_client.o $(BUILD_PATH)test_server.o $(CFLAGS)

%.o: $(TEST_PATH)%.c build
	$(CC) -o $(BUILD_PATH)$@ -c $< $(CFLAGS)

launch_server: clean server
	./server

launch_test_server: test_server
	./test_server

clean:
	$(RM) *.o *~ $(BIN) $(BUILD_PATH)*

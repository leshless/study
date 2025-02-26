CC=g++
CFLAGS=-c
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

all: main

test: tests
	./tests

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

main: main.o longnum.o | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/main.o $(BUILD_PATH)/longnum.o -o main

tests: test.o longnum.o | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/test.o $(BUILD_PATH)/longnum.o -o tests

longnum.o: $(SRC_PATH)/longnum.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/longnum.cpp -o $(BUILD_PATH)/longnum.o

test.o: $(SRC_PATH)/test.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/test.cpp -o $(BUILD_PATH)/test.o

main.o: $(SRC_PATH)/main.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/main.o

clean:
	rm -rf $(BUILD_PATH)/main
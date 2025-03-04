CC=g++
CFLAGS=-c
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

all: main

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

main: main.o expression.o | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/main.o $(BUILD_PATH)/expression.o -o main

expression.o: $(SRC_PATH)/expression.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/expression.cpp -o $(BUILD_PATH)/expression.o

main.o: $(SRC_PATH)/main.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/main.o

clean:
	rm -rf $(BUILD_PATH)/expression.o
	rm -rf $(BUILD_PATH)/main.o
	rm -rf main
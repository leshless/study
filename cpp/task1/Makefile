CC=g++
CFLAGS=-c
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

all: main
	./main

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

main: main.o longnum.o | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/main.o $(BUILD_PATH)/longnum.o -o main

longnum.o: $(SRC_PATH)/longnum.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/longnum.cpp -o $(BUILD_PATH)/longnum.o

main.o: $(SRC_PATH)/main.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/main.o

clean:
	rm -rf $(BUILD_PATH)/main
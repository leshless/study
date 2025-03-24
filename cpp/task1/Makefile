CC=g++
CFLAGS=-c -std=c++20
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

OBJECTS_WC = $(wildcard $(SRC_PATH)/longnum/*.cpp)
OBJECTS = $(patsubst $(SRC_PATH)/longnum/%.cpp, $(BUILD_PATH)/%.o, $(OBJECTS_WC))

all: main

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

main: main.o $(OBJECTS) | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/main.o $(OBJECTS) -o main

main.o: $(SRC_PATH)/main.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/main.o

pi: pi.o $(OBJECTS) | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/pi.o $(OBJECTS) -o pi
	./pi

pi.o: $(SRC_PATH)/pi.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/pi.cpp -o $(BUILD_PATH)/pi.o

test: test.o $(OBJECTS) | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/test.o $(OBJECTS) -o test
	./test

test.o: $(SRC_PATH)/test.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/test.cpp -o $(BUILD_PATH)/test.o


$(BUILD_PATH)/%.o: $(SRC_PATH)/longnum/%.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf main
	rm -rf test
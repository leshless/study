CC=g++
CFLAGS=-c -std=c++20
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

OBJECTS_WC = $(wildcard $(SRC_PATH)/sympp/*.cpp)
OBJECTS = $(patsubst $(SRC_PATH)/sympp/%.cpp, $(BUILD_PATH)/%.o, $(OBJECTS_WC))

all: main

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

main: main.o $(OBJECTS) | $(BUILD_PATH)
	$(info $(OBJECTS))
	$(CC) $(BUILD_PATH)/main.o $(OBJECTS) -o main
	./main

main.o: $(SRC_PATH)/main.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/main.o

$(BUILD_PATH)/%.o: $(SRC_PATH)/sympp/%.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_PATH)/expression.o
	rm -rf $(BUILD_PATH)/main.o
	rm -rf main
CC=g++
CFLAGS=-c -std=c++20
LDFLAGS=
BUILD_PATH=build
SRC_PATH=src

OBJECTS_WC = $(wildcard $(SRC_PATH)/sympp/*.cpp)
OBJECTS = $(patsubst $(SRC_PATH)/sympp/%.cpp, $(BUILD_PATH)/%.o, $(OBJECTS_WC))

all: differentiator

test: test

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

test: test.o $(OBJECTS) | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/test.o $(OBJECTS) -o test
	./test

differentiator: differentiator.o $(OBJECTS) | $(BUILD_PATH)
	$(CC) $(BUILD_PATH)/differentiator.o $(OBJECTS) -o differentiator

differentiator.o: $(SRC_PATH)/differentiator.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/differentiator.cpp -o $(BUILD_PATH)/differentiator.o

test.o: $(SRC_PATH)/test.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH)/test.cpp -o $(BUILD_PATH)/test.o

$(BUILD_PATH)/%.o: $(SRC_PATH)/sympp/%.cpp | $(BUILD_PATH)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf main
	rm -rf test
CC      = gcc
CXX     = g++
CFLAGS  = -O2 -Wall -Wextra -std=c11
CXXFLAGS= -O2 -Wall -Wextra -std=c++17

SRC_C   = src/main.c
SRC_CPP = src/xbrz_wrapper.cpp xBRZ_1.9/xbrz.cpp

OBJ_C   = $(SRC_C:%.c=build/obj/%.o)
OBJ_CPP = $(SRC_CPP:%.cpp=build/obj/%.o)
OBJ     = $(OBJ_C) $(OBJ_CPP)

TARGET = build/xbrz

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p build
	$(CXX) $(OBJ) -o $(TARGET) -lm

build/obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

run: all
	./$(TARGET)

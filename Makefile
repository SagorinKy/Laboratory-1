COMPILER = g++
COMPILER_FLAGS = -g -Wall -pthread -I. -Werror -Wpedantic

SRC_FILES = $(wildcard *.cpp)

HEADER_FILES = $(wildcard *.h)

OBJ_LIST = $(SRC_FILES:.cpp=.o)

all: runLab1

$(OBJ_LIST): %.o : %.cpp $(HEADER_FILES)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

runLab1: $(OBJ_LIST)
	$(COMPILER) $(COMPILER_FLAGS) -o runLab1 $(OBJ_LIST)

remove_objs:
	rm -f *.o

full_clean:
	rm -f *.o GaussianBlur.bmp Rotated90CounterClockwise.bmp Rotated90Clockwise.bmp runLab1

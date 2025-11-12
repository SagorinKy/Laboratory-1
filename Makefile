COMPILER = g++
COMPILER_FLAGS = -fopenmp -g -Wall -pthread -I. -I./bmp_process -I./tests -Werror -Wpedantic

SRC_FILES = bmp_process/ClassBMP.cpp  

OBJ_LIST = $(SRC_FILES:.cpp=.o)

all: runLab1 

# Компиляция исходников классов (без Lab1.cpp)
$(OBJ_LIST): %.o : %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@


# Сборка основной программы
runLab1: bmp_process/Lab1.o bmp_process/ClassBMP.o
	$(COMPILER) $(COMPILER_FLAGS) -o runLab1 bmp_process/Lab1.o bmp_process/ClassBMP.o



# Удаление объектных файлов
remove_objs:
	rm -f $(OBJ_LIST) $(TEST_OBJ_LIST) bmp_process/*.o

# Полная очистка
full_clean:
	rm -f $(OBJ_LIST)  runLab1 GaussianBlur.bmp Rotated90CounterClockwise.bmp Rotated90Clockwise.bmp

.PHONY: all remove_objs full_clean 

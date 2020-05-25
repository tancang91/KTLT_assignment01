#Specify entry point file
SRCS =	test_main.cpp \
		test_knight.cpp \
		knight.cpp

# Specify all dependencies
DEP_DIR = src

OBJ_DIR=obj
HEADER_DIR=include

#Scpecify executable file here
TARS = test

#Specify all compile options here
CC = g++
CFLAGS = -Wall -g -std=c++11
LIBS =

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o) )

.PHONY = all run clean

all: $(TARS)

$(TARS): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARS) 

vpath %.cpp $(DEP_DIR)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(CC) $(CFLAGS) -o target knight.cpp

clean:
	rm -f $(filter-out $(OBJ_DIR)/test_main.o, $(OBJS)) $(TARS) target

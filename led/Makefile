#Tool definitions
CC ?= gcc
CXX ?= g++

#Directories
SOURCE_DIR	:= src
INCLUDE_DIR := inc
BUILD_DIR	:= build
OBJ_DIR		:= build/obj
TEST_DIR 	:= test 
NAME		:= led

CSOURCES := $(wildcard $(SOURCE_DIR)/*.c)

#Search path for header files
CFLAGS += 

#Compiler flags
CFLAGS += -Wall -g

#Linker flags
LDFLAGS += 

COBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(CSOURCES))

.PHONY: all $(NAME) clean test test_clean

all: $(BUILD_DIR)/$(NAME)

#Build target
$(BUILD_DIR)/$(NAME): $(COBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

#Build object files in the obj directory
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

$(OBJ_DIR):
	mkdir -p $@

#Run tests
test:
	make -C $(TEST_DIR)

test_clean:
	make -C $(TEST_DIR) clean
	
clean:
	rm -rf $(BUILD_DIR)




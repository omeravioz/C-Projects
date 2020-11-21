#ds makefile

NAME = 
SHARED_P = ds
LIB_DIR_DEBUG = /home/omer/omeravioz/ds/lib/debug
LIB_DIR_RELEASE = /home/omer/omeravioz/ds/lib/release
INCLUDE_DIR = /home/omer/omeravioz/ds/include
TEST_DIR = /home/omer/omeravioz/ds/test
SRC_DIR = /home/omer/omeravioz/ds/src
OBJ_DIR = /home/omer/omeravioz/ds/obj
DS_DIR = /home/omer/omeravioz/ds

OBJ_DEBUG = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/debug/%.o,$(wildcard $(SRC_DIR)/*.c))
OBJ_RELEASE = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/release/%.o,$(wildcard $(SRC_DIR)/*.c))

CC = gcc 
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
CFLAGS += -I $(INCLUDE_DIR)
GD_FLAGS = $(CFLAGS) -g
GC_FLAGS = $(CFLAGS) -DNDEBUG -O3


#------------------------------------------------------------------------------#

test: $(NAME)_debug.out

all: $(LIB_DIR_DEBUG)/lib$(SHARED_P).so $(LIB_DIR_RELEASE)/lib$(SHARED_P).so

debug: $(LIB_DIR_DEBUG)/lib$(SHARED_P).so

release: $(LIB_DIR_RELEASE)/lib$(SHARED_P).so


$(NAME)_debug.out: $(LIB_DIR_DEBUG)/lib$(SHARED_P).so
	$(CC) $(GD_FLAGS) -L$(LIB_DIR_DEBUG) -Wl,-rpath=$(LIB_DIR_DEBUG) $(TEST_DIR)/$(NAME)_test.c lib/debug/lib$(SHARED_P).so -o $(NAME)_debug.out -lm


$(LIB_DIR_DEBUG)/lib$(SHARED_P).so: $(OBJ_DEBUG)
	$(CC) $(GD_FLAGS) -shared $^ -o $@


$(LIB_DIR_RELEASE)/lib$(SHARED_P).so: $(OBJ_RELEASE)
	$(CC) $(GC_FLAGS) -shared $^ -o $@


$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	$(CC) $(GD_FLAGS) -c $^ -fPIC -o $@
	

$(OBJ_DIR)/release/%.o: $(SRC_DIR)/%.c
	$(CC) $(GC_FLAGS) -c $^ -fPIC -o $@

clean:
	rm -f $(NAME)_debug $(NAME)_release $(TEST_DIR)/$(NAME).o $(OBJ_DIR)/debug/$(NAME).o $(OBJ_DIR)/release/$(NAME).o $(LIB_DIR)/$(NAME).h.gch


cleanall:
	rm -f *_debug *_release *.o $(TEST_DIR)/*.o $(OBJ_DIR)/debug/*.o $(OBJ_DIR)/release/*.o $(LIB_DIR_DEBUG)/*.so $(LIB_DIR_RELEASE)/*.so $(DS_DIR)/*.out


.PHONY: clean cleanall all test debug release

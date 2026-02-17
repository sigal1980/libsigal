# Сборка и установка библиотек от sigal1980
CC = gcc

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS = $(SOURCES:%.c=%.o)


CREATE_OBJECTS_FLAGS = -c -fPIC
CREATE_DYN_LIB_FLAGS = -shared
CREATE_STAT_LIB_FLAGS = -static
NAME_DYN_LIB = libsigal.so.
VERSION_LIB = 1.0
NAME_LINK = libsigal.so

HOME_PATH = ~/.local/share/sigal1980
SRC_PATH = $(HOME_PATH)/src
LIB_PATH = $(HOME_PATH)/lib
INC_PATH = $(HOME_PATH)/inc

$(NAME_DYN_LIB)$(VERSION_LIB) : $(OBJECTS)
	$(CC) $(CREATE_DYN_LIB_FLAGS) -o $(NAME_DYN_LIB)$(VERSION_LIB) $(OBJECTS)

$(OBJECTS) : %.o : %.c $(HEADERS)
	$(CC) $(CREATE_OBJECTS_FLAGS) $< -o $@

.PHONY : clean install

install :
	-mkdir -p $(LIB_PATH)
	-mkdir -p $(INC_PATH)
	-mkdir -p $(SRC_PATH)
	-rm $(LIB_PATH)/$(NAME_DYN_LIB)* $(LIB_PATH)/$(NAME_LINK)
	-cp $(NAME_DYN_LIB)$(VERSION_LIB) $(LIB_PATH)
	-ln $(LIB_PATH)/$(NAME_DYN_LIB)$(VERSION_LIB) $(LIB_PATH)/$(NAME_LINK)
	-cp $(HEADERS) $(INC_PATH)
	-cp $(SOURCES) $(SRC_PATH)

clean:
	-rm $(OBJECTS) $(NAME_DYN_LIB)$(VERSION_LIB)

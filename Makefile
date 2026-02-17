# Сборка и установка библиотек от sigal1980
#PREFIX = /usr/local
PREFIX = ~/.local/share/sigal1980
CC = gcc

DIRS = $(shell find . -not \( -path './.*' -o -path '.' \) \
                      -type d -name '*' -print)
SOURCES = $(shell find . -not \( -path './.*' -o -path '.' \) \
                         -type f -name '*.c' -print)

HEADERS = $(shell find . -not \( -path './.*' -o -path '.' \) \
                         -type f -name '*.h' -print)
OBJECTS = $(SOURCES:%.c=%.o)


CREATE_OBJECTS_FLAGS = -c -fPIC
CREATE_DYN_LIB_FLAGS = -shared
CREATE_STAT_LIB_FLAGS = -static
BASE_NAME = libsigal
VERSION_LIB = 1.0.0
LINK_LIB = $(BASE_NAME).so
NAME_LIB = $(BASE_NAME).so.$(VERSION_LIB)

SRC_PATH = $(PREFIX)/src
LIB_PATH = $(PREFIX)/lib
INC_PATH = $(PREFIX)/include


$(NAME_LIB) : $(OBJECTS)
	$(CC) $(CREATE_DYN_LIB_FLAGS) -o $(NAME_LIB) $(OBJECTS)

$(OBJECTS) : %.o : %.c $(HEADERS)
	$(CC) $(CREATE_OBJECTS_FLAGS) $< -o $@

.PHONY : clean install

install :
	-mkdir -p $(LIB_PATH)
	-mkdir -p $(INC_PATH)
	install $(NAME_LIB) $(LIB_PATH)
	install $(HEADERS) $(INC_PATH)
	-ln -s $(LIB_PATH)/$(NAME_LIB) $(LIB_PATH)/$(LINK_LIB)

clean:
	-rm $(OBJECTS) $(NAME_LIB)

#*******************************************************************************
# PROJECT: Hexagones
#
# AUTHOR: Yohann Martin
#
# DATE CREATED: 07/04/2019
#
# Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
#
# Licensed under the MIT License. See LICENSE file in the project root for full
# license information.
#*******************************************************************************

CC		= gcc
PKGCONFIG	= $(shell which pkg-config)
GTK_CFLAGS	= $(shell $(PKGCONFIG) --cflags gtk+-3.0)
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ $(GTK_CFLAGS)

LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

TARGET	= hexagones
RM		= rm -f

SRC		= \
		$(wildcard src/model/*.c) \
		$(wildcard src/ui/*.c) \
		$(wildcard src/*.c)

OBJ		= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS) -lm

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

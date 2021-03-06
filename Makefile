# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseguin <lseguin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 10:38:58 by lseguin           #+#    #+#              #
#    Updated: 2016/12/19 01:04:52 by lseguin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG_FLAGS:=
ifdef DEBUG
DEBUG_FLAGS:=-D DEBUG
endif

NAME=ftparser.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f
LDFLAGS=-L.
LDLIBS=-lft
SRC = ./src/debug.c \
./src/eof.c \
./src/create_context.c \
./src/list.c \
./src/map_to.c \
./src/create_match.c \
./src/pick.c \
./src/join_characters.c \
./src/zero_or_one.c \
./src/repeat.c \
./src/utils.c \
./src/delete_match.c \
./src/map.c \
./src/sequence_of.c \
./src/any_of.c \
./src/zero_or_more.c \
./src/one_or_more.c \
./src/parse.c \
./src/delete_context.c \
./src/character.c \
./src/characters_in_list.c \
./src/any_character.c \
./src/character_range.c \
./src/exact.c \
./src/not.c \
./src/integer.c \
./src/recursive.c
OBJ = $(SRC:.c=.o)
INC = ./inc/

$(NAME): $(OBJ)
		@rm -rf $(NAME)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
		$(CC) -I. -o $@ -c $? $(CFLAGS) $(DEBUG_FLAGS)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean clean
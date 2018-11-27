# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snassour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/07 11:40:19 by snassour          #+#    #+#              #
#    Updated: 2018/09/07 14:19:24 by snassour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
#-fsanitize=address
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC_NAME = add_anthill.c\
add_link.c\
add_room.c\
bonus.c\
check_all.c\
check_format_link.c\
check_format_room.c\
lemin_ants.c\
main.c\
map_init_destroy.c\
paths_find.c\
tools_lemin.c

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_PATH = ./includes/\
./libft/includes/\

LIB_PATH1 = ./libft/

LIB_PATH = $(LIB_PATH1)

LIB_LINKS = -lft

NAME = lem-in

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB = $(addprefix -L,$(LIB_PATH))
INC = $(addprefix -I,$(INC_PATH))

all: lib $(NAME)

$(NAME):$(OBJ) ./includes/lemin.h
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LIB_LINKS) $(INC) -o $(NAME)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c ./includes/lemin.h
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make clean -C $(LIB_PATH1)
	rm -rfv $(OBJ_PATH)

fclean: clean
	make fclean -C $(LIB_PATH1)
	rm -fv $(NAME)

re: fclean all

lib:
	make -C $(LIB_PATH1)

cleanlib:
	make clean -C $(LIB_PATH1)

fcleanlib:
	make fclean -C $(LIB_PATH1)

relib:
	make re -C $(LIB_PATH1)

reall: fcleanlib re

realmost:
	make fclean -C $(LIB_PATH1)
	make fclean
	make re

gitupdate:fclean fcleanlib
	git add $(SRC)

gitupload:gitupdate
	git push

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 16:43:31 by alagroy-          #+#    #+#              #
#    Updated: 2021/02/17 17:03:04 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = clang

SRCS_FILES = 

vpath %.c ./srcs/

INCLUDES_PATH = ./includes/

HEADERS += 

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJ_PATH = ./.obj/

OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRCS_FILES))

CFLAGS = -Wall -Werror -Wextra -g

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $@

$(NAME): $(OBJ) $(LIBFT)
	ar rcs $@ $^
	printf "\n\033[0;32m[libft_malloc] Linking [OK]\n"

$(OBJ): $(OBJ_PATH)%.o: %.c $(HEADER) Makefile
	printf "\033[0;32m[libft_malloc] Compilation [$<]                 \r\033[0m"
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) -Rf $(OBJ_PATH)
	make -C $(LIBFT_DIR) $@
	printf "\033[0;31m[libft_malloc] Clean [OK]\n"

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) $@
	printf "\033[0;31m[libft_malloc] Fclean [OK]\n"

re: fclean all

.PHONY: fclean clean all re
.SILENT:
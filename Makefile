# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 16:43:31 by alagroy-          #+#    #+#              #
#    Updated: 2021/02/17 22:46:30 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = clang

SRCS_FILES = malloc.c

SRCS_PATH = ./srcs/

INCLUDES_PATH = ./includes/ $(LIBFT_DIR)includes

HEADERS += libft_malloc.h

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJ_PATH = ./.objs/
OBJ_FILES = $(SRCS_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

CFLAGS = -Wall -Werror -Wextra -g
CFLAGS += $(addprefix -I , $(INCLUDES_PATH))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	ar rcs $@ $^
	printf "\n\033[0;32m[libft_malloc] Linking [OK]\n"
	ln -s $(NAME) libft_malloc.so

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@
	printf "\033[0;32m[libft_malloc] Compilation [$<]                 \r\033[0m"

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
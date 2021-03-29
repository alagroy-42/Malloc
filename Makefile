# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 16:43:31 by alagroy-          #+#    #+#              #
#    Updated: 2021/03/29 17:11:34 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBNAME = libft_malloc.so

CC = clang

SRCS_FILES = malloc.c malloc_tools.c zone_tools.c alloc_tools.c

SRCS_PATH = ./srcs/

INCLUDES_PATH = ./includes/ $(LIBFT_DIR)includes

HEADERS += libft_malloc.h

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJ_PATH = ./.objs/
OBJ_FILES = $(SRCS_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
CFLAGS += $(addprefix -I , $(INCLUDES_PATH))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_DIR) -fPIC -lft -shared $(SRCS) -o $@
	printf "\n\033[0;32m[libft_malloc] Linking [OK]\n"
	$(RM) $(LIBNAME)
	ln -s $(NAME) $(LIBNAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c -fPIC $< -o $@
	printf "\033[0;32m[libft_malloc] Compilation [$<]                 \r\033[0m"

clean:
	$(RM) -Rf $(OBJ_PATH)
	make -C $(LIBFT_DIR) $@
	printf "\033[0;31m[libft_malloc] Clean [OK]\n"

fclean: clean
	$(RM) $(LIBNAME)
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) $@
	printf "\033[0;31m[libft_malloc] Fclean [OK]\n"

test: $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) -o test_libft_malloc

re: fclean all

.PHONY: fclean clean all re
.SILENT:
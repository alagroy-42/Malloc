# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 16:43:31 by alagroy-          #+#    #+#              #
#    Updated: 2021/04/14 14:21:10 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBNAME = libft_malloc.so

CC = clang

SRCS_FILES = malloc.c utils.c zones.c alloc.c free.c realloc.c show_alloc_memory.c \
			checks.c
SRCS_PATH = ./srcs/

INCLUDES_PATH = ./includes/ $(LIBFT_DIR)includes

HEADERS += ./includes/libft_malloc.h

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJ_PATH = ./.objs/
OBJ_FILES = $(SRCS_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
CFLAGS += $(addprefix -I , $(INCLUDES_PATH))
CFLAGS_LMALLOC = -L . -lft_malloc

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJ) -L $(LIBFT_DIR) -lft
	printf "\n\033[0;32m[libft_malloc] Linking [OK]\n"
	$(RM) $(LIBNAME)
	ln -s $(NAME) $(LIBNAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS) Makefile
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
	$(CC) $(CFLAGS) -Wl,-rpath,$(PWD) main.c -o test_libft_malloc -L $(LIBFT_DIR) -lft -L. -lft_malloc

re: fclean all

.PHONY: fclean clean all re
.SILENT:
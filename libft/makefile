# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 16:20:51 by amdemuyn          #+#    #+#              #
#    Updated: 2025/07/09 21:08:16 by amdemuyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#If the library file already exists, it adds or replace object file
#The 'c' flag tells ar to create the library if it doesn't already exist. 
#The 'r' flag tells it to replace older object files with the new object files.

#ranlib: command used to create or update the index
#Bc after an archive is created, or modified, there is a need to index it.

#.PHONY: allows to declare phony targets, so that make will not check them as 
#actual file name.

NAME = libft.a

SRC = ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_calloc.c \
	  ft_strcmp.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c
	 
SRC_B = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

%.o: %.c
	@$(CC) $(CFLAGS) -c $<
all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

bonus: $(OBJ_B)
	@ar rc $(NAME) $(OBJ_B)

clean:
	@rm -rf $(OBJ) $(OBJ_B)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: $(NAME), all, clean, fclean, re

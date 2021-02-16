# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 14:15:15 by jmogo             #+#    #+#              #
#    Updated: 2021/02/16 16:36:52 by jmogo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

LIB		= ar rc $(NAME)

DIR		= ./srcs/

OBJ_DIR	= ./objects/

HEADER	= ./includes/

HFILE	= libft.h

FLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

SRCS	= ft_atoi.c\
		  ft_bzero.c\
		  ft_calloc.c\
		  ft_isalnum.c\
		  ft_isalpha.c\
		  ft_isascii.c\
		  ft_isdigit.c\
		  ft_isprint.c\
		  ft_isspace.c\
		  ft_itoa.c\
		  ft_lstnew.c\
		  ft_lstadd_front.c\
		  ft_lstsize.c\
		  ft_lstlast.c\
		  ft_lstadd_back.c\
		  ft_lstdelone.c\
		  ft_lstclear.c\
		  ft_lstiter.c\
		  ft_lstmap.c\
		  ft_memccpy.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_memcpy.c\
		  ft_memmove.c\
		  ft_memset.c\
		  ft_putchar_fd.c\
		  ft_putendl_fd.c\
		  ft_putnbr_fd.c\
		  ft_putstr_fd.c\
		  ft_putstrn_fd.c\
		  ft_realloc.c\
		  ft_split.c\
		  ft_strchr.c\
		  ft_strcmp.c\
		  ft_strdup.c\
		  ft_strjoin.c\
		  ft_strlcat.c\
		  ft_strlcpy.c\
		  ft_strlen.c\
		  ft_strmapi.c\
		  ft_strncmp.c\
		  ft_strnstr.c\
		  ft_strrchr.c\
		  ft_strtrim.c\
		  ft_substr.c\
		  ft_tolower.c\
		  ft_toupper.c

vpath %.c	$(DIR)
vpath %.o	$(OBJ_DIR)
vpath %.h	$(HEADER)

OBJS		= $(SRCS:.c=.o)

%.o:		%.c $(HFILE) | $(OBJ_DIR)
			$(CC) $(FLAGS) -c -I$(HEADER) $< -o $(OBJ_DIR)$@

all:		$(NAME) | $(OBJ_DIR)

$(NAME):	$(NAME)($(OBJS))

$(OBJ_DIR):
			mkdir -p $@

$(NAME)(%.o):	%.o
			$(LIB) $(OBJ_DIR)$%

$(OBJS):	%.o:	%.c	$(HFILE) | $(OBJ_DIR)
			$(CC) $(FLAGS) -I$(HEADER) -c $< -o $(OBJ_DIR)$@

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

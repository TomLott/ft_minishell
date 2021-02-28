# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmogo <jmogo@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 14:15:15 by jmogo             #+#    #+#              #
#    Updated: 2021/02/28 16:46:46 by jmogo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

DIR		= ./srcs/

FLAGS	= -Wall -Wextra -Werror

HEADER	= ./includes/

HFILE	= minishell.h

LIB		= ./libft/libft.a

NAME	= minishell

OBJ_DIR	= ./objects/

SRCS	=	clean_line.c \
			convert_dol_question.c \
			do_error.c \
			do_malloc.c \
			do_pipe.c \
			do_pipe2.c \
			env_operations.c \
			env_operations2.c \
			free_arr.c \
			ft_fd.c \
			ft_minishell.c \
			ft_parse_dollar.c \
			ft_utils.c \
			ft_utils2.c \
			ft_utils3.c \
			get_next_line.c \
			get_path.c \
			getting_cmd.c \
			getting_cmd2.c \
			init_obj.c \
			manage_cmds.c \
			operations.c \
			operations2.c \
			operations3.c \
			pipi.c \
			process_tilda.c \
			str_swap.c \
			swap_env.c

vpath %.c	$(DIR)
vpath %.o	$(OBJ_DIR)
vpath %.h	$(HEADER)

OBJS		= $(SRCS:.c=.o)

OBJS_W_DIR	= $(addprefix $(OBJ_DIR), $(OBJS))

%.o:		%.c $(HFILE) | $(OBJ_DIR)
			$(CC) $(FLAGS) -c -I$(HEADER) $< -o $(OBJ_DIR)$@

all:		$(NAME) | $(OBJ_DIR)

$(NAME):	$(LIB) | $(OBJS)
			$(CC) $(FLAGS) $(LIB) $(OBJS_W_DIR) -I$(HEADER) -o $@

$(LIB):
			make -C ./libft/

$(OBJ_DIR):
			mkdir -p $@

$(NAME)(%.o):	%.o
			$(CC) -I$(HEADER) $(OBJ_DIR)$%

$(OBJS):	%.o:	%.c	$(HFILE) | $(OBJ_DIR)
			$(CC) $(FLAGS) -I$(HEADER) -c $< -o $(OBJ_DIR)$@

clean:
			rm -rf $(OBJ_DIR)
			rm -rf ./libft/objects/
			rm -f $(LIB)

fclean:		clean
			rm -f $(NAME)
			rm -f $(LIB)

re:			fclean all

.PHONY:		all clean fclean re

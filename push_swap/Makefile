# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/06 17:48:47 by seungsle          #+#    #+#              #
#    Updated: 2022/03/20 19:27:09 by seungsle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc -g
CFLAG	= -Werror -Wall -Wextra

PS_NAME = push_swap
CHR_NAME = checker
NAME	= $(PS_NAME) $(CHR_NAME)

PS_SRCS	=	srcs/action/action_exe.c				\
			srcs/action/action_p.c					\
			srcs/action/action_r.c					\
			srcs/action/action_rr.c					\
			srcs/action/action_s.c					\
			srcs/action/action_util.c				\
			srcs/algorithm/simple_sort.c			\
			srcs/algorithm/sorting_algorithm_util.c	\
			srcs/algorithm/sorting_algorithm.c		\
			srcs/algorithm/insertion_sort_util.c	\
			srcs/algorithm/insertion_sort.c			\
			srcs/parsing/create.c					\
			srcs/parsing/exception.c				\
			srcs/parsing/free.c						\
			srcs/parsing/node.c						\
			srcs/parsing/parsing_util.c				\
			srcs/parsing/parsing.c					\
			srcs/push_swap.c

CHR_SRCS	=	srcs/checker/checker.c					\
				srcs/checker/get_next_line.c			\
				srcs/checker/get_next_line_utils.c		\
				srcs/action/action_exe.c				\
				srcs/action/action_p.c					\
				srcs/action/action_r.c					\
				srcs/action/action_rr.c					\
				srcs/action/action_s.c					\
				srcs/action/action_util.c				\
				srcs/parsing/create.c					\
				srcs/parsing/exception.c				\
				srcs/parsing/free.c						\
				srcs/parsing/node.c						\
				srcs/parsing/parsing_util.c				\
				srcs/parsing/parsing.c


PS_OBJS		=	${PS_SRCS:.c=.o}
CHR_OBJS	=	${CHR_SRCS:.c=.o}
INCLUDE	= -I./includes/

all : $(NAME)

$(PS_NAME) : $(PS_OBJS)
	$(CC) $(CFLAG) $(PS_OBJS) $(INCLUDE) -o $(PS_NAME)
	
$(CHR_NAME) : $(CHR_OBJS)
	$(CC) $(CFLAG) $(CHR_OBJS) $(INCLUDE) -o $(CHR_NAME)

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(PS_OBJS) $(CHR_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
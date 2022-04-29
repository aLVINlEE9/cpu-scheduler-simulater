NAME	= cpu-scheduler
CC		= gcc -g
CFLAG	= -Werror -Wall -Wextra
SRCS 	=	srcs/main.c				\
			srcs/error.c			\
			srcs/init_util.c		\
			srcs/init.c				\
			srcs/algorithm/FCFS.c	\
			srcs/algorithm/HRN.c	\
			srcs/algorithm/MFQ.c	\
			srcs/algorithm/PS.c		\
			srcs/algorithm/RR.c		\
			srcs/algorithm/SJF.c	\
			srcs/algorithm/SRTF.c

OBJS 	= ${SRCS:.c=.o}
INCLUDE	= -I./includes/

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) $(INCLUDE) -o $(NAME)

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
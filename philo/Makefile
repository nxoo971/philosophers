SRCS	=	main.c		init.c		parser.c		ft_atoi.c		time.c \
			free.c		routine.c	actions.c		watchers.c		print.c

NAME	=	philo

INC		=	-I ./

FLAGS	=	-g3 -Wall -Werror -Wextra

OBJS	=	${SRCS:.c=.o}

all : ${NAME}

%.o:%.c
		gcc ${FLAGS} -c $< -o $@

${NAME} : ${OBJS}
		gcc ${FLAGS} ${INC} ${OBJS} -o ${NAME}

clean :
		rm -rf ${OBJS}

fclean : clean
		rm -rf ${NAME}

re : fclean all

.PHONY : all bonus clean fclean re
NAME	= pipex

CC		= cc

CFLAGS	= -Wall -Werror -Wextra -g3

SRCS	= pipex.c parsing.c forks.c ./lst_functions/ft_lst.c \

LIB_DIR	= libft

LIBFT	= ${LIB_DIR}/libft.a

INCLUDES	= -I . -I ./libft -I ./lst_functions

OBJS	= ${SRCS:.c=.o}

all: ${LIBFT} ${NAME}

.o: .c
	${CC} ${CFLAGS} -o $@ -c $< ${INCLUDES}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT} :
	make -C ${LIB_DIR}

clean:
	rm -f ${OBJS}
	make clean -C ${LIB_DIR}

fclean: clean
	rm -f ${NAME}
	make fclean -C ${LIB_DIR}

re: fclean all

.PHONY: all clean fclean re
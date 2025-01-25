NAME	= push_swap

CC		= cc

CFLAGS	= -Wall -Werror -Wextra -g3

SRCS	= push_swap.c push_swap_utils.c parsing.c tools.c sorting.c sorting_2.c

LIB_DIR	= libft

LIBFT	= ${LIB_DIR}/libft.a

INCLUDES	= -I . -I ./libft

OBJS	= ${SRCS:.c=.o}

all: ${LIBFT} ${NAME}

.o: .c
	${CC} ${CFLAGS} -o $@ -c $< ${INCLUDES}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT} :
	make bonus -C ${LIB_DIR}

clean:
	rm -f ${OBJS}
	make clean -C ${LIB_DIR}

fclean: clean
	rm -f ${NAME}
	make fclean -C ${LIB_DIR}

re: fclean all

.PHONY: all clean fclean re
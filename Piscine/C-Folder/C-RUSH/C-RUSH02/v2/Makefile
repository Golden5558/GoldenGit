SRCS			= ft_putchar.c ft_putstr.c ft_strlen.c ft_strstr.c \
					parse_dict.c verif_arg.c decompose_nb.c \
					show_nb.c decompose_nb2.c main.c
OBJS            = $(SRCS:.c=.o)

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I .

NAME			= rush-02

all:            $(OBJS) $(NAME)

$(NAME):        $(OBJS)
				$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
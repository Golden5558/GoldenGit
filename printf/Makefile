NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3# -fsanitize=address

HEADER = libftprintf.h

SRC = ft_printf.c ft_print_str.c ft_print_decimal.c ft_print_hexa.c ft_print_unsigned_decimal.c \

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
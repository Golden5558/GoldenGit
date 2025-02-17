NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

HEADER = libft.h

SRC = ft_atoi.c ft_itoa.c ft_calloc.c ft_split.c ft_substr.c ft_strdup.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memmove.c ft_memset.c ft_memcpy.c ft_strchr.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strnstr.c ft_strrchr.c \
	ft_strncmp.c  ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
	ft_tolower.c ft_toupper.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putnbr_base.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_printf.c ft_printf_utils.c ft_fprintf.c ft_fprintf_utils.c \

SRC2 = ft_lst_main.c ft_lst_secondary.c \

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC) $(SRC2)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(OBJ2)

all: $(NAME)

bonus: $(OBJ) $(OBJ2)
	ar rcs $(NAME) $(OBJ) $(OBJ2)

clean:
	rm -f $(OBJ) $(OBJ2)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

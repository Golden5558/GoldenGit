NAME	= so_long

CFLAGS	= -Wextra -Wall -Werror

CC		= cc

LIBMLX	= ./lib/MLX42

HEADERS	= -I ./include -I $(LIBMLX)/include -I ./gnl

LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	= main.c rendering_map.c rendering_entity.c \
		./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
		./parsing/check_path.c ./parsing/exits_and_utils.c \
		./parsing/parsing.c

OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.o: .c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re libmlx
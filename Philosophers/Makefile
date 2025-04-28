# **************************************************************************** #
#                                 VARIABLES                                  #
# **************************************************************************** #

# Compilation

NAME		:= philo
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -pthread -g3

# Directory

INCLUDE_DIR	:= . ./includes
OBJ_DIR		:= obj
SRC_DIR		:= src

# Sources

SRCS		:= philosophers.c src/cleanup.c src/parsing.c src/tools.c \
			src/thread_process.c src/thread_utils.c

# Objects and Dependencies

OBJS		:= $(patsubst %.c, ${OBJ_DIR}/%.o, $(notdir ${SRCS}))
DEPS		:= ${OBJS:.o=.d}

# **************************************************************************** #
#                                 COLORS                                      #
# **************************************************************************** #

RESET       := \033[0m
GREEN       := \033[32m
YELLOW      := \033[33m
CYAN        := \033[36m

# **************************************************************************** #
#                                 RULES                                       #
# **************************************************************************** #

$(NAME): $(OBJS)
	@echo "$(CYAN)[🔨] Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[✅] Build complete!$(RESET)"

${OBJ_DIR}:
	@mkdir -p $(OBJ_DIR)

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
	@echo "$(YELLOW)[🔄] Compiling: $< $(RESET)"
	@${CC} ${CFLAGS} $(foreach dir, ${INCLUDE_DIR}, -I$(dir)) -MMD -c $< -o $@

-include $(DEPS)

vpath %.c . ${SRC_DIR} ${LST_DIR}

all: ${NAME}

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -f ${NAME}

re: fclean all

norm:
	norminette --use-gitignore

vg: ${NAME}
	@echo "$(CYAN)[🔍] Starting Valgrind memory analysis...$(RESET)"
	@valgrind -s --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --gen-suppressions=all --track-fds=yes ./${NAME}

fs: CFLAGS += -fsanitize=thread
fs: clean ${NAME}
	@echo "$(GREEN)[✅] Build with Address Sanitizer complete!$(RESET)"

.PHONY: all clean fclean re norm vg fs  
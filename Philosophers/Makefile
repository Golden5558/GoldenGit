# **************************************************************************** #
#                                 VARIABLES                                  #
# **************************************************************************** #

# Compilation
NAME		:= philo
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g3 #-fsanitize=thread

# Directory

INCLUDE_DIR	:= . ./includes
LST_DIR		:= lst_functions
OBJ_DIR		:= obj
SRC_DIR		:= src

# Sources

SRCS		:= ${LST_DIR}/ft_lst.c ${LST_DIR}/ft_utils.c philosophers.c parsing.c

# Objects and Dependencies

OBJS		:= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
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

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	@echo "$(YELLOW)[🔄] Compiling: $< $(RESET)"
	@${CC} ${CFLAGS} $(foreach dir, ${INCLUDE_DIR}, -I$(dir)) -MMD -c $< -o $@

${OBJ_DIR}/%.o: ${LST_DIR}/%.c | ${OBJ_DIR}
	@echo "$(YELLOW)[🔄] Compiling: $< $(RESET)"
	@${CC} ${CFLAGS} $(foreach dir, ${INCLUDE_DIR}, -I$(dir)) -MMD -c $< -o $@

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
	@echo "$(YELLOW)[🔄] Compiling: $< $(RESET)"
	@${CC} ${CFLAGS} $(foreach dir, ${INCLUDE_DIR}, -I$(dir)) -MMD -c $< -o $@

-include $(DEPS)

all: ${NAME}

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -f ${NAME}

re: fclean all

norm:
	norminette --use-gitignore

.PHONY: all clean fclean re norm
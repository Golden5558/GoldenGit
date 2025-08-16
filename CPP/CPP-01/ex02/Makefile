# **************************************************************************** #
#                                 VARIABLES                                  #
# **************************************************************************** #

# Compilation

NAME		:= hi_this_is_brain
CC			:= c++
FLAGS		:= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

# Directory

OBJ_DIR		:= obj

# Sources

SRCS		:= main.cpp

# Objects and Dependencies

OBJS		:= $(patsubst %.cpp,${OBJ_DIR}/%.o,${SRCS})
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
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)[✅] Build complete!$(RESET)"

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}	

${OBJ_DIR}/%.o: %.cpp | ${OBJ_DIR}
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[🔄] Compiling: $< $(RESET)"
	@${CC} ${FLAGS} $(foreach dir, ${INCLUDE_DIR}, -I$(dir)) -MMD -c $< -o $@

-include $(DEPS)

vpath %.cpp .

all: $(NAME)

clean:
	@rm -rf ${OBJ_DIR}
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

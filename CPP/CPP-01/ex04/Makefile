# **************************************************************************** #
#                                 VARIABLES                                  #
# **************************************************************************** #

# Compilation

NAME		:= sedis4losers
CC			:= c++
FLAGS		:= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

# Directory

INCLUDE_DIR	:= includes
OBJ_DIR		:= obj
SRC_DIR		:= src

# Sources

SRCS		:= Replace.cpp
ALL_SRCS	:= main.cpp $(addprefix src/, ${SRCS})

# Objects and Dependencies

OBJS		:= $(patsubst %.cpp,${OBJ_DIR}/%.o,${ALL_SRCS})
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

vpath %.cpp . ${SRC_DIR}

all: $(NAME)

clean:
	@rm -rf ${OBJ_DIR}
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

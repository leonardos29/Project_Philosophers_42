NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

SRCS		= $(SRC_DIR)/philo.c \
			  $(SRC_DIR)/parsing/parsing.c \
			  $(SRC_DIR)/parsing/parsing_utils.c \
			  $(SRC_DIR)/simulation/create.c \
			  $(SRC_DIR)/simulation/init.c \
			  $(SRC_DIR)/routine/routine.c \
			  $(SRC_DIR)/routine/routine_utils.c \
			  $(SRC_DIR)/routine/verify_dead.c \
			  $(SRC_DIR)/clear_and_time/clear.c \
			  $(SRC_DIR)/clear_and_time/print_and_time.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(YELLOW)Compiling: $<$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re

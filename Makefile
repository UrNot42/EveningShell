NAME 				=	minishell

CC 					=	cc
CFLAGS 				=	-g -pthread -Wall -Wextra -Werror
INCLUDES_DIR 		=	include/
SRC_DIR 			=	src/
OBJ_DIR 			=	.obj/
LIB_DIR 			=	lib/
INCLUDES_H			=	-I./$(INCLUDES_DIR) -I./$(LIB_DIR)
DEPS 				=	$(INCLUDES_DIR)minishell.h $(INCLUDES_DIR) Makefile


SRC_BUILTINS		=	$(addprefix src_builtins/, \
						builtins_cd.c \
						builtins_echo.c \
						\
						)

# COMMENT
MINISHELL_SRC		=  $(addprefix $(SRC_DIR), \
					utils.c \
					minishell.c \
					\
					$(SRC_BUILTINS) \
					)

OBJS 			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(MINISHELL_SRC))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_H) -c -o $@ $<

$(NAME): $(OBJS) $(DEPS)
	@echo "\e[36mMaking $(NAME)...\e[0m"
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(OBJS) -o $(NAME)
	@echo "\e[32mDone !\e[0m"

bonus: all

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\e[31mObject files removed.\e[0m"

fclean:	clean
	@rm -f $(NAME)
	@echo "\e[31m$(NAME) removed.\e[0m"

re:		fclean all

clear:
	clear

.PHONY = all bonus clean fclean re

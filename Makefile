NAME 				=	minishell

CC 					=	cc
CFLAGS 				=	-Wall -Wextra -Werror $(DBFLAGS)
DBFLAGS				=	-g -g3
LIBFLAGS			=	-lreadline
INCLUDES_DIR 		=	include/
SRC_DIR 			=	src/
OBJ_DIR 			=	.obj/
LIB_DIR 			=	lib/
INCLUDES_H			=	-I./$(INCLUDES_DIR) -I./$(LIB_DIR)
DEPS 				=	$(INCLUDES_DIR)minishell.h $(INCLUDES_DIR) Makefile $(LIB_DIR)libft/Makefile
RM					=	rm -f

# COMMENT ?
SRC_MINISHPLIT		=	$(addprefix minishplit/, \
						dollars.c \
						minishplit.c \
						check_error.c \
						double_quotes.c \
						single_quotes.c \
						metacharacters.c \
						check_syntax_error.c \
						check_quoting_error.c \
						\
						)

# COMMENT ?
SRC_TOKENIZATION		=	$(addprefix tokenization/, \
						command.c \
						redir_type.c \
						tokenization.c \
						token_creation.c \
						\
						)

# COMMENT ?
SRC_EXPANSION		=	$(addprefix expansion/, \
						expansion.c \
						check_for_dollar.c \
						expand_one_token.c \
						\
						)

# COMMENT ?
SRC_PARSING			=	$(addprefix parsing/, \
						$(SRC_MINISHPLIT) \
						$(SRC_TOKENIZATION) \
						$(SRC_EXPANSION) \
						\
						)

SRC_ENVIRONMENT		=	$(addprefix environment/, \
						building_env.c \
						\
						)

# COMMENT ?
SRC_BUILTINS		=	$(addprefix builtins/, \
						cd.c \
						pwd.c \
						echo.c \
						exit.c \
						builtins.c \
						\
						)

# COMMENT ?
SRC_EXECUTION		=	$(addprefix execution/, \
						$(SRC_BUILTINS) \
						$(SRC_ENVIRONMENT) \
						)

# COMMENT ?
MINISHELL_SRC		=  $(addprefix $(SRC_DIR), \
						minishell.c \
						\
						$(SRC_PARSING) \
						$(SRC_EXECUTION) \
						\
						debug.c \
						)
#debug.c => temporary

OBJS 			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(MINISHELL_SRC))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_H) -c -o $@ $<

$(NAME): $(OBJS) $(DEPS)
	@echo "\e[36mMaking $(NAME)...\e[0m"
	@make --no-print-directory -C lib/libft/
	@mv lib/libft/libft.a .obj/
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(OBJS) $(LIBFLAGS) -o $(NAME) .obj/libft.a
	@echo "\e[32mDone !\e[0m"

bonus: all

clean:
	@rm -rf $(OBJ_DIR)
	@make --no-print-directory -C lib/libft/ clean
	@echo "\e[31mObject files removed.\e[0m"

fclean:	clean
	@$(RM) $(NAME)
	@echo "\e[31m$(NAME) removed.\e[0m"

re:		fclean all

clear:
	clear

.PHONY = all bonus clean fclean re

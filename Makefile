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

# FIRST STEP OF THE SHELL OPERATIONS BREAKING THE INPUT IN WORDS AND OPERATORS
SRC_LEXER			=	$(addprefix lexer/, \
						dollars.c \
						minishplit.c \
						check_error.c \
						double_quotes.c \
						single_quotes.c \
						metacharacters.c \
						check_syntax_error.c \
						check_quotation_error.c \
						\
						)

# SECOND TO THIRD STEP OF THE SHELL OPERATIONS CREATES COMPOUNDS WITH SPECIFICS
SRC_PARSER			=	$(addprefix parser/, \
						command.c \
						parsing.c \
						redir_type.c \
						free_compound.c \
						compound_creation.c \
						\
						)

SRC_EXPAND_CHAR		= $(addprefix char_management/, \
						char2d_management.c \
						string_add_one_char.c \
						)

SRC_EXPAND_NEW_CONT	= $(addprefix create_new_content/, \
						create_new_content.c \
						add_one_char_in_new_content.c \
						)

SRC_EXPAND_DOLLAR	= $(addprefix expand_dollar/, \
						ft_itoa_no_malloc.c \
						expand_dollar.c \
						environment_variables.c \
						expand_one_environment_variable.c \
						add_one_environment_variable_character.c \
						)

# FOURTH STEP OF THE SHELL OPERATIONS REPLACING THE VARIABLES WITH THEIR VALUE
SRC_EXPAND			=	$(addprefix expand/, \
						expand.c \
						is_expand_dollar.c \
						quotes_management.c \
						expand_one_content.c \
						\
						$(SRC_EXPAND_CHAR) \
						$(SRC_EXPAND_DOLLAR) \
						$(SRC_EXPAND_NEW_CONT) \
						)

SRC_HEREDOC			=	$(addprefix heredocs/, \
						heredoc.c \
						open_heredoc_file.c \
						\
						)

# ENVIRONMENT FUNCTIONS - CREATING AN ENVIROMENT AND FUNCTIONS TO WORK WITH IT
SRC_ENVIRONMENT		=	$(addprefix environment/, \
						default_env.c \
						building_env.c \
						\
						)

# BUILT-INS OF THE SHELL THAT SHALL BE USED DIRECTLY INSTEAD OF THE BINARY FILES
SRC_BUILTINS		=	$(addprefix builtins/, \
						cd.c \
						env.c \
						pwd.c \
						echo.c \
						exit.c  \
						unset.c \
						export.c \
						builtins.c \
						\
						)

SRC_TOOL_LAYER		=	$(addprefix overlay/, \
						pids.c \
						pipes.c \
						signal.c \
						exec_struct.c \
						init_command.c \
						file_handling.c \
						\
						)

# PROCESSING COMMANDS AND DIRECTING INPUTS AND OUTPUTS
SRC_EXECUTION		=	$(addprefix execution/, \
						cmd_build.c \
						execution.c \
						child_process.c \
						$(SRC_BUILTINS) \
						$(SRC_ENVIRONMENT) \
						$(SRC_HEREDOC) \
						$(SRC_TOOL_LAYER) \
						\
						)

# MAIN MANAGER FILES
MINISHELL_SRC		=  $(addprefix $(SRC_DIR), \
						prompt.c \
						running.c \
						minishell.c \
						error_display.c \
						\
						$(SRC_LEXER) \
						$(SRC_EXPAND) \
						$(SRC_PARSER) \
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

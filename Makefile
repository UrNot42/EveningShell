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

# SECOND TO THIRD STEP OF THE SHELL OPERATIONS CREATES TOKENS WITH SPECIFICS
SRC_TOKENIZATION		=	$(addprefix tokenization/, \
						command.c \
						redir_type.c \
						tokenization.c \
						token_creation.c \
						free_token.c \
						\
						)

# FOURTH STEP  OF THE SHELL OPERATIONS REPLACING THE VARIABLES WITH THEIR VALUE
SRC_EXPANSION		=	$(addprefix expansion/, \
						expansion.c \
						check_for_dollar.c \
						expand_one_token.c \
						\
						)

# GENERAL WRAPPING OF THE PARSING PROCESS - WORKS ON THE INPUT DIRECTLY
SRC_PARSING			=	$(addprefix parsing/, \
						$(SRC_MINISHPLIT) \
						$(SRC_TOKENIZATION) \
						$(SRC_EXPANSION) \
						\
						)

SRC_HEREDOC			=	$(addprefix heredocs/, \
						heredoc.c \
						open_heredoc_file.c \
						keyword_management.c \
						\
						)

# ENVIRONMENT FUNCTIONS - CREATING AN ENVIROMENT AND FUNCTIONS TO WORK WITH IT
SRC_ENVIRONMENT		=	$(addprefix environment/, \
						building_env.c \
						default_env.c \
						\
						)

# BUILT-INS OF THE SHELL THAT SHALL BE USED DIRECTLY INSTEAD OF THE BINARY FILES
SRC_BUILTINS		=	$(addprefix builtins/, \
						cd.c \
						pwd.c \
						echo.c \
						exit.c \
						builtins.c \
						\
						)

# PROCESSING COMMANDS AND DIRECTING INPUTS AND OUTPUTS
SRC_EXECUTION		=	$(addprefix execution/, \
						pids.c \
						pipes.c \
								 \
								  \
						exec_cmd.c \
						cmd_build.c \
						execution.c \
						exec_debug.c \
						init_struct.c \
						init_command.c \
						file_handling.c \
						$(SRC_BUILTINS) \
						$(SRC_ENVIRONMENT) \
						$(SRC_HEREDOC) \
						\
						)

# MAIN MANAGER FILES
MINISHELL_SRC		=  $(addprefix $(SRC_DIR), \
						minishell.c \
						prompt.c \
						running.c \
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

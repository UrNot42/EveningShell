/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:16:01 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 13:47:10 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_double_char(char **argv, char *debug_print, int print_name)
{
	int	i;

	if (print_name)
		printf("\n-- %s --\n", debug_print);
	i = 0;
	while (argv[i])
	{
		printf("%s[%d] : `%s`\n", debug_print, i, argv[i]);
		++i;
	}
}

void	debug_compound(t_compound *compound, char *debug_print)
{
	int	i;

	printf("\n-- %s --\n", debug_print);
	i = 0;
	while (compound[i].type != UNSET && compound[i].type != -1)
	{
		if (compound[i].type == CMD)
			printf("compound[%d] type : CMD\n", i);
		if (compound[i].type == REDIR_IN)
			printf("compound[%d] type : REDIR_IN\n", i);
		if (compound[i].type == REDIR_OUT)
			printf("compound[%d] type : REDIR_OUT\n", i);
		if (compound[i].type == HERE_DOC)
			printf("compound[%d] type : HERE_DOC\n", i);
		if (compound[i].type == APPEND)
			printf("compound[%d] type : APPEND\n", i);
		if (compound[i].type == PIPE)
			printf("compound[%d] type : PIPE\n", i);
		debug_double_char(compound[i].content, "	content", 0);
		++i;
	}
}

void	debug_heredoc(int fd)
{
	ssize_t	read_size;
	char	buffer[11];

	read_size = read(fd, &buffer, 10);
	buffer[read_size] = '\0';
	printf("-- HEREDOC - FD [%d] -- \n", fd);
	while (read_size && ft_strchr(buffer, '\n'))
	{
		printf("%s", buffer);
		read_size = read(fd, &buffer, 10);
		buffer[read_size] = '\0';
	}
}

void	debug_expand(char *content, int index)
{
	int	i;

	i = 0;
	printf("content: ");
	while (content[i])
	{
		if (i == index)
		{
			if (content[i] == '"' || content[i] == '\'')
				printf("\033[0;31m%c\033[0;37m", content[i]);
			else if (content[i] == '$')
				printf("\033[0;32m%c\033[0;37m", content[i]);
			else
				printf("\033[0;36m%c\033[0;37m", content[i]);
		}
		else
			printf("%c", content[i]);
		++i;
	}
	printf("\n");
}

void	db_print_file(t_file *file, char *s, char c)
{
	printf("%c	file[%s]: %p\n", c, s, file);
	printf("%c	name: %s\n", c, file->name);
	printf("%c	boool: %d\n", c, file->exists);
	printf("%c	type: %d\n", c, file->type);
}

void	db_print_exec_struct(t_exec *exec)
{
	printf("Recap after init of the exec structure\n");
	printf("	size of commands: %d\n", exec->cmd_size);
	printf("	size of files: %d\n", exec->file_size);
	printf("Pipe struct\n");
	printf("	pipe[0]: %d | pipe[1]: %d\n", exec->pi.pe[0], exec->pi.pe[1]);
	printf("	prev[0]: %d \n", exec->pi.pe_prev);
	printf("Cmd struct\n");
	for (int i = 0; i < exec->cmd_size; i++)
	{
		printf("	cmd[%d]: %s\n", i, exec->cmd[i].cmd);
		if (!exec->cmd[i].args)
			printf("\tCMD Arg %d doesn't exist\n", i);
		for (int j = 0; exec->cmd[i].args && exec->cmd[i].args[j]; j ++)
			printf("	arg[%d]: %s\n", j, exec->cmd[i].args[j]);
		if (exec->cmd[i].in != NULL)
			db_print_file(exec->cmd[i].in, "in", '\t');
		if (exec->cmd[i].out != NULL)
			db_print_file(exec->cmd[i].out, "out", '\t');
	}
	printf("File struct\n");
	printf("TYPES:\n-REDIR_IN: %d\n-REDIR_OUT: %d\n-HERE_DOC: %d\n-APPEND: %d\n",
		REDIR_IN, REDIR_OUT, HERE_DOC, APPEND);
	for (int i = 0; i < exec->file_size; i++)
		db_print_file(&exec->files[i], ft_itoa(i), ' ');
}

/*
void	print_env(char **env);
// test of epxort functions
int	main(int ac, char **av, char **envb)
{
	char	**env;
	char	**args;

	args = ft_calloc(2, sizeof(char *));
	if (ac == 1 && envb && *envb)
		env = copy_env(envb);
	else
		env = NULL;
	print_env(env);
	if (ac < 2)
	{
		printf("Adding A1=123\n");
		args[0] = ft_strdup("A1=123");
		ft_export(&env, args);
		print_env(env);
		printf("Adding A1=321\n");
		free(args[0]);
		args[0] = ft_strdup("A1=321");
		ft_export(&env, args);
		free(args[0]);
		print_env(env);
	}
	else
	{
		printf("\nAdding %s\n\n", av[1]);
		env = extend_env(env, av[1]);
	}
	free(args);
	ft_free_dstr(env);
}
*/

/*
Here is a prototype which copies memory so that we're independant from tokens
int	dup_file_names(t_files *file, int max_file)
{
	int	i;

	i = 0;
	while (i < max_file)
	{
		file[i].name = ft_strdup(file[i].name);
		if (!file[i].name)
			return (free_files(file), 1);
		file[i].exists = true;
		i++;
	}
	return (0);
}
*/

/* LOGIC OF THE EXEC - CHILD
-> exec
	(tokens) (env)
	-> child frees (tokens) (env)
	~~~> alloc (cpy of args) free (tokens)
	~~~> alloc (split of PATH) ??? (x)	- lets try without it
										- otherwise we just allocate it
		-> exec frees (char **) (env)
*/

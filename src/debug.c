/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:16:01 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 12:39:28 by aoberon          ###   ########.fr       */
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
================= TESTS =================
LEXER TEST :


"a"sss"f"f|fdf>fd<$$$HOME
result : 
"a"sss"f"
f
|
fdf
>
fd
<
$$$HOME


"a  1	2"bbb"c"d|efg>hi<<$$$HOME$USER
"a  1        2"bbb"c"d|efg>hi<<$$$HOME$$USER || $PW|
"a  1        2"bbb"c"d| e          fg>hi<<$$$HOME$$USER || $PW|	'zyx'5'wvuts' "rq'po'nmlk" 'jihg"fed"cba'

PARSING TEST :

cmd1 op arg1 arg2 > file arg3 | cmd2 arg1 arg2 < file arg3 | cmd3 arg1 >> file arg2 arg3 | cmd4 << file arg1 arg2 arg3

cmd1 op arg1 arg2 > file arg3 | cmd2 arg1 arg2 < file arg3 | cmd3 arg1 >> file arg2 arg3 | cmd4 << file arg1 arg2 arg3 | cmd5 > file | >> file < file

ls cmdjdkf and so em no >> filehere > true file < infile < infiletwo | cat oui oui oui

--------------------------------------------------

EXPAND TEST :

echo $HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'
result :
/mnt/nfs/homes/aoberonaoberon$PATH'0'"$PATH"

echo "toto$HOME"'$USER toto'"'toto'"
result :
toto/mnt/nfs/homes/aoberon$USER toto'toto'

echo "tata$USER"'$PATH'toto"'$?'"titi
result :
tataaoberon$PATHtototiti
--------------------------------------------------
*/

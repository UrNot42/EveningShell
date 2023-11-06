#include "minishell.h"

void	print_file(t_file *file, char *s, char c)
{
	printf("%c	file[%s]: %p\n", c, s, file);
	printf("%c	name: %s\n", c, file->name);
	printf("%c	boool: %d\n", c, file->exists);
	printf("%c	type: %d\n", c, file->type);
}

void	print_exec_struct(t_exec *exec)
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
		for (int j = 0; exec->cmd[i].args[j]; j ++)
			printf("	arg[%d]: %s\n", j, exec->cmd[i].args[j]);
		if (exec->cmd[i].in != NULL)
			print_file(exec->cmd[i].in, "in", '\t');
		if (exec->cmd[i].out != NULL)
			print_file(exec->cmd[i].out, "out", '\t');
	}
	printf("File struct\n");
	printf("TYPES:\n-REDIR_IN: %d\n-REDIR_OUT: %d\n-HERE_DOC: %d\n-APPEND: %d\n",
		REDIR_IN, REDIR_OUT, HERE_DOC, APPEND);
	for (int i = 0; i < exec->file_size; i++)
		print_file(&exec->files[i], ft_itoa(i), ' ');
}

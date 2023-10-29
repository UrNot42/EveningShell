/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/29 13:46:26 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file(t_file *file, char *s, char c)
{
	printf("%c	file[%s]: %p\n", c, s, file);
	printf("%c	name: %s\n", c, file->name);
	printf("%c	boool: %d\n", c, file->exists);
	printf("%c	type: %d\n", c, file->type);
}

void	print_exec_sruct(t_exec *exec)
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

// TODO: WIP
int	execute(t_token *token_list, char **env)
{
	t_exec	exec;

	if (set_execute_struct(token_list, &exec))
		return (1);
	print_exec_sruct(&exec);
	(void)env;
	return (1); // TODO: REMOVE, HERE ONLY FOR TESTING
	// open_files(ex.files);
	// i = 0;
	// while (i < exec.cmd_size)
	// {
	// 	if (i < exec.cmd_size - 1) // not last cmd
	// 		pipe(exec.pi.pe);
	// 	exec.pi.ds[i] = fork(); // store the pid
	// 	if (exec.pi.ds[i] == 0) // if inside the child do the process
	// 		child_process(&ex, i); // start the child loop
	// 	if (exec.pi.pe_prev != -1) // if there is a previous pipe close it
	// 		close(exec.pi.pe_prev);
	// 	exec.pi.pe_prev = exec.pi.pe[0]; // store the new previous pipe for the next child process to use
	// 	close(exec.pi.pe[1]);
	// 	i++;
	// }
	// (close(exec.pi.pe[0]), close(exec.pi.pe_prev)); // close ur unclosed pipes
	// free_token(token_list);
	// exec.pi.ds[i] = -1;
	return (wait_pids(exec.pi.ds));
}

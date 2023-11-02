/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/02 17:31:18 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_exec *ex, int i, int last_err)
{
	int	code;

	code = is_builtin(ex->cmd[i].cmd);
	if (code == BT_CD)
		builtins_cd(ex->cmd[i].args, ex->env);
	if (code == BT_ECHO)
		builtins_echo(ex->cmd[i].args);
	if (code == BT_ENV)
		env(ex->env);
	if (code == BT_EXIT)
	{
		if (ex->cmd[i].args && ex->cmd[i].args[0] && ex->cmd[i].args[1])
			code = ft_atoi(ex->cmd[i].args[1]);
		else
			code = last_err;
		free_exec(ex, true);
		builtins_exit(code);
	}
	if (code == BT_EXPORT)
		ft_export(ex->env, ex->cmd[i].args);
	if (code == BT_PWD)
		buitlins_pwd(ex->cmd[i].args);
	if (code == BT_UNSET)
		unset(ex->env, ex->cmd[i].args);
	return (0);
}

int	dup_fd(t_cmd *cmd, t_pipe pi)
{
	if (cmd->in != NULL && cmd->in->exists)
	{
		if (cmd->in->fd == -1)
			return (perror(cmd->in->name), 1);
		dup2(cmd->in->fd, STDIN_FILENO);
		close(cmd->in->fd);
	}
	else
		dup2(pi.pe_prev, STDIN_FILENO);
	if (cmd->out != NULL && cmd->out->exists)
	{
		if (cmd->out->fd == -1)
			return (perror(cmd->out->name), 1);
		dup2(cmd->out->fd, STDOUT_FILENO);
		close(cmd->out->fd);
	}
	else
		dup2(pi.pe[1], STDOUT_FILENO);
	return (0);
}

void	exec_cmd(t_exec *exec, int i, int last_err)
{
	if (is_builtin(exec->cmd[i].cmd))
	{
		execute_builtin(exec, i, last_err);
		free_exec(exec, true);
		exit(0);
	}
}

void	child_process(t_exec *exec, int i, int last_err)
{
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	if (dup_fd(&exec->cmd[i], exec->pi))
	{
		close_files(exec->files, exec->file_size);
		close_pipe(&exec->pi, PIP_ALL);
		free_exec(exec, true);
		exit(127);
	}
	close_files(exec->files, exec->file_size);
	close_pipe(&exec->pi, PIP_ALL);
	exec_cmd(exec, i, last_err);
	if (create_cmd(&exec->cmd[i], exec->env, &cmd, &args))
		(free_exec(exec, true), exit(127));
	free_exec(exec, false);
	execve(cmd, args, exec->env);
	ft_free_dstr(exec->env);
	exit(127);
}

/*
-> exec
	(tokens) (env)
	-> child frees (tokens) (env)
	~~~> alloc (cpy of args) free (tokens)
	~~~> alloc (split of PATH) ??? (x)	- lets try without it
										- otherwise we just allocate it
		-> exec frees (char **) (env)
*/

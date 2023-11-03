/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/03 12:51:57 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_exec *ex, int last_err)
{
	int	code;

	code = is_builtin(ex->cmd->cmd);
	if (code == BT_CD)
		code = builtins_cd(ex->cmd->args, *ex->env);
	else if (code == BT_ECHO)
		code = builtins_echo(ex->cmd->args);
	else if (code == BT_ENV)
		code = env(*ex->env);
	else if (code == BT_EXIT)
	{
		if (ex->cmd->args && ex->cmd->args[0] && ex->cmd->args[1])
			code = ft_atoi(ex->cmd->args[1]);
		else
			code = last_err;
		free_exec(ex, true);
		code = builtins_exit(code);
	}
	else if (code == BT_EXPORT)
		code = ft_export(ex->env, &ex->cmd->args[1]);
	else if (code == BT_PWD)
		code = buitlins_pwd(ex->cmd->args);
	else if (code == BT_UNSET)
		code = unset(*ex->env, ex->cmd->args);
	return (close_files(ex->files, ex->file_size), code);
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
	int	code;

	if (is_builtin(exec->cmd[i].cmd))
	{
		code = execute_builtin(exec, last_err);
		free_exec(exec, true);
		exit(code);
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
	if (create_cmd(&exec->cmd[i], *exec->env, &cmd, &args))
		(free_exec(exec, true), exit(127));
	free_exec(exec, false);
	execve(cmd, args, *exec->env);
	ft_free_dstr(*exec->env);
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

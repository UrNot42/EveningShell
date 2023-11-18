/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/18 12:47:00 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sends the correct function with the correct arguments within the
 * shell builtins
 *
 * @param ex
 * @param last_err
 * @param i
 * @param fd
 * @return int
 */
int	execute_builtin(t_exec *ex, int last_err, int i, int fd)
{
	int	code;

	code = is_builtin(ex->cmd[i].cmd);
	if (code == BT_CD)
		code = builtins_cd(ex->cmd[i].args, *ex->env);
	else if (code == BT_ECHO)
		code = builtins_echo(ex->cmd[i].args);
	else if (code == BT_ENV)
		code = env(*ex->env);
	else if (code == BT_EXIT)
		code = builtins_exit(ex, i, last_err, fd);
	else if (code == BT_EXPORT)
		code = ft_export(ex->env, &ex->cmd[i].args[1]);
	else if (code == BT_PWD)
		code = builtins_pwd();
	else if (code == BT_UNSET)
		code = unset(*ex->env, &ex->cmd[i].args[1]);
	return (code);
}

/**
 * @brief dups in and out file or the previous or next pipe
 *
 * @param cmd
 * @param pi
 * @return int
 */
int	dup_fd(t_cmd *cmd, t_pipe pi)
{
	if (cmd->in != NULL && cmd->in->exists)
	{
		if (cmd->in->fd == -1)
			return (1);
		if (dup2(cmd->in->fd, STDIN_FILENO) == -1)
			return (error_dup_failed("in"), close(cmd->out->fd), 1);
		close(cmd->in->fd);
	}
	else if (pi.pe_prev != -1 && dup2(pi.pe_prev, STDIN_FILENO) == -1)
		return (error_dup_failed("in pipe"), 1);
	if (cmd->out != NULL && cmd->out->exists)
	{
		if (cmd->out->fd == -1)
			return (1);
		if (dup2(cmd->out->fd, STDOUT_FILENO) == -1)
			return (error_dup_failed("out"), close(cmd->out->fd), 1);
		close(cmd->out->fd);
	}
	else if (pi.pe[1] != -1 && dup2(pi.pe[1], STDOUT_FILENO) == -1)
		return (error_dup_failed("out pipe"), 1);
	return (0);
}

/**
 * @brief executes builtin and checks for existence of the said command
 *
 * @param exec
 * @param i
 * @param last_err
 */
void	exec_cmd(t_exec *exec, int i, int last_err)
{
	int	code;

	if (!exec->cmd[i].cmd)
		exit(0);
	if (is_builtin(exec->cmd[i].cmd))
	{
		code = execute_builtin(exec, last_err, i, -1);
		close_files(exec->files, exec->file_size);
		free_exec(exec, true);
		exit(code);
	}
}

/**
 * @brief process inside a fork to start correctly a command
 *
 * @param exec
 * @param i
 * @param last_err
 */
void	child_process(t_exec *exec, int i, int last_err)
{
	char	*cmd;
	char	**args;
	int		err_cmd;

	cmd = NULL;
	args = NULL;
	if (dup_fd(&exec->cmd[i], exec->pi))
		(close_files(exec->files, exec->file_size),
			close_pipe(&exec->pi, PIP_ALL), free_exec(exec, true), exit(1));
	close_files(exec->files, exec->file_size);
	close_pipe(&exec->pi, PIP_ALL);
	if (!exec->cmd[i].args)
		(free_exec(exec, true), exit(0));
	exec_cmd(exec, i, last_err);
	err_cmd = create_cmd(&exec->cmd[i], *exec->env, &cmd, &args);
	if (err_cmd)
		(free_exec(exec, true), exit(127 - (err_cmd == 2)));
	free_exec(exec, false);
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	execve(cmd, args, *exec->env);
	ft_free_dstr(*exec->env);
	exit(127);
}

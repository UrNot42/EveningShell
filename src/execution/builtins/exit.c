/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/09 19:11:52 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	check_exit_args(char **args)
{
	int	i;
	int	err;

	err = 0;
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		write(2, "exit\n", 5);
	if (!args || !*args)
		return (err);
	i = 0;
	while (args[i])
	{
		if (!is_num(args[i]))
		{
			err = 1;
			break ;
		}
		i++;
	}
	if (!err && args[1] && args[2])
		err = 2;
	if (err == 1)
		write(2, "minishell: exit: numeric argument required\n", 43);
	else if (err == 2)
		write(2, "minishell: exit: too many arguments\n", 36);
	return (err);
}

/**
 * @brief Exits the shell process currently running
 *
 * @return exit [n]
 * 			Exit the shell, returning a status of n to the shell’s parent.
 * 			If n is omitted, the exit status is that of the last command executed.
 * 			Any trap on EXIT is executed before the shell terminates.
 */
int	builtins_exit(t_exec *ex, int i, int last_err, int fd_stdout)
{
	int	code;
	int	err;

	if (ex->cmd[i].args && ex->cmd[i].args[0] && ex->cmd[i].args[1])
		code = ft_atoi(ex->cmd[i].args[1]);
	else
		code = last_err;
	err = check_exit_args(&ex->cmd[i].args[1]);
	if (err == 1)
		code = 2;
	if (err == 2)
		return (2);
	else
	{
		free_exec(ex, true);
		if (fd_stdout != -1)
			close(fd_stdout);
		exit((unsigned char)code);
	}
	return (code);
}

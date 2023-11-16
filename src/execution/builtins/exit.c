/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:26:42 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 19:45:06 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if a str is only composed of digits
 *
 * @param str
 * @return true
 * @return false
 */
static bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+' && str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief allows or not the exit function to actually exit the current process
 *
 * @param args
 * @return errors while checking the arguments
 */
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
	if (!err && args[1] && args[1][0] != '\0')
		err = 2;
	if (err == 1)
		write(2, "MarmiShell: exit: numeric argument required\n", 44);
	else if (err == 2)
		write(2, "MarmiShell: exit: too many arguments\n", 37);
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
		code = 1;
	if (err == 2)
		return (1);
	else
	{
		free_exec(ex, true);
		if (fd_stdout != -1)
			close(fd_stdout);
		exit((unsigned char)code);
	}
	return (code);
}

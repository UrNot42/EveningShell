/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:16:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 18:57:28 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display error message when malloc fails and exit
 *
 */
void	error_malloc_failed(bool _exit)
{
	write(2, "MarmiShell: malloc failed\n", 26);
	if (_exit)
		exit(1);
}

/**
 * @brief prints a simple message
 *
 * @param s
 */
void	error_dup_failed(char *cmd)
{
	write(2, "MarmiShell: dup failed ", 23);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

/**
 * @brief Displays that a certain command hasn't been found
 *
 * @param cmd
 */
void	command_not_found(char *cmd, bool spe)
{
	if (spe)
	{
		write(2, "Command '", 9);
		write(2, cmd, ft_strlen(cmd));
		write(2, "' not found\n", 12);
	}
	else
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
}

/*
export test="arg1	arg2"
echo 'echo $1' > tmp_test_sh
bash tmp_test_sh $test
echo 'echo $2' > tmp_test_sh
bash tmp_test_sh $test
rm -f tmp_test_sh
*/

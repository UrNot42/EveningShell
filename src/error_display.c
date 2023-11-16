/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:16:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 14:01:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display error message when malloc fails and exit
 *
 */
void	error_malloc_failed(bool _exit)
{
	printf("MarmiShell: malloc failed\n");
	if (_exit)
		exit(1);
}

void	error_dup_failed(void)
{
	printf("MarmiShell: dup failed\n");
}

/**
 * @brief Displays that a certain command hasn't been found
 *
 * @param cmd
 */
void	command_not_found(char *cmd)
{
	write(2, "Command '", 9);
	write(2, cmd, ft_strlen(cmd));
	write(2, "' not found\n", 12);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:16:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:44:29 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display error message when malloc fails and exit
 *
 */
void	error_malloc_failed(bool _exit)
{
	printf("MarmiShell-4.2$: malloc failed\n");
	if (_exit)
		exit(1);
}

void	command_not_found(char *cmd)
{
	write(2, "Command '", 9);
	write(2, cmd, ft_strlen(cmd));
	write(2, "' not found\n", 12);
}

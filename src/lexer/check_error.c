/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:29:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:10:44 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check for quoting and syntax error
 * 
 * @param argv array of strings to check
 * @return int 1 if there is an error, 0 otherwise
 */
int	check_error(char **argv)
{
	if (check_quoting_error(argv) || check_syntax_error(argv))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:29:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/20 18:15:18 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check for quoting and syntax error
 * 
 * @param argv array of strings to check
 * @return int 1 if there is an error, 0 otherwise
 */
int	check_error(char **argv, char **env)
{
	int	syntax_error;

	if (check_quotation_error(argv))
		return (1);
	syntax_error = check_syntax_error(argv, env);
	if (syntax_error == -42)
		return (-42);
	if (syntax_error == 1)
		return (1);
	return (0);
}

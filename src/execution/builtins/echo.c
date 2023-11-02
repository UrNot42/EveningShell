/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 16:42:11 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Detects if the option -n is present in the arguments
 *
 *
 * @param str string to check
 * @return int 1 if the option is present, 0 otherwise
 */
static int	detect_option_n(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Builtins of the command echo
 *
 * /!\ Have to change "arguments" to a better word
 *
 * @param argv char** of the arguments
 */
int	builtins_echo(char **args)
{
	int	i;
	int	new_line;

	new_line = detect_option_n(args[1]);
	i = 1 + new_line;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		printf(" ");
		++i;
	}
	if (!new_line)
		printf("\n");
	return (0);
}

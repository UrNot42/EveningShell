/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 15:15:53 by aoberon          ###   ########.fr       */
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

/**
 * @brief Detects if the option -n is present in the arguments
 * and returns the number of -n
 * 
 * @param argv char ** of the arguments
 * @return int returns the number of -n
 */
static int	detect_option_n(char **argv)
{
	int	i;
	int	j;
	int	new_line;

	if (!argv || !argv[1] || argv[1][0] != '-')
		return (0);
	new_line = 0;
	i = 1;
	j = 0;
	while (argv[i] && argv[i][j] == '-')
	{
		j++;
		while (argv[i][j] == 'n')
			j++;
		if (!argv[i][j])
			new_line += 1;
		i++;
		j = 0;
	}
	return (new_line);
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

	new_line = detect_option_n(args);
	i = 1 + new_line;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		++i;
	}
	if (!new_line)
		printf("\n");
	return (0);
}

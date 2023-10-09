/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 21:26:20 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Detects if the option -n is present in the arguments
 * 
 * /!\ Have to change "arguments" to a better word
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
void	builtins_echo(char **argv)
{
	int	i;
	int	new_line;

	new_line = detect_option_n(argv[1]);
	i = 1 + new_line;
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		printf(" ");
		++i;
	}
	if (!new_line)
		printf("\n");
}

/**
 * @brief Detects if the command is echo
 * 
 * /!\ Have to change "arguments" to a better word
 * 
 * @param argv char** of the arguments to check
 * @return int 1 if the command is echo, 0 otherwise
 */
int	detect_echo(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
	{
		printf("A builtins detected : echo\n");
		return (1);
	}
	return (0);
}

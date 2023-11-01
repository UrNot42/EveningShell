/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:00:52 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 15:10:20 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the number of string in the command type
 * 
 * @param argv array of strings used to create compounds
 * @return size_t count of strings
 */
static size_t	get_number_str_in_cmd(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i] && ft_strcmp(argv[i], "|"))
	{
		if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], "<<")
			|| !ft_strcmp(argv[i], ">") || !ft_strcmp(argv[i], ">>"))
		{
			if (argv[i + 1])
				i += 2;
			else
				i += 1;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

/**
 * @brief Set one string in the compound content (of cmd type)
 * 
 * @param compound array of compounds
 * @param argv array of strings used to create compounds
 * @param i size_t pointer to the index of argv
 * @param k size_t index of the string to be set
 * @return int returns 0 if malloc fails, 1 otherwise
 */
static int	set_one_str_in_cmd(t_compound compound, char **argv,
	size_t *i, size_t k)
{
	if (argv[*i])
	{
		compound.content[k] = ft_strdup(argv[*i]);
		if (!compound.content[k])
			return (0);
		*i += 1;
	}
	return (1);
}

/**
 * @brief parsing a command type
 * 
 * @param compound array of compounds
 * @param i size_t pointer to the index of argv
 * @param n size_t pointer to the index of compound
 * @param argv array of strings used to create compounds
 * @return int returns 0 if malloc fails, 1 otherwise
 */
int	parsing_command(t_compound *compound, size_t *i, size_t *n, char **argv)
{
	size_t	limiter[2];
	size_t	nbis;

	compound[*n].type = CMD;
	limiter[0] = get_number_str_in_cmd(&argv[*i]);
	compound[*n].content = ft_calloc(limiter[0] + 1, sizeof(char *));
	if (!compound[*n].content)
		return (0);
	limiter[1] = -1;
	nbis = 0;
	while (++limiter[1] < limiter[0])
	{
		while (get_redir_type(argv[*i]))
		{
			compound[*n + ++nbis]
				= create_compound(&argv[*i], get_redir_flag(argv[*i]), 2);
			if (!compound[*n + nbis].content || compound[*n + nbis].type == -1)
				return (0);
			*i += 2;
		}
		if (!set_one_str_in_cmd(compound[*n], argv, i, limiter[1]))
			return (0);
	}
	*n += nbis + 1;
	return (1);
}

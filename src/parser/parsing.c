/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:06:06 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 14:42:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of compounds to be created in a command type
 *
 * @param argv array of strings used to create compounds
 * @param i size_t pointer to the index of argv
 * @param count size_t pointer to the count of compounds
 */
static void	count_compound_cmd(char **argv, size_t *i, size_t *count)
{
	*count += 1;
	while (argv[*i] && ft_strcmp(argv[*i], "|"))
	{
		if (!ft_strcmp(argv[*i], "<") || !ft_strcmp(argv[*i], "<<")
			|| !ft_strcmp(argv[*i], ">") || !ft_strcmp(argv[*i], ">>"))
		{
			if (argv[*i + 1])
				*i += 2;
			else
				*i += 1;
			*count += 1;
		}
		else
			*i += 1;
	}
}

/**
 * @brief Counts the number of compounds to be created
 *
 * @param argv array of strings used to create compounds
 * @return size_t count of compounds
 */
static size_t	count_compound(char **argv)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], "<<")
			|| !ft_strcmp(argv[i], ">") || !ft_strcmp(argv[i], ">>"))
		{
			if (argv[i + 1])
				i += 2;
			else
				i++;
			count++;
		}
		else if (!ft_strcmp(argv[i], "|"))
		{
			i++;
			count++;
		}
		else
			count_compound_cmd(argv, &i, &count);
	}
	return (count);
}

/**
 * @brief Set the compounds
 *
 * @param compound array of compounds
 * @param argv array of strings used to create compounds
 * @param i size_t pointer to the index of argv
 * @param n size_t pointer to the index of compound
 * @return int 0 if a malloc failed, 1 otherwise
 */
static int	set_compounds(t_compound *compound, char **argv,
	size_t *i, size_t *n)
{
	if (get_redir_type(argv[*i]))
	{
		compound[*n] = create_compound(&argv[*i], get_redir_type(argv[*i]), 2);
		if (!compound[*n].content)
			return (0);
		if (argv[*i + 1])
			*i += 2;
		else
			*i += 1;
		*n += 1;
	}
	else if (!ft_strcmp(argv[*i], "|"))
	{
		compound[*n] = create_compound(&argv[*i], PIPE, 1);
		if (!compound[*n].content)
			return (0);
		*i += 1;
		*n += 1;
	}
	else if (!parsing_command(compound, i, n, argv))
		return (0);
	if (!compound[*n - 1].content)
		return (0);
	return (1);
}

/**
 * @brief parsing of the command line
 *
 * @param argv array of strings used to create compounds
 * @return t_compound* array of compounds
 */
t_compound	*parsing(char **argv)
{
	size_t		i;
	size_t		n;
	t_compound	*compound;

	compound = ft_calloc(count_compound(argv) + 1, sizeof(t_compound));
	if (!compound)
		return (NULL);
	i = 0;
	n = 0;
	while (argv[i])
	{
		if (!set_compounds(compound, argv, &i, &n))
		{
			return (free_compound(compound), NULL);
		}
	}
	return (compound);
}

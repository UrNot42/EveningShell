/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:00:52 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 20:33:43 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the number of string in the command type
 * 
 * @param argv array of strings used to create tokens
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
 * @brief Set one string in the token content (of cmd type)
 * 
 * @param token array of tokens
 * @param argv array of strings used to create tokens
 * @param i size_t pointer to the index of argv
 * @param k size_t index of the string to be set
 * @return int returns 0 if malloc fails, 1 otherwise
 */
static int	set_one_str_in_cmd(t_token token, char **argv, size_t *i, size_t k)
{
	if (argv[*i])
	{
		token.content[k] = ft_strdup(argv[*i]);
		if (!token.content[k])
			return (0);
		*i += 1;
	}
	return (1);
}

/**
 * @brief Tokenization a command type
 * 
 * @param token array of tokens
 * @param i size_t pointer to the index of argv
 * @param n size_t pointer to the index of token
 * @param argv array of strings used to create tokens
 * @return int returns 0 if malloc fails, 1 otherwise
 */
int	tokenization_command(t_token *token, size_t *i, size_t *n, char **argv)
{
	size_t	limiter[2];
	size_t	n_bis;

	token[*n].type = CMD;
	limiter[0] = get_number_str_in_cmd(&argv[*i]);
	token[*n].content = ft_calloc(limiter[0] + 1, sizeof(char *));
	if (!token[*n].content)
		return (0);
	limiter[1] = -1;
	n_bis = 0;
	while (++limiter[1] < limiter[0])
	{
		while (get_redir_type(argv[*i]))
		{
			token[*n + ++n_bis]
				= create_token(&argv[*i], get_redir_flag(argv[*i]), 2);
			if (!token[*n + n_bis].content || token[*n + n_bis].type == -1)
				return (0);
			*i += 2;
		}
		if (!set_one_str_in_cmd(token[*n], argv, i, limiter[1]))
			return (0);
	}
	*n += n_bis + 1;
	return (1);
}

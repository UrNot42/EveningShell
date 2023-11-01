/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:06:06 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 12:25:47 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of tokens to be created in a command type
 * 
 * @param argv array of strings used to create tokens
 * @param i size_t pointer to the index of argv
 * @param count size_t pointer to the count of tokens
 */
static void	count_tokenization_cmd(char **argv, size_t *i, size_t *count)
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
 * @brief Counts the number of tokens to be created
 * 
 * @param argv array of strings used to create tokens
 * @return size_t count of tokens
 */
static size_t	count_tokenization(char **argv)
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
			count_tokenization_cmd(argv, &i, &count);
	}
	return (count);
}

/**
 * @brief Set the tokens
 * 
 * @param token array of tokens
 * @param argv array of strings used to create tokens
 * @param i size_t pointer to the index of argv
 * @param n size_t pointer to the index of token
 * @return int 
 */
static int	set_tokens(t_token *token, char **argv, size_t *i, size_t *n)
{
	if (get_redir_type(argv[*i]))
	{
		token[*n] = create_token(&argv[*i], get_redir_flag(argv[*i]), 2);
		if (!token[*n].content)
			return (0);
		if (argv[*i + 1])
			*i += 2;
		else
			*i += 1;
		*n += 1;
	}
	else if (!ft_strcmp(argv[*i], "|"))
	{
		token[*n] = create_token(&argv[*i], PIPE, 1);
		if (!token[*n].content)
			return (0);
		*i += 1;
		*n += 1;
	}
	else if (!tokenization_command(token, i, n, argv))
		return (0);
	if (!token[*n - 1].content)
		return (0);
	return (1);
}

/**
 * @brief Tokenization of the command line
 * 
 * @param argv array of strings used to create tokens
 * @return t_token* array of tokens
 */
t_token	*tokenization(char **argv)
{
	size_t	i;
	size_t	n;
	t_token	*token;

	token = ft_calloc(count_tokenization(argv) + 1, sizeof(t_token));
	if (!token)
		return (NULL);
	i = 0;
	n = 0;
	while (argv[i])
	{
		if (!set_tokens(token, argv, &i, &n))
			return (free_token(token), NULL);
	}
	token[n].type = -1;
	return (token);
}

// cmd1 op arg1 arg2 > file arg3 | cmd2 arg1 arg2 < file arg3 | cmd3 arg1 >> file arg2 arg3 | cmd4 << file arg1 arg2 arg3
// cmd1 op arg1 arg2 > file arg3 | cmd2 arg1 arg2 < file arg3 | cmd3 arg1 >> file arg2 arg3 | cmd4 << file arg1 arg2 arg3 | cmd5 > file | >> file < file

// ls cmdjdkf and so em no >> filehere > true file < infile < infiletwo | cat oui oui oui

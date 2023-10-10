/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:06:06 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/10 11:04:00 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_tokenization(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], "<<")
			|| !ft_strcmp(argv[i], ">") || !ft_strcmp(argv[i], ">>"))
		{
			i += 2;
			count += 2;
		}
		else if (!ft_strcmp(argv[i], "|"))
		{
			i++;
			count++;
		}
		else
		{
			while (argv[i] && ft_strcmp(argv[i], "|"))
			{
				if (!ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], ">")
					|| !ft_strcmp(argv[i], ">>"))
				{
					i += 2;
					count += 2;
				}
				else
					i++;
			}
		}
	}
	printf("count: %d\n", count);
	return (count);
}

size_t	get_next_command_type(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i] && ft_strcmp(argv[i], "|"))
	{
		if (!ft_strcmp(argv[i], ">"))
		{
			i += 2;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	**doublecharncpy(char **src, size_t n)
{
	char	**dest;
	size_t	i;

	dest = ft_calloc(n + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	return (dest);
}

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
		if (!ft_strcmp(argv[i], "<"))
		{
			token[n].type = REDIR_IN;
			token[n].content = doublecharncpy(&argv[i], 2);
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			i += 2;
			n++;
		}
		else if (!ft_strcmp(argv[i], ">"))
		{
			token[n].type = REDIR_OUT;
			token[n].content = doublecharncpy(&argv[i], 2);
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			i += 2;
			n++;
		}
		else if (!ft_strcmp(argv[i], "<<"))
		{
			token[n].type = HERE_DOC;
			token[n].content = doublecharncpy(&argv[i], 2);
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			i += 2;
			n++;
		}
		else if (!ft_strcmp(argv[i], ">>"))
		{
			token[n].type = APPEND;
			token[n].content = doublecharncpy(&argv[i], 2);
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			i += 2;
			n++;
		}
		else if (!ft_strcmp(argv[i], "|"))
		{
			token[n].type = PIPE;
			token[n].content = doublecharncpy(&argv[i], 1);
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			i++;
			n++;
		}
		else
		{
			size_t		j;
			size_t		k;
			size_t	n_bis;
			token[n].type = CMD;
			j = get_next_command_type(&argv[i]);
			token[n].content = ft_calloc(j + 1, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			k = 0;
			n_bis = 0;
			while (k < j)
			{
				if (!ft_strcmp(argv[i], ">"))
				{
					n_bis++;
					token[n + n_bis].type = REDIR_OUT;
					token[n + n_bis].content = doublecharncpy(&argv[i], 2);
					if (!token[n + n_bis].content)
						return (printf("FREE AND EXIT !\n"), NULL);
					i += 2;
				}
				if (argv[i])
				{
					token[n].content[k] = ft_strdup(argv[i]);
					i++;
				}
				k++;
			}
			n += n_bis + 1;
		}
	}
	debug_token(token);
	return (token);
}

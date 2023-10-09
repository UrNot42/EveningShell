/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:06:06 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/09 18:27:58 by aoberon          ###   ########.fr       */
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
			i++;
	}
	printf("count: %d\n", count);
	return (count);
}

size_t	get_next_command_type(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && ft_strcmp(argv[i], "<") && ft_strcmp(argv[i], "<<")
		&& ft_strcmp(argv[i], ">") && ft_strcmp(argv[i], ">>")
		&& ft_strcmp(argv[i], "|"))
		i++;
	return (i);
}

t_token	*tokenization(char **argv)
{
	int		i;
	int		n;
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
			token[n].content = ft_calloc(3, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			token[n].content[0] = ft_strdup(argv[i]);
			i++;
			token[n].content[1] = ft_strdup(argv[i]);
			token[n].content[2] = NULL;
			i++;
			n++;
		}
		else if (!ft_strcmp(argv[i], ">"))
		{
			token[n].type = REDIR_OUT;
			token[n].content = ft_calloc(3, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			token[n].content[0] = ft_strdup(argv[i]);
			i++;
			token[n].content[1] = ft_strdup(argv[i]);
			token[n].content[2] = NULL;
			i++;
			n++;
		}
		else if (!ft_strcmp(argv[i], "<<"))
		{
			token[n].type = HERE_DOC;
			token[n].content = ft_calloc(3, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			token[n].content[0] = ft_strdup(argv[i]);
			i++;
			token[n].content[1] = ft_strdup(argv[i]);
			token[n].content[2] = NULL;
			i++;
			n++;
		}
		else if (!ft_strcmp(argv[i], ">>"))
		{
			token[n].type = APPEND;
			token[n].content = ft_calloc(3, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			token[n].content[0] = ft_strdup(argv[i]);
			i++;
			token[n].content[1] = ft_strdup(argv[i]);
			token[n].content[2] = NULL;
			i++;
			n++;
		}
		else if (!ft_strcmp(argv[i], "|"))
		{
			token[n].type = PIPE;
			token[n].content = ft_calloc(2, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			token[n].content[0] = ft_strdup(argv[i]);
			i++;
			token[n].content[2] = NULL;
			i++;
			n++;
		}
		else
		{
			printf("i: %d\n", i);
			printf("argv[i]: %s\n", argv[i]);
			printf("n: %d\n", n);
			int		j;
			int		k;
			token[n].type = CMD;
			j = get_next_command_type(&argv[i]);
			printf("j: %d\n", j);
			token[n].content = ft_calloc(j + 1, sizeof(char *));
			if (!token[n].content)
				return (printf("FREE AND EXIT !\n"), NULL);
			k = 0;
			while (k < j)
			{
				printf("strdup: %s\n", argv[i]);
				token[n].content[k] = ft_strdup(argv[i]);
				i++;
				k++;
			}
			printf("end loop : %s\n", argv[i]);
			// i++;
			n++;
		}
	}
	debug_token(token);
	return (token);
}

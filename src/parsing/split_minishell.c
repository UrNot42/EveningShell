/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:59:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 21:28:32 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// " -> "
// ' -> "
// sapce + tab -> cut
// < -> cut
// > -> cut
// | -> cut
// $ -> sapce + tab

static bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

static int	wl_double_quote(char const *s, int i)
{
	i++;
	while (s[i] != '"' && s[i])
	{
		i++;
	}
	return (i);
}

static int	wl_single_quote(char const *s, int i)
{
	i++;
	while (s[i] != '\'' && s[i])
	{
		i++;
	}
	return (i);
}

static size_t	word_length(char const *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '|' || s[i] == ' ' || s[i] == '\t')
		return (1);
	if (s[i] == '<')
	{
		if (s[i + 1] == '<')
			return (2);
		return (1);
	}
	if (s[i] == '>')
	{
		if (s[i + 1] == '>')
			return (2);
		return (1);
	}
	while (s[i])
	{
		if (s[i] == '"')
		{
			i = wl_double_quote(s, i);
			while (!is_metacharacter(s[i + 1]) && s[i])
			{
				i++;
				if (s[i] == '"')
					i = wl_double_quote(s, i);
			}
			i++;
			break ;
		}
		if (s[i] == '\'')
		{
			i = wl_single_quote(s, i);
			while (!is_metacharacter(s[i + 1]) && s[i])
			{
				i++;
				if (s[i] == '\'')
					i = wl_single_quote(s, i);
			}
			i++;
			break ;
		}
		if (is_metacharacter(s[i]))
			break ;
		if (s[i] == '$')
		{
			while (s[i] == '$')
				i++;
			while (!is_metacharacter(s[i]) && s[i] != '/' && s[i])
			{
				i++;
				if (s[i] == '$')
					break ;
			}
			break ;
		}
		i++;
	}
	return (i);
}

static size_t	word_count(char const *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	while (*s)
	{
		while (!*s || *s == ' ' || *s == '\t')
		{
			s++;
		}
		i = word_length(s);
		if (i)
			count++;
		s += i;
	}
	return (count);
}

static char	*ft_strcpy(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (0);
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_rewind_free(char **result, size_t y)
{
	while (y <= 0)
	{
		free(result[y]);
		y--;
	}
	free(result);
	return (NULL);
}


void	debug_minishplit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("minishplit[%d] : %s\n", i, argv[i]);
		++i;
	}
}

char	**split_minishell(char const *s)
{
	size_t	i;
	size_t	count;
	char	**argv;

	i = 0;
	count = word_count(s);
	argv = ft_calloc(count + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	while (i < count)
	{
		while (!*s || *s == ' ' || *s == '\t')
			s++;
		argv[i] = ft_strcpy((char *)s, word_length(s));
		if (!argv[i])
			return (ft_rewind_free(argv, i));
		s += word_length(s);
		i++;
	}
	debug_minishplit(argv);
	return (argv);
}

// "a"sss"f"f|fdf>fd<$$$HOME
// "a"sss"f"
// f
// |
// fdf
// >
// fd
// <
// $$$HOME

// "a"sss"f"f|fdf>fd<$$$HOME
// "a  1	2"bbb"c"d|efg>hi<<$$$HOME$USER
// "a  1        2"bbb"c"d|efg>hi<<$$$HOME$$USER || $PW|
// "a  1        2"bbb"c"d| e          fg>hi<<$$$HOME$$USER || $PW|

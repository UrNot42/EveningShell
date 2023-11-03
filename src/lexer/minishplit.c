/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:59:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 17:43:54 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count the length of a word. A word is delimited by metacharacters,
 * double quotes, single quotes.
 * 
 * @param s string to count in
 * @return size_t size of the word
 */
static size_t	word_length(char const *s)
{
	size_t	i;

	i = wl_metacharacters(s);
	if (i)
		return (i);
	while (s[i])
	{
		if (s[i] == '"')
		{
			return (i + wl_double_quotes(&s[i]));
		}
		if (s[i] == '\'')
		{
			return (i + wl_single_quotes(&s[i]));
		}
		if (is_metacharacter(s[i]))
			break ;
		i++;
	}
	return (i);
}

/**
 * @brief count the number of words in a string.
 * 
 * @param s string to count in
 * @return size_t number of words, used to malloc the array of strings
 */
static size_t	word_count(char const *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
		{
			s++;
		}
		if (!*s)
			break ;
		i = word_length(s);
		if (i)
			count++;
		s += i;
	}
	return (count);
}

/**
 * @brief copy a string of size n
 * 
 * @param src string to copy
 * @param n size of the string
 * @return char* string copied
 */
static char	*ft_strcpy(char *src, size_t n)
{
	size_t		i;
	char		*dest;

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

/**
 * @brief free the mallocs in rewind to avoid unallocated memory
 * 
 * @param argv array of strings to free
 * @param y size_t of the last string malloced
 * @return char** NULL
 */
static char	**ft_rewind_free(char **argv, size_t y)
{
	while (y <= 0)
	{
		free(argv[y]);
		y--;
	}
	free(argv);
	return (NULL);
}

/**
 * @brief Special split for minishell
 * 
 * @param s string returned by readline
 * @return char** array of strings splitted by bash rules
 */
char	**minishplit(char const *s)
{
	size_t	i;
	size_t	count;
	size_t	length_word;
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
		length_word = word_length(s);
		argv[i] = ft_strcpy((char *)s, length_word);
		if (!argv[i])
			return (ft_rewind_free(argv, i));
		s += length_word;
		i++;
	}
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
// "a  1        2"bbb"c"d| e          fg>hi<<$$$HOME$$USER
//		 || $PW|	'zyx'5'wvuts' "rq'po'nmlk" 'jihg"fed"cba'
// DELETE COMMENT AT THE START OF THE FILE \/!\/!\/!\/

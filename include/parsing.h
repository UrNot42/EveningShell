/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:31 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/09 17:57:24 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

enum	e_command_type
{
	CMD,
	REDIR_IN, //char *tab[3] = {"<", "fallout", NULL};
	REDIR_OUT, //char *tab[3] = {">", "fallout", NULL};
	HERE_DOC, //char *tab[3] = {"<<", "fallout", NULL};
	APPEND, //char *tab[3] = {">>", "fallout", NULL};
	PIPE, //char *tab[2] = {"|", NULL};
};

typedef struct s_token	t_token;

struct s_token
{
	int		type;
	char	**content;
};

// ========================== MINISHPLIT ==========================

// -------------------------- SPLIT_MINISHELL --------------------------

char	**split_minishell(char const *s);

// -------------------------- double_quote --------------------------

size_t	wl_double_quotes(char const *s);

// -------------------------- single_quote --------------------------

size_t	wl_single_quotes(char const *s);

// -------------------------- dollar --------------------------

size_t	wl_dollars(char const *s);

// -------------------------- METACHARACTERS --------------------------

bool	is_metacharacter(char c);

size_t	wl_metacharacters(char const *s);

// ========================== TOKENIZATION ==========================

// -------------------------- TOKENIZATION --------------------------

t_token	*tokenization(char **argv);

#endif

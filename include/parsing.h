/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:31 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 13:11:13 by aoberon          ###   ########.fr       */
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

// -------------------------- CHECK_ERROR --------------------------

int		check_error(char **argv);

// -------------------------- CHECK_QUOTING_ERROR --------------------------

int		check_quoting_error(char **argv);

// -------------------------- CHECK_SYNTAX_ERROR --------------------------

int		check_syntax_error(char **argv);

// -------------------------- DOUBLE_QUOTES --------------------------

size_t	wl_double_quotes(char const *s);

// -------------------------- SINGLE_QUOTES --------------------------

size_t	wl_single_quotes(char const *s);

// -------------------------- MINISHPLIT --------------------------

char	**split_minishell(char const *s);

// -------------------------- DOLLARS --------------------------

size_t	wl_dollars(char const *s);

// -------------------------- METACHARACTERS --------------------------

bool	is_metacharacter(char c);

size_t	wl_metacharacters(char const *s);

// ========================== TOKENIZATION ==========================

// -------------------------- COMMAND --------------------------

int		tokenization_command(t_token *token, size_t *i, size_t *n, char **argv);

// -------------------------- REDIR_TYPE --------------------------

int		get_redir_type(char const *str);
int		get_redir_flag(char const *str);

// -------------------------- TOKEN_CREATION --------------------------

char	**doublecharncpy(char **src, size_t n);

t_token	create_token(char **argv, int type, int size);

// -------------------------- TOKENIZATION --------------------------

t_token	*tokenization(char **argv);

// ========================== EXPANSION ==========================

// -------------------------- EXPANSION --------------------------

void	expansion(t_token **token, char **env);

#endif

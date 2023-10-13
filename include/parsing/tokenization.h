/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:04 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 13:44:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

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


#endif

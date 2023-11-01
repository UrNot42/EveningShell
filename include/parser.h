/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:04 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 15:03:06 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum	e_command_type
{
	UNSET,
	CMD,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	PIPE,
};

/*
CMD, char **tab = {"cmd", "arg1", "arg2", .., NULL}
REDIR_IN, char *tab[3] = {"<", "fallout", NULL};
REDIR_OUT, char *tab[3] = {">", "fallout", NULL};
HERE_DOC, char *tab[3] = {"<<", "fallout", NULL};
APPEND, char *tab[3] = {">>", "fallout", NULL};
PIPE, char *tab[2] = {"|", NULL};
*/

typedef struct s_compound	t_compound;

struct s_compound
{
	int		type;
	char	**content;
};

// ========================== PARSER ==========================

// -------------------------- COMMAND --------------------------

int			parsing_command(t_compound *compound,
				size_t *i, size_t *n, char **argv);

// -------------------------- REDIR_TYPE --------------------------

int			get_redir_type(char const *str);
int			get_redir_flag(char const *str);

// -------------------------- COMPOUND_CREATION --------------------------

char		**doublecharncpy(char **src, size_t n);

t_compound	create_compound(char **argv, int type, int size);

// -------------------------- PARSING --------------------------

t_compound	*parsing(char **argv);

void		free_compound(t_compound *command_list);

#endif

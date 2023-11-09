/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/09 13:29:06 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_expand_params
{
	size_t	index_dollar;
	size_t	var_name_length;
	size_t	var_content_length;
	// size_t	expand_length;
	int		index_env;
	char	*var;
}	t_expand_params;

// ========================== EXPAND ==========================

// -------------------------- CHECK_FOR_DOLLAR --------------------------

size_t	check_for_dollar(char const *str, size_t *index_dollar);

// -------------------------- EXPAND_ONE_COMPOUND --------------------------

int		expand_one_content(char **content, char **env, int exit_status);
int		expand_one_compound(t_compound compound, char **env, int exit_status);

// -------------------------- EXPAND --------------------------

void	expand(t_compound **compound, char **env, int exit_status);

// -------------------------- QUOTES_MANAGEMENT --------------------------

char	*remove_quotes(char *word);

// -------------------------- VARIABLE_ENV_FUNCTIONS --------------------------

int		set_var(t_expand_params *params, char *content, char **env,
			int exit_status);

#endif

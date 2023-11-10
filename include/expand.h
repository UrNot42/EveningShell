/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/10 21:52:15 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

// ========================== EXPAND ==========================

// -------------------------- CHECK_FOR_DOLLAR --------------------------

size_t	check_for_dollar(char const *str, size_t *index_dollar);

// -------------------------- EXPAND_ONE_COMPOUND --------------------------

// int		expand_one_content(char **content, char **env, int exit_status);
int		expand_one_compound(t_compound compound, char **env, int exit_status);

char	**expand_one_content(char *content, char **env, int exit_status);

// -------------------------- EXPAND --------------------------

void	expand(t_compound **compound, char **env, int exit_status);

// -------------------------- QUOTES_MANAGEMENT --------------------------

char	*remove_quotes(char *word);

// -------------------------- VARIABLE_ENV_FUNCTIONS --------------------------

// int		set_var(t_expand_params *params, char *content, char **env,
// 			int exit_status);


// typedef struct s_expand_total_length_params
// {
// 	char *content;
// 	char **env;
// 	int	exit_status;
// 	int	index;
// 	int	index_env;
// 	int	total_length;
// 	int	word_length;
// }	t_expand_total_length_params;


int	get_varname_length(char const *str, int index);
int	retrieve_var_name(char **var, char *str, int index_dollar, int size);
int	ft_nbrlen(long n);
int	total_length(char *content, char **env, int exit_status);
int	word_length_expand(char *content, char **env, int exit_status, int *index);
void	ft_itoa_no_malloc(int n, char result[12]);
char	**ft_rewind_free(char **argv, size_t y);

#endif

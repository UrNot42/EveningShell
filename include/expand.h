/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 10:57:51 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_expand_dollar
{
	char	*word;
	char	**env;
	int		exit_status;
}	t_expand_dollar;

typedef struct s_expand_new_content
{
	char			***new_content;
	int				*count;
	int				*index;
	char			*flag;
	t_expand_dollar	t_ed;
}	t_expand_new_content;

// ========================== EXPAND ==========================

// -------------------------- EXPAND_ONE_CONTENT --------------------------

int		expand_one_content(t_compound **compound, int *index,
			char **env, int exit_status);

// -------------------------- EXPAND --------------------------

void	expand(t_compound **compound, char **env, int exit_status);

// -------------------------- IS_EXPAND_DOLLAR --------------------------

bool	is_expand_dollar(char *word);

// -------------------------- QUOTES_MANAGEMENT --------------------------

char	*remove_quotes(char *word);

// ========================== CHAR_MANAGEMENT ==========================

// -------------------------- CHAR2D_MANAGEMENT --------------------------

char	**char2d_add_one_string(char **array);
char	**insert_char2d_into_char2d(char **array1, char **array2, int *index);

// -------------------------- STRING_ADD_CHAR --------------------------

char	*str_add_one_char(char *str_to_free, char c);

// ========================== CREATE_NEW_CONTENT ==========================

// --------------------- ADD_ONE_CHAR_IN_NEW_CONTENT ---------------------

int		add_one_char_in_new_content(t_expand_new_content expand_new_content);

// -------------------------- CREATE_NEW_CONTENT --------------------------

int		new_char_in_word(char **word, char new_char);

char	**create_new_content(t_expand_dollar expand_dollar_t);

// ========================== EXPAND_DOLLAR ==========================

// -------------------------- ENVIRONMENT_VARIABLES --------------------------

int		get_var_name_length(char const *str, int index);
int		retrieve_var_name(char **var, char *str, int index_dollar, int size);

// -------------------------- EXPAND_DOLLAR --------------------------

int		expand_dollar(t_expand_new_content t_enc);

// --------------- ADD_ONE_ENVIRONMENT_VARIABLE_CHARACTER ---------------

int		add_one_env_var_char(char ***new_content, int *count,
			char env_var_char, char *flag);

// --------------------- EXPAND_ONE_ENVIRONMENT_VARIABLE ---------------------

int		expand_one_environment_variable(char ***new_content, int *count,
			char *flag, char *env_var);

// -------------------------- FT_ITOA_NO_MALLOC --------------------------

int		ft_nbrlen(int n);

void	ft_itoa_no_malloc(int n, char result[12]);

#endif

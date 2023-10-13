/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:51:07 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/13 13:44:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

// ========================== ENVIRONMENT ==========================

// -------------------------- ENVIRONMENT --------------------------

int		get_env_var_index(char **env, char *var);

char	**create_default_env(void);
char	**copy_env(char **old_env);
char	**extend_env(char **old_env, char *new_var);
char	**shorten_env(char **env, size_t index_var_to_delete);

#endif

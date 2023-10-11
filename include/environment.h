/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:51:07 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/11 20:56:12 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

char	**copy_env(char **old_env);
char	**extend_env(char **old_env, char *new_var);
char	**shorten_env(char **env, size_t index_var_to_delete);
char	**create_default_env(void);
int		get_env_var_index(char **env, char *var);

#endif

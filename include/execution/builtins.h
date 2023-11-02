/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 17:15:23 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

enum	e_bt_commands
{
	NOT_A_BT,
	BT_CD,
	BT_ECHO,
	BT_ENV,
	BT_EXIT,
	BT_EXPORT,
	BT_PWD,
	BT_UNSET,
};

// -------------------------- BUILTINS --------------------------

int	is_builtin(char *cmd);

int	builtins_cd(char **args, char **env);
int	builtins_echo(char **args);
int	builtins_exit(int code);
int	buitlins_pwd(char **args);
int	unset(char **env, char **args);
int	ft_export(char **env, char **args);
int	env(char **env);

#endif

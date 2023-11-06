/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/06 18:30:27 by aoberon          ###   ########.fr       */
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

// ========================== BUILTINS ==========================

// -------------------------- BUILTINS --------------------------

int	is_builtin(char *cmd);

// -------------------------- CD --------------------------

int	builtins_cd(char **args, char **env);

// -------------------------- ECHO --------------------------

int	builtins_echo(char **args);

// -------------------------- ENV --------------------------

int	env(char **env);

// -------------------------- EXIT --------------------------

int	builtins_exit(int code);

// -------------------------- EXPORT --------------------------

int	ft_export(char ***env, char **args);

// -------------------------- PWD --------------------------

int	buitlins_pwd(void);

// -------------------------- UNSET --------------------------

int	unset(char **env, char **args);



#endif

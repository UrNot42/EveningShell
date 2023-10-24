/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/24 18:50:47 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include "environment.h"

// ========================== PROMPT ==========================

void	prompt(char **envp);
// t_token	*parse_line(char *line);

// ========================= EXECUTION ========================

// int		execute(t_token *tokens, char **env);

typedef struct s_pipes	t_pipes;

struct s_pipes
{
	int	pids[1024];
	int	s[2];
	int	prev;
};

#endif

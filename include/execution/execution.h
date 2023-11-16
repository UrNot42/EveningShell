/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:22:12 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include "environment.h"
# include "exec_struct.h"
# include "files.h"
# include "here_doc.h"

# define PIP_ZERO 0b001
# define PIP_ONE  0b010
# define PIP_PREV 0b100
# define PIP_BOTH 0b011
# define PIP_ALL  0b111
# define PIP_READ 0b101

// ========================= INIT ========================

int		fill_cmds(t_compound *comp, t_cmd *cmd, t_file *file);
int		set_execute_struct(t_compound *comp, t_exec *ex, char ***env);
size_t	get_compound_type_size(t_compound *comp, bool is_cmd);
char	*ft_safe_strjoin(char *to_free_str, char *str_2);
int		create_cmd(t_cmd *cmd, char **env, char **n_cmd, char ***n_args);

// ========================= EXECUTION ========================

int		execute(t_compound *comp, char ***env, int last_err);
int		execute_builtin(t_exec *ex, int last_err, int i, int fd);
void	free_exec(t_exec *ex, bool env);
void	child_process(t_exec *exec, int i, int last_err);

int		close_pipe(t_pipe *pi, size_t code);

int		wait_pids(int *pids);

// ========================== SIGNAL ==========================

void	sig_handler_exec(int signum);
void	sig_handler_prompt(int signum);
void	sig_handler_heredoc(int signum);

#endif

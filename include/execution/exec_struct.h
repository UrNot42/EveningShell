/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:14:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/06 20:04:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

typedef struct s_exec	t_exec;
typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;
typedef struct s_file	t_file;

struct s_file
{
	bool	exists;
	int		type;
	int		fd;
	char	*name;
};

struct s_pipe
{
	int	*ds;
	int	pe[2];
	int	pe_prev;
};

struct s_cmd
{
	char	*cmd;
	char	**args;
	t_file	*in;
	t_file	*out;
};

struct s_exec
{
	int			cmd_size;
	int			pipe_size;
	int			file_size;
	t_pipe		pi;
	t_cmd		*cmd;
	t_file		*files;
	t_compound	*allocated_content;
	char		***env;
};

#endif

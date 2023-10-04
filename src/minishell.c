/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 09:59:34 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	printf("minishell :\n");
	if (argc == 1)
	{
		printf("No arguments.\n");
		return (1);
	}
	if (detect_echo(argc, argv))
		return (0);
	if (detect_cd(argv))
		return (0);
	if (detect_pwd(argv))
		return (0);
	else
	{
		printf("Not a builtins.\n");
		return (1);
	}
	return (0);
}

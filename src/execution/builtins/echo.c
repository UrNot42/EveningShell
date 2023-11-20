/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:28:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/20 17:01:45 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Detects if the option -n is present in the arguments
 * and returns the number of -n
 *
 * @param argv char ** of the arguments
 * @return int the number of -n
 */
static int	detect_option_n(char **argv)
{
	int	i;
	int	j;
	int	new_line;

	if (!argv || !argv[1] || argv[1][0] != '-'
		|| (argv[1][0] == '-' && argv[1][1] != 'n'))
		return (0);
	new_line = 0;
	i = 1;
	j = 0;
	while (argv[i] && argv[i][j] == '-' && argv[i][j + 1] == 'n')
	{
		j++;
		while (argv[i][j] == 'n')
			j++;
		if (!argv[i][j])
			new_line += 1;
		i++;
		j = 0;
	}
	return (new_line);
}

/**
 * @brief Builtins of the command echo
 *
 * @param args char ** of the arguments
 * @return int 0 in any case
 */
int	builtins_echo(char **args)
{
	int	i;
	int	new_line;

	new_line = detect_option_n(args);
	i = 1 + new_line;
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		++i;
	}
	if (!new_line)
		write(1, "\n", 1);
	return (0);
}

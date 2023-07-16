/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:09:13 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:22:56 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	exchange_pipes(char *str, char delimiter)
{
	while (*str && *str != delimiter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimiter)
	{
		if (*str == '|')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		exchange_pipes(str, delimiter);
}

static void	repair_pipes(char **args)
{
	char	*str;

	while (*args)
	{
		str = *args;
		while (*str)
		{
			if (*str == -1)
				*str = '|';
			str++;
		}
		args++;
	}
	return ;
}

char	**split_cmds(char *input)
{
	char	**cmd;

	exchange_pipes(input, '"');
	exchange_pipes(input, '\'');
	cmd = ft_split(input, '|');
	repair_pipes(cmd);
	return (cmd);
}

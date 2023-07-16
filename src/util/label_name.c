/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:57:44 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:36:38 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	name_end(char *name)
{
	int	end_name;

	end_name = 0;
	while (name[end_name] && !str_delimiter(name[end_name]))
	{
		if (name[end_name] == '\'')
		{
			move_forward(&name[end_name]);
			while (name[end_name] && name[end_name] != '\'')
				end_name++;
			move_forward(&name[end_name]);
		}
		else if (name[end_name] == '"')
		{
			move_forward(&name[end_name]);
			while (name[end_name] && name[end_name] != '"')
				end_name++;
			move_forward(&name[end_name]);
		}
		else if (name[end_name] && !str_delimiter(name[end_name]))
			end_name++;
	}
	return (end_name);
}

char	*label_name(char *direction_str)
{
	int		start_name;
	int		end_name;
	char	*name;
	char	*cmd_rest;

	start_name = 0;
	move_forward(direction_str);
	if (direction_str[start_name] == '>')
		move_forward(&direction_str[start_name]);
	while (direction_str[start_name] == ' '
		|| direction_str[start_name] == '\t')
		start_name++;
	end_name = name_end(&direction_str[start_name]);
	name = ft_substr(&direction_str[start_name], 0, end_name);
	cmd_rest = &direction_str[start_name + end_name];
	ft_memmove(direction_str, cmd_rest, ft_strlen(cmd_rest) + 2);
	return (name);
}

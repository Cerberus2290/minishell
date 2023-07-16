/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_ret.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:12:23 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:23:21 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*locate_exit_ret(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

static void	update_input(char **input, char *exit_ret, char *exit_second)
{
	char	*exit_first;
	char	*new_input;

	exit_first = ft_strjoin(*input, exit_ret);
	new_input = ft_strjoin(exit_first, exit_second);
	free(*input);
	free(exit_first);
	*input = new_input;
}

void	expand_exit_ret(char **input, int exit_ret)
{
	char	*exit_ret_pos;
	char	*exit_ret_str;

	exit_ret_pos = locate_exit_ret(*input);
	if (exit_ret_pos)
	{
		*exit_ret_pos = '\0';
		exit_ret_str = ft_itoa(exit_ret);
		update_input(input, exit_ret_str, (exit_ret_pos + 2));
		free(exit_ret_str);
		expand_exit_ret(input, exit_ret);
	}
}

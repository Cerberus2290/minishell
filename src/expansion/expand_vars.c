/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:17:37 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:24:08 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*locate_var_pos(char *input)
{
	while (*input)
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
				if (*input == '$' && ft_varname(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && ft_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

static void	update_input(char **input, char *var_value, char *var_second)
{
	char	*var_first;
	char	*new_input;

	if (!*input[0] && !var_value)
		var_first = ft_strdup("");
	else if (!*input[0] && var_value)
		var_first = ft_strdup(var_value);
	else if (!var_value)
		var_first = ft_strdup(*input);
	else
		var_first = ft_strjoin(*input, var_value);
	new_input = ft_strjoin(var_first, var_second);
	free(var_first);
	free(*input);
	*input = new_input;
}

void	expand_vars(char **input, t_enviro *envi)
{
	char	*var_pos;
	char	*var_name;
	char	*var_value;
	int		size_name;

	var_pos = locate_var_pos(*input);
	if (var_pos)
	{
		size_name = 0;
		while (ft_varname(var_pos[size_name + 1]))
			size_name++;
		var_name = ft_substr(var_pos, 1, size_name);
		*var_pos = '\0';
		var_value = envi_value(var_name, envi);
		update_input(input, var_value, (var_pos + 1 + size_name));
		free(var_name);
		expand_vars(input, envi);
	}
}

void	handle_expansions(char **input, t_enviro *envi, int exit_ret)
{
	expand_exit_ret(input, exit_ret);
	expand_vars(input, envi);
}

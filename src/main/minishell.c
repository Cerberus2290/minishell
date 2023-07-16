/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:46:54 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/16 08:56:45 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	minishell(t_enviro *envi)
{
	int		exit_ret;
	char	*input;
	char	**cmd;

	exit_ret = EXIT_SUCCESS;
	while (1)
	{
		main_signals();
		input = prompt_input(envi);
		if (input_error(input, &exit_ret, envi))
			continue ;
		handle_expansions(&input, envi, exit_ret);
		if (!str_pipe(input))
			exit_ret = exec_cmd(input, &envi);
		else
		{
			cmd = split_cmds(input);
			free(input);
			exit_ret = exec_cmds(cmd, &envi);
			array_free(cmd);
		}
	}
	return (exit_ret);
}

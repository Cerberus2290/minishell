/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:54:57 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:03 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_pipe(int og_fdout, char *curr_cmd, char **cmds)
{
	int			first_cmd;
	int			next_cmd;
	char		*last_command;
	static int	pipe_fds[2];

	last_command = cmds[array_len(cmds) - 1];
	first_cmd = (curr_cmd == cmds[0]);
	next_cmd = (curr_cmd != last_command);
	if (!first_cmd)
		direction_fd(pipe_fds[IN], STDIN_FILENO);
	if (next_cmd)
	{
		if (pipe(pipe_fds) == -1)
			print_perror_msg("pipe", curr_cmd);
		direction_fd(pipe_fds[OUT], STDOUT_FILENO);
	}
	else
		direction_fd(og_fdout, STDOUT_FILENO);
}

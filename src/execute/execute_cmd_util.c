/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:49:08 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:23 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	save_fdin(int og_fds[2])
{
	if (og_fds[IN] == NO_REDIRECT)
		og_fds[IN] = dup(STDIN_FILENO);
}

void	save_fdout(int og_fds[2])
{
	if (og_fds[OUT] == NO_REDIRECT)
		og_fds[OUT] = dup(STDOUT_FILENO);
}

int	handle_direction_in(char *cmd, int og_fds[2])
{
	save_fdin(og_fds);
	if (direction_input(cmd) == FAILED)
	{
		direction_fd(og_fds[IN], STDIN_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

int	handle_direction_out(char *cmd, int og_fds[2])
{
	save_fdout(og_fds);
	if (direction_output(cmd) == FAILED)
	{
		direction_fd(og_fds[OUT], STDOUT_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}

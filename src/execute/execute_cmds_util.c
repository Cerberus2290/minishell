/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:45:15 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:13 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	*init_child_pid(char **cmds)
{
	int		*children_pid;
	size_t	size;

	size = sizeof(int) * (array_len(cmds) + 1);
	children_pid = malloc(size);
	if (!children_pid)
		return (NULL);
	ft_bzero(children_pid, size);
	return (children_pid);
}

void	cleanup_execute(int *child_pid)
{
	kill_extra_fds();
	free(child_pid);
}

void	kill_child(char **cmds, t_enviro **envi)
{
	rl_clear_history();
	free_envi(envi);
	array_free(cmds);
	kill_fds();
	exit(EXIT_FAILURE);
}

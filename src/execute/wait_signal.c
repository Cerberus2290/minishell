/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:04:48 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:45:43 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	control_c(int status)
{
	return (WTERMSIG(status) == SIGINT);
}

static id_t	control_slash(int status)
{
	return (WTERMSIG(status) == SIGQUIT);
}

static int	handle_sig_int(int status, int last_child)
{
	if (control_c(status))
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (control_slash(status) && last_child)
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (INTERRUPT + WTERMSIG(status));
}

int	wait_on_child(int child_pid, int last_child)
{
	int	status;

	if (child_pid == FORK_ERROR)
		return (EXIT_FAILURE);
	if (waitpid(child_pid, &status, 0) == -1)
		print_perror_msg("waitpid", ft_itoa(child_pid));
	if (WIFSIGNALED(status))
		return (handle_sig_int(status, last_child));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_on_children(int children_pid[1024])
{
	int	i;
	int	exit_ret;
	int	last_child;

	i = 0;
	exit_ret = 0;
	while (children_pid[i] != 0)
	{
		last_child = children_pid[i + 1] == 0;
		exit_ret = wait_on_child(children_pid[i], last_child);
		i++;
	}
	cleanup_execute(children_pid);
	return (exit_ret);
}

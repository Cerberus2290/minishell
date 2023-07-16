/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:08:50 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/12 12:56:04 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	handle_directions(char *cmd, int og_fds[2])
{
	char	direction;

	og_fds[IN] = NO_REDIRECT;
	og_fds[OUT] = NO_REDIRECT;
	direction = get_next_direction(cmd);
	while (direction)
	{
		if (direction == '<')
		{
			if (!handle_direction_in(cmd, og_fds))
				return (FAILED);
		}
		if (direction == '>')
		{
			if (!handle_direction_out(cmd, og_fds))
				return (FAILED);
		}
		if (direction < 0)
		{
			save_fdin(og_fds);
			direction_heredoc(cmd, direction);
		}
		direction = get_next_direction(cmd);
	}
	return (SUCCESS);
}

static void	reset_fds(int og_fds[2])
{
	if (og_fds[IN] != NO_REDIRECT)
		direction_fd(og_fds[IN], STDIN_FILENO);
	if (og_fds[OUT] != NO_REDIRECT)
		direction_fd(og_fds[OUT], STDOUT_FILENO);
}

int	exec_bin_forked(char **args, t_enviro *envi)
{
	int		child_pid;
	char	*cmd;

	cmd = args[0];
	child_pid = fork();
	signals_execute(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", cmd);
	else if (child_pid == 0)
		exec_bin(args, envi);
	else
		return (wait_on_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}

int	exec_cmd(char *cmd, t_enviro **envi)
{
	char	**args;
	int		exit_ret;
	int		og_fds[2];

	if (!handle_directions(cmd, &og_fds[0]))
	{
		reset_fds(og_fds);
		free(cmd);
		return (EXIT_FAILURE);
	}
	args = split_args(cmd);
	free(cmd);
	if (is_builtin(args[0]))
		exit_ret = exec_builtin(args, envi);
	else
		exit_ret = exec_bin_forked(args, *envi);
	array_free(args);
	reset_fds(og_fds);
	return (exit_ret);
}

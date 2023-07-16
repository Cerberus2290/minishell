/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:28:22 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:18 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	save_fds(int og_fds[2])
{
	og_fds[0] = dup(STDIN_FILENO);
	og_fds[1] = dup(STDOUT_FILENO);
}

static void	handle_directions(char *cmd, char **cmds, t_enviro **envi)
{
	char	direction;

	direction = get_next_direction(cmd);
	while (direction)
	{
		if (direction == '<')
		{
			if (direction_input(cmd) == FAILED)
				kill_child(cmds, envi);
		}
		if (direction == '>')
		{
			if (direction_output(cmd) == FAILED)
				kill_child(cmds, envi);
		}
		if (direction < 0)
			direction_heredoc(cmd, direction);
		direction = get_next_direction(cmd);
	}
}

static void	exec_cmd_forked(char *cmd, char **cmds, t_enviro **envi)
{
	char	**args;

	kill_extra_fds();
	args = split_args(cmd);
	array_free(cmds);
	if (is_builtin(args[0]))
		exec_builtin_forked(args, envi);
	else
		exec_bin(args, *envi);
}

static void	reset_fds(int og_fds[2])
{
	direction_fd(og_fds[IN], STDIN_FILENO);
	direction_fd(og_fds[OUT], STDOUT_FILENO);
}

int	exec_cmds(char **cmds, t_enviro **envi)
{
	int	og_fds[2];
	int	*children_pid;
	int	i;

	save_fds(og_fds);
	children_pid = init_child_pid(cmds);
	i = 0;
	while (cmds[i])
	{
		handle_pipe(og_fds[OUT], cmds[i], cmds);
		children_pid[i] = fork();
		signals_execute(children_pid[i]);
		if (children_pid[i] == -1)
			print_perror_msg("fork", cmds[i]);
		else if (children_pid[i] == 0)
		{
			free(children_pid);
			handle_directions(cmds[i], cmds, envi);
			exec_cmd_forked(cmds[i], cmds, envi);
		}
		i++;
	}
	reset_fds(og_fds);
	return (wait_on_children(children_pid));
}

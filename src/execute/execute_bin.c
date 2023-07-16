/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:57:40 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:36 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	is_folder(char *cmd)
{
	struct stat	statbuff;

	if (stat(cmd, &statbuff) != 0)
		return (0);
	if (S_ISDIR(statbuff.st_mode))
	{
		if (*cmd == '.')
			cmd++;
		if (*cmd == '.')
			cmd++;
		if (*cmd == '/')
			return (TRUE);
	}
	return (FALSE);
}

static void	handle_execve_err(char **args, char *path, char **envip)
{
	int	error;

	error = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK) != 0)
		error = CMD_NOT_FOUND;
	else if (access(path, X_OK) != 0)
		error = NOT_EXECUTABLE;
	array_free(args);
	array_free(envip);
	free(path);
	exit(error);
}

void	bin_exit(char **args, t_enviro *envi, int exit_ret)
{
	if (exit_ret == NOT_EXECUTABLE)
		print_error_msg(args[0], NOT_EXECUTABLE_MSG);
	if (exit_ret == CMD_NOT_FOUND)
		print_error_msg(args[0], CMD_NOT_FOUND_MSG);
	rl_clear_history();
	free_envi(&envi);
	array_free(args);
	kill_fds();
	exit(exit_ret);
}

static int	envi_has_path(t_enviro *envi)
{
	return (envi_value("PATH", envi) != NULL);
}

int	exec_bin(char **args, t_enviro *envi)
{
	char	*path;
	char	*cmd;
	char	**envip;

	cmd = args[0];
	if (str_empty(cmd))
		bin_exit(args, envi, EXIT_SUCCESS);
	if (is_folder(cmd))
		bin_exit(args, envi, NOT_EXECUTABLE);
	path = find_path(cmd, envi);
	if (path == NULL && envi_has_path(envi))
		bin_exit(args, envi, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(cmd);
	rl_clear_history();
	kill_extra_fds();
	envip = envi_to_envip(envi);
	free_envi(&envi);
	if (execve(path, args, envip) == -1)
		handle_execve_err(args, path, envip);
	exit(EXIT_SUCCESS);
}

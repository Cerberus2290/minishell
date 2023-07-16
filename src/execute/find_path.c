/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:38:33 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:22:08 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	create_path(char root[], char *part1, char *part2, char *part3)
{
	*root = 0;
	ft_strlcat(root, part1, PATH_MAX);
	ft_strlcat(root, part2, PATH_MAX);
	ft_strlcat(root, part3, PATH_MAX);
}

static int	is_path(char *cmd)
{
	if (*cmd == '.')
		cmd++;
	if (*cmd == '.')
		cmd++;
	if (*cmd == '/')
		return (TRUE);
	return (FALSE);
}

static char	*local_path(char *cmd, t_enviro *envi)
{
	char	complete_path[PATH_MAX];

	if (*cmd == '/')
		return (ft_strdup(cmd));
	complete_path[0] = 0;
	create_path(complete_path, envi_value("PWD", envi), "/", cmd);
	return (ft_strdup(complete_path));
}

char	*find_path(char *cmd, t_enviro *envi)
{
	char	*path_env;
	char	**paths;
	char	current_path[PATH_MAX];
	char	**paths_start;

	if (is_path(cmd))
		return (local_path(cmd, envi));
	path_env = envi_value("PATH", envi);
	paths = ft_split(path_env, ':');
	paths_start = paths;
	while (paths && *paths)
	{
		create_path(current_path, *paths, "/", cmd);
		if (access(current_path, F_OK) == 0)
		{
			array_free(paths_start);
			return (ft_strdup(current_path));
		}
		paths++;
	}
	array_free(paths_start);
	return (NULL);
}

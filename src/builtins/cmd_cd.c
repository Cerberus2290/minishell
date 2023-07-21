/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:28:15 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/16 08:56:42 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cd_error(void)
{
	print_error_msg("cd", "too many arguments");
	return (EXIT_FAILURE);
}

int	ft_cd(char **args, t_enviro *envi)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (args[1] && args[2])
		return (cd_error());
	if (args[1] && !str_equal(args[1], "~"))
		path = args[1];
	else
		path = envi_value("HOME", envi);
	if (chdir(path) != 0)
	{
		print_perror_msg("cd", args[1]);
		return (EXIT_FAILURE);
	}
	pwd = envi_value("PWD", envi);
	oldpwd = envi_value("OLDPWD", envi);
	if (oldpwd && pwd && *pwd)
		update_envi("OLDPWD", pwd, envi);
	if (pwd && *pwd)
		update_envi("PWD", getcwd(cwd, PATH_MAX), envi);
	return (EXIT_SUCCESS);
}

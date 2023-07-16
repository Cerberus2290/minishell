/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:53:25 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/12 12:56:02 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_builtin_forked(char **args, t_enviro **envi)
{
	int	exit_ret;

	exit_ret = exec_builtin(args, envi);
	array_free(args);
	free_envi(envi);
	rl_clear_history();
	exit(exit_ret);
}

int	exec_builtin(char **args, t_enviro **envi)
{
	char	*cmd;

	cmd = args[0];
	if (str_equal(cmd, "echo"))
		return (ft_echo(args));
	if (str_equal(cmd, "pwd"))
		return (ft_pwd());
	if (str_equal(cmd, "env"))
		return (ft_env(*envi));
	if (str_equal(cmd, "export"))
		return (ft_export(args, envi));
	if (str_equal(cmd, "unset"))
		return (ft_unset(args, envi));
	if (str_equal(cmd, "cd"))
		return (ft_cd(args, *envi));
	if (str_equal(cmd, "exit"))
		return (minishell_exit(args, envi));
	else
		return (EXIT_FAILURE);
}

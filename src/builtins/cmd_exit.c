/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:36:41 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 16:04:29 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	fits_in_ll(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (0);
		out = out * 10 + c;
		str++;
	}
	return (1);
}

static void	check_args_error(char **args)
{
	char	*exit_status;

	if (!args || !args[1])
	{
		if (args)
			array_free(args);
		kill_fds();
		exit(EXIT_SUCCESS);
	}
	exit_status = args[1];
	if (!ft_atoll(exit_status))
	{
		array_free(args);
		exit_w_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (args[2] != NULL)
	{
		array_free(args);
		exit_w_error("exit", "too many arguments", EXIT_FAILURE);
	}
}

int	minishell_exit(char **args, t_enviro **envi)
{
	int	exit_status;

	rl_clear_history();
	free_envi(envi);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	check_args_error(args);
	kill_fds();
	exit_status = ft_atoll(args[1]);
	array_free(args);
	exit(exit_status);
}

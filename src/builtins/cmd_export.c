/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:40:03 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/10 18:09:52 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	declare_envi(t_enviro *envi)
{
	t_enviro	*aux;

	aux = envi;
	while (aux)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name_only(aux->value), STDOUT_FILENO);
		if (ft_strchr(aux->value, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value_only(aux->value), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		aux = aux->next;
	}
	return (0);
}

int	ft_export(char **args, t_enviro **envi)
{
	char	*value;
	char	*var_name;
	int		exit_ret;

	args++;
	exit_ret = EXIT_SUCCESS;
	if (!*args)
		return (declare_envi(*envi));
	while (*args)
	{
		value = *args;
		var_name = name_only(value);
		if (!valid_var_name(var_name) || str_equal(value, "="))
		{
			print_var_error("export", value);
			exit_ret = EXIT_FAILURE;
		}
		else if (envi_node(var_name, *envi))
			update_envi(var_name, value_only(value), *envi);
		else
			lst_enviro_append(value, envi);
		free(var_name);
		args++;
	}
	return (exit_ret);
}

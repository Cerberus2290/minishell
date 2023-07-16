/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:47:12 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/10 18:25:53 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	del_next_node(t_enviro **node)
{
	t_enviro	*temp;

	temp = (*node)->next;
	(*node)->next = ((*node)->next)->next;
	free(temp->value);
	free(temp);
}

static void	remove_from_envi(char *var_name, t_enviro **envi)
{
	t_enviro	*aux;

	aux = *envi;
	while (aux && aux->next)
	{
		if (ft_strncmp((aux->next)->value, var_name, ft_strlen(var_name)) == 0)
		{
			if ((aux->next)->value[ft_strlen(var_name)] == '=')
				return (del_next_node(&aux));
		}
		aux = aux->next;
	}
}

int	ft_unset(char **args, t_enviro **envi)
{
	char	*var_name;
	int		exit_ret;

	args++;
	exit_ret = EXIT_SUCCESS;
	if (!*args)
		return (0);
	while (*args)
	{
		var_name = *args;
		if (!valid_var_name(var_name))
		{
			print_var_error("unset", var_name);
			exit_ret = EXIT_FAILURE;
		}
		else
			remove_from_envi(var_name, envi);
		args++;
	}
	return (exit_ret);
}

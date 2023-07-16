/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:35:05 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/07 08:50:34 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_enviro *envi)
{
	t_enviro	*aux;

	aux = envi;
	while (aux)
	{
		if (ft_strchr(aux->value, '='))
		{
			ft_putstr_fd(aux->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		aux = aux->next;
	}
	return (0);
}

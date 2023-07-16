/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:34:44 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/16 08:56:33 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*envi_value(char *name, t_enviro *envi)
{
	t_enviro	*aux;

	aux = envi_node(name, envi);
	if (!aux)
		return (NULL);
	return (value_only(aux->value));
}

t_enviro	*envi_node(char *name, t_enviro *envi)
{
	t_enviro	*aux;
	int			size;

	aux = envi;
	size = ft_strlen(name);
	while (aux)
	{
		if (ft_strncmp(name, aux->value, size) == 0)
		{
			if (aux->value[size] == '=')
				return (aux);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	update_envi(char *name, char *value, t_enviro *envi)
{
	t_enviro	*aux;
	char		*new_value;

	if (value == NULL)
		return (get_cwd_fix(envi));
	aux = envi_node(name, envi);
	if (!aux)
	{
		new_value = create_value(name, value);
		lst_enviro_append(new_value, &envi);
		free(new_value);
		return ;
	}
	free(aux->value);
	create_envi_value(name, value, aux);
}

size_t	envi_size(t_enviro *envi)
{
	size_t		size;
	t_enviro	*aux;

	size = 0;
	aux = envi;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

char	**envi_to_envip(t_enviro *envi)
{
	char		**envip;
	t_enviro	*aux;
	int			i;

	envip = malloc(sizeof(char *) * (envi_size(envi) + 1));
	aux = envi;
	i = 0;
	while (aux)
	{
		envip[i] = ft_strdup(aux->value);
		i++;
		aux = aux->next;
	}
	envip[i] = NULL;
	return (envip);
}

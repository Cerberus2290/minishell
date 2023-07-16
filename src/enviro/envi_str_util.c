/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envi_str_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:42:42 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/15 15:55:29 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*name_only(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i])
		i++;
	return (ft_substr(value, 0, i));
}

char	*value_only(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '=' && value[i])
		i++;
	if (!value[i])
		return (NULL);
	return (&value[i + 1]);
}

char	*create_value(char *name, char *value)
{
	char	*value_two;
	int		value_size;
	int		i;

	value_size = ft_strlen(name) + ft_strlen(value) + 2;
	value_two = malloc(value_size * sizeof(char));
	i = 0;
	while (*name)
		value_two[i++] = *name++;
	value_two[i++] = '=';
	while (*value)
		value_two[i++] = *value++;
	value_two[i] = '\0';
	return (value);
}

void	free_envi(t_enviro **envi)
{
	t_enviro	*aux;
	t_enviro	*next;

	aux = *envi;
	while (aux)
	{
		free(aux->value);
		next = aux->next;
		free(aux);
		aux = next;
	}
	envi = NULL;
}

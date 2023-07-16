/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:36:57 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/16 08:56:28 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (*array)
	{
		len++;
		array++;
	}
	return (len);
}

void	get_cwd_fix(t_enviro *env)
{
	char	**helper;

	helper = ft_split("cd ..", ' ');
	ft_cd(helper, env);
	ft_putstr_fd("cd: cannot access parent directory\n", STDERR_FILENO);
	array_free(helper);
}

void	create_envi_value(char *name, char *value, t_enviro *aux)
{
	int		size;
	int		i;
	char	*new_value;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	new_value = malloc(size * sizeof(char));
	i = 0;
	while (*name)
		new_value[i++] = *name++;
	new_value[i++] = '=';
	while (*value)
		new_value[i++] = *value++;
	new_value[i] = '\0';
	aux->value = new_value;
}

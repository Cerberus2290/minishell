/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:29:44 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/15 15:41:13 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	incr_shlvl(t_enviro **envi)
{
	t_enviro	*shlvl_node;
	int			shlvl;
	char		*new_value;
	char		*shlvl_value;
	char		*new_shlvl;

	shlvl_node = envi_node("SHLVL", *envi);
	if (shlvl_node)
	{
		shlvl = ft_atoi(ft_strchr(shlvl_node->value, '=') + 1) + 1;
		new_value = ft_itoa(shlvl);
		new_shlvl = ft_strjoin("SHLVL=", new_value);
		free(new_value);
		free(shlvl_node->value);
		shlvl_node->value = new_shlvl;
	}
	else
	{
		shlvl_value = ft_itoa(1);
		lst_enviro_append(ft_strjoin("SHLVL=", shlvl_value), envi);
		free(shlvl_value);
	}
}

t_enviro	*init_envi(char **envip)
{
	t_enviro	*lst;
	int			i;

	lst = NULL;
	i = 0;
	while (envip[i])
	{
		lst_enviro_append(envip[i], &lst);
		i++;
	}
	if (!envi_node("OLDPWD", lst))
		lst_enviro_append("OLDPWD", &lst);
	incr_shlvl(&lst);
	return (lst);
}

void	lst_enviro_append(char *value, t_enviro **lst)
{
	struct s_enviro	*new_node;
	struct s_enviro	*aux_node;

	new_node = malloc(sizeof(struct s_enviro));
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	aux_node = *lst;
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new_node;
}

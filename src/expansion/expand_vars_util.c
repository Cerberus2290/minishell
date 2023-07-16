/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:24:52 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:25:14 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	valid_var_name(char *var)
{
	if (!ft_isalpha(*var))
		return (FALSE);
	while (*var)
	{
		if (!ft_varname(*var))
			return (FALSE);
		var++;
	}
	return (TRUE);
}

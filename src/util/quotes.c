/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:18:36 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:46:35 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	ft_error(void)
{
	ft_putstr_fd("minishell: open quotes detected - abort", STDERR_FILENO);
	return (1);
}

int	quotes(char *str)
{
	char	opened_last;

	opened_last = 0;
	while (*str && !opened_last)
	{
		if (*str == '\'' || *str == '"')
			opened_last = *str;
		str++;
	}
	while (*str && opened_last)
	{
		if (*str && *str == opened_last)
			opened_last = 0;
		str++;
	}
	if (*str)
		return (quotes(str));
	else if (!opened_last)
		return (0);
	else
		return (ft_error());
}

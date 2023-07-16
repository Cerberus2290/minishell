/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:41:26 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:37:06 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	str_equal(const char *s1, const char *s2)
{
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1);
	if (size != ft_strlen(s2))
		return (0);
	return (ft_strncmp(s1, s2, size) == 0);
}

void	move_forward(char *str)
{
	ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

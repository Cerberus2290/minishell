/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:25:31 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:07:40 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (str_equal(cmd, "echo"))
		return (1);
	if (str_equal(cmd, "cd"))
		return (1);
	if (str_equal(cmd, "pwd"))
		return (1);
	if (str_equal(cmd, "export"))
		return (1);
	if (str_equal(cmd, "unset"))
		return (1);
	if (str_equal(cmd, "env"))
		return (1);
	if (str_equal(cmd, "exit"))
		return (1);
	return (0);
}

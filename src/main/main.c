/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:42:50 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/15 15:10:28 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	main(int argc, char **argv, char **envip)
{
	if (argv && argc > 1)
	{
		ft_putstr_fd("Minishell does not require "
			"any arguments - it just is ✋\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (minishell(init_envi(envip)));
}

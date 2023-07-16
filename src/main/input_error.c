/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:35:50 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:23:03 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	input_error(char *input, int *exit_ret, t_enviro *envi)
{
	int	result;

	result = FALSE;
	if (str_empty(input))
		result = TRUE;
	else if (quotes(input))
		result = TRUE;
	else if (syntax_check(input))
	{
		*exit_ret = 2;
		result = TRUE;
	}
	else if (handle_heredoc(input, exit_ret, envi) == FAILED)
		result = TRUE;
	if (result == TRUE)
		free(input);
	return (result);
}

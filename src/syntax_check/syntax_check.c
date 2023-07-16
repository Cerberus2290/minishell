/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:24:00 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:22:58 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pipe_start(char *input)
{
	if (input[0] == '|')
		return (syntax_error("|"));
	return (FALSE);
}

int	direction_no_label(char *input)
{
	char	*direction_pos;
	char	next_direction;

	next_direction = get_next_direction(input);
	direction_pos = get_direction_position(input, next_direction);
	if (!direction_pos)
		return (FALSE);
	if (direction_pos[0] == '<' && direction_pos[1] == '<')
		direction_pos++;
	else if (direction_pos[0] == '>' && direction_pos[1] == '>')
		direction_pos++;
	direction_pos++;
	while (*direction_pos == ' ' || *direction_pos == '\t')
		direction_pos++;
	if (*direction_pos == '\0')
		return (syntax_error("newline"));
	if (invalid_token(*direction_pos))
		return (unexpected_token(direction_pos));
	return (direction_no_label(direction_pos));
}

int	empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = find_next_pipe(input);
	if (!next_pipe)
		return (FALSE);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
		return (syntax_error("|"));
	return (empty_pipe(next_pipe));
}

int	syntax_check(char *input)
{
	if (pipe_start(input))
		return (TRUE);
	if (direction_no_label(input))
		return (TRUE);
	if (empty_pipe(input))
		return (TRUE);
	return (FALSE);
}

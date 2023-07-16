/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:42:41 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:09:04 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	direction_input(char *cmd)
{
	char	*input_direction;
	char	*file_name;
	int		fd;

	input_direction = get_direction_position(cmd, '<');
	if (!input_direction)
		return (SUCCESS);
	file_name = label_name(input_direction);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		direction_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}

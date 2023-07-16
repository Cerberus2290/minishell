/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:30:59 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:09:12 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	direction_output(char *cmd)
{
	char	*output_direction;
	char	*file_name;
	int		fd;
	int		open_flags;

	output_direction = get_direction_position(cmd, '>');
	if (!output_direction)
		return (SUCCESS);
	if (output_direction[1] == '>')
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = label_name(output_direction);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		direction_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (SUCCESS);
}

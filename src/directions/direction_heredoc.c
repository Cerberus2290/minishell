/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:59:21 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:08:49 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*temp_filename(int heredoc_num)
{
	char	filename[30];
	char	*num_str;

	ft_bzero(filename, 30);
	num_str = ft_itoa(heredoc_num);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, num_str, 30);
	free(num_str);
	return (ft_strdup(filename));
}

void	direction_heredoc(char *cmd, int heredoc_num)
{
	char	*filename;
	int		fd_tmp_file;
	char	*heredoc_pos;

	filename = temp_filename(heredoc_num);
	fd_tmp_file = open(filename, O_RDONLY);
	if (fd_tmp_file == -1)
	{
		print_error_msg("open", filename);
		free(filename);
		return ;
	}
	free(filename);
	direction_fd(fd_tmp_file, STDIN_FILENO);
	heredoc_pos = get_direction_position(cmd, heredoc_num);
	move_forward(heredoc_pos);
}

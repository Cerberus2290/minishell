/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:50:52 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:35:38 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	kill_extra_fds(void)
{
	int	last_fd;

	last_fd = open("/tmp/last_fd", O_RDWR | O_CREAT, 0666);
	if (last_fd == -1)
		print_perror_msg("open", "/tmp/last_fd");
	while (last_fd > STDERR_FILENO)
	{
		close(last_fd);
		last_fd--;
	}
}

void	kill_fds(void)
{
	kill_extra_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

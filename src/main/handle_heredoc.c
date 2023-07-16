/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:01:07 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:01:07 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*heredoc_position(char *str)
{
	while (*str && str[1])
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*tmp_filename(int heredoc_num)
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

void	read_heredoc(int *exit_ret, t_enviro *envi, char *delimiter,
				int heredoc_num)
{
	char	*line;
	char	*filename;
	int		fd_tmpfile;

	filename = tmp_filename(heredoc_num);
	fd_tmpfile = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	line = readline("heredoc> ");
	while (line && !str_equal(line, delimiter))
	{
		expand_exit_ret(&line, *exit_ret);
		expand_vars(&line, envi);
		ft_putstr_fd(line, fd_tmpfile);
		ft_putchar_fd('\n', fd_tmpfile);
		free(line);
		line = readline("> ");
	}
	if (!line)
		print_error_msg("warning: heredoc delimited by EOF. Wanted", delimiter);
	free(line);
	close(fd_tmpfile);
	free(delimiter);
	free_envi(&envi);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	exec_heredoc(char *delimiter, int heredoc_num, int *exit_ret,
					t_enviro *envi)
{
	int	child_pid;

	child_pid = fork();
	signals_heredoc(child_pid);
	if (child_pid == -1)
		print_error_msg("fork - heredoc_prompt", delimiter);
	else if (child_pid == 0)
		read_heredoc(exit_ret, envi, delimiter, heredoc_num);
	else
	{
		*exit_ret = wait_on_child(child_pid, TRUE);
		main_signals();
		if (*exit_ret != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}

int	handle_heredoc(char *input, int *exit_ret, t_enviro *envi)
{
	static int	heredoc_num;
	char		*heredoc_pos;
	char		*delimiter;

	heredoc_num = -1;
	heredoc_pos = heredoc_position(input);
	if (!heredoc_pos)
		return (SUCCESS);
	heredoc_num--;
	*heredoc_pos = heredoc_num;
	heredoc_pos++;
	delimiter = label_name(heredoc_pos);
	if (!exec_heredoc(delimiter, heredoc_num, exit_ret, envi))
	{
		free(delimiter);
		return (FAILED);
	}
	free(delimiter);
	return (handle_heredoc(input, exit_ret, envi));
}

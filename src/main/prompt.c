/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:54:49 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 17:22:55 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*prompt_str(t_enviro *envi)
{
	char		*user;
	char		*cwd;
	char		*dir;
	static char	prompt[PATH_MAX];

	user = envi_value("USER", envi);
	if (!user)
		user = "UNKNOWN";
	cwd = envi_value("PWD", envi);
	if (!cwd)
		cwd = "UNKNOWN";
	dir = ft_strrchr(cwd, '/') + 1;
	if (ft_strncmp(cwd, "/", 2) == 0)
		dir = "ROOT";
	ft_bzero(prompt, sizeof(prompt));
	ft_strlcat(prompt, user, PATH_MAX);
	ft_strlcat(prompt, "  ", PATH_MAX);
	ft_strlcat(prompt, dir, PATH_MAX);
	ft_strlcat(prompt, " ✅ minishell ➡\uFE0F", PATH_MAX);
	return (prompt);
}

char	*prompt_input(t_enviro *envi)
{
	char	*input;

	input = readline(prompt_str(envi));
	if (!input)
		minishell_exit(NULL, &envi);
	if (input && *input)
		add_history(input);
	return (input);
}

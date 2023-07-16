/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:58:07 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/11 15:45:22 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	remove_spaces(char *str, char delimeter)
{
	while (*str && *str != delimeter)
		str++;
	if (*str)
		str++;
	while (*str && *str != delimeter)
	{
		if (*str == ' ')
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		remove_spaces(str, delimeter);
}

static void	reset_spaces(char **arg)
{
	char	*str;

	while (*arg)
	{
		str = *arg;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		arg++;
	}
	return ;
}

static int	has_quotemark(char *str)
{
	if (!str)
		return (0);
	while (str && *str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	del_quotemarks(char *str)
{
	char	open_last;

	open_last = 0;
	while (*str && !open_last)
	{
		if (*str == '\'' || *str == '"')
		{
			open_last = *str;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	while (*str && open_last)
	{
		if (*str && *str == open_last)
		{
			open_last = 0;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	if (*str)
		return (del_quotemarks(str));
}

char	**split_args(char *cmd)
{
	char	**args;

	if (!has_quotemark(cmd))
		return (ft_split(cmd, ' '));
	remove_spaces(cmd, '"');
	remove_spaces(cmd, '\'');
	del_quotemarks(cmd);
	args = ft_split(cmd, ' ');
	reset_spaces(args);
	return (args);
}

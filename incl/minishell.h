/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstrassb <tstrassb@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:20:11 by tstrassb          #+#    #+#             */
/*   Updated: 2023/07/16 08:56:39 by tstrassb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"// libft
# include <stdio.h>// perror
# include <readline/readline.h>// readline
# include <readline/history.h>// history
# include <stdlib.h>// getenv
# include <unistd.h>// getpwd
# include <sys/wait.h>// waitpid
# include <sys/stat.h>// stat
# include <signal.h>// sigaction
# include <fcntl.h>// open flags

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0

# define NO_REDIRECT -1

// Error_Defines

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "is a directory"

// Execute_Defines

# define IN 0
# define OUT 1

// struct Environment

typedef struct s_enviro
{
	char			*value;
	struct s_enviro	*next;
}				t_enviro;

// src/builtins

int			is_builtin(char *cmd);
int			ft_cd(char **args, t_enviro *envi);
int			ft_echo(char **args);
int			ft_env(t_enviro *envi);
int			minishell_exit(char **args, t_enviro **envi);
int			ft_export(char **args, t_enviro **envi);
int			ft_pwd(void);
int			ft_unset(char **args, t_enviro **envi);

// src/execute

int			exec_builtin_forked(char **args, t_enviro **envi);
int			exec_builtin(char **args, t_enviro **envi);
int			exec_bin(char **args, t_enviro *envi);
int			exec_bin_forked(char **args, t_enviro *envi);
int			exec_cmd(char *cmd, t_enviro **envi);
int			exec_cmds(char **cmds, t_enviro **envi);
char		*find_path(char *cmd, t_enviro *envi);
int			*init_child_pid(char **cmds);
void		cleanup_execute(int *child_pid);
void		kill_child(char **cmds, t_enviro **envi);
void		save_fdin(int og_fds[2]);
void		save_fdout(int og_fds[2]);
int			handle_direction_in(char *cmd, int og_fds[2]);
int			handle_direction_out(char *cmd, int og_fds[2]);
void		handle_pipe(int og_fdout, char *curr_cmd, char **cmds);
char		**split_args(char *cmd);
int			wait_on_child(int child_pid, int last_child);
int			wait_on_children(int children_pid[1024]);

// src/expansion

void		expand_exit_ret(char **input, int exit_ret);
void		expand_vars(char **input, t_enviro *envi);
void		handle_expansions(char **input, t_enviro *envi, int exit_ret);
int			ft_varname(char c);
int			valid_var_name(char *var);

// src/enviro

t_enviro	*init_envi(char **envip);
void		lst_enviro_append(char *value, t_enviro **lst);
char		*envi_value(char *name, t_enviro *envi);
t_enviro	*envi_node(char *name, t_enviro *envi);
void		update_envi(char *name, char *value, t_enviro *envi);
size_t		envi_size(t_enviro *envi);
char		**envi_to_envip(t_enviro *envi);
char		*name_only(char *value);
char		*value_only(char *value);
char		*create_value(char *name, char *value);
void		free_envi(t_enviro **envi);

// src/directions

char		*get_direction_position(char *str, char direct_char);
char		get_next_direction(char *str);
void		direction_fd(int fd_direction, int fd_location);
int			direction_output(char *cmd);
int			direction_input(char *cmd);
void		direction_heredoc(char *cmd, int heredoc_num);

// src/main

char		*heredoc_position(char *str);
void		read_heredoc(int *exit_ret, t_enviro *envi, char *delimiter,
				int heredoc_num);
int			exec_heredoc(char *delimiter, int heredoc_num, int *exit_ret,
				t_enviro *envi);
int			handle_heredoc(char *input, int *exit_ret, t_enviro *envi);
int			input_error(char *input, int *exit_ret, t_enviro *envi);
int			minishell(t_enviro *envi);
char		*prompt_str(t_enviro *envi);
char		*prompt_input(t_enviro *envi);
char		**split_cmds(char *input);

// src/syntax_check

int			invalid_token(char token);
int			unexpected_token(char *input);
int			syntax_error(char *token);
char		*find_next_pipe(char *str);
int			pipe_start(char *input);
int			direction_no_label(char *input);
int			empty_pipe(char *input);
int			syntax_check(char *input);

// src/util

int			array_len(char **array);
void		print_error_msg(char *cmd, char *msg);
void		exit_w_error(char *cmd, char *msg, int error);
void		print_perror_msg(char *cmd, char *p_msg);
void		print_var_error(char *cmd, char *var);
void		kill_extra_fds(void);
void		kill_fds(void);
void		array_free(char **array);
long long	ft_atoll(const char *str);
char		*label_name(char *direction_str);
int			quotes(char *str);
void		main_signals(void);
void		signals_execute(int child_pid);
void		signals_heredoc(int child_pid);
int			str_empty(char *str);
int			is_quote(char c);
int			str_pipe(char *str);
int			str_delimiter(char c);
int			str_equal(const char *s1, const char *s2);
void		move_forward(char *str);
void		get_cwd_fix(t_enviro *env);
void		create_envi_value(char *name, char *value, t_enviro *aux);

#endif
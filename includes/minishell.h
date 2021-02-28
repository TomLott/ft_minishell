/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:22 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/28 14:04:53 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

typedef enum
{
	DEF,
	CD,
	ECHO,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	SELF,
	ALL
}	t_cmd;

typedef enum
{
	E_DEF,
	E_EXIT,
	E_FD,
	E_MALLOC,
	E_NO_LINE,
	E_PIPE,
	E_READ,
	E_SYNTAX,
	E_EXIT_ARG
}	t_err;

typedef struct		s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}					t_envlst;

typedef struct		s_args
{
	t_cmd			cmd;
	int				redir;
	char			**args;
	void			*next;
}					t_args;

typedef struct		s_pipi
{
	char			*cmd;
	char			**args;
	int				fd0;
	int				fd1;
	int				exists;
	struct s_pipi	*next;
}					t_pipi;

typedef struct		s_redir
{
	int				redir;
	char			*cont;
	struct s_redir	*next;
}					t_redir;

int					g_f[3];
int					g_ex_code;

typedef struct		s_all
{
	char			**env;
	char			**loc_env;
	char			*line;
	t_cmd			cmd;
	char			*arg;
	int				redir;
	int				cmd_len;
	int				pipe;
	t_list			*grbg;
	t_err			err;
	t_args			args;
	t_redir			*l_red;
	int				last_rv;
	int				dollar;
	char			*def_cmd;
	int				fd1;
	int				fd0;
	int				fd1_def;
	int				fd0_def;
	char			*exec;
	int				exit_code;
}					t_all;

char				**arr_append(char **arr, char *to_add);
int					arr_len(char **arr);
void				check_and_add(char	***env, char *to_add);
int					check_key(char **arr, char *key);
int					check_nodes(t_pipi *pipi);
char				*concat_path_exec(char *dir, char *exec);
int					convert_dol_question(t_all *all, char *line, int *i);
char				**copy_env(char **env);
void				do_error(t_all *all);
void				do_malloc(t_all *all, void **p, t_cmd type);
int					do_pipe(t_all *all, t_pipi *pp);
void				env_add_back(t_all *all, char *env);
char				*extract_env(char **env, char *key);
int					file_exists(char *file_path);
int					fill_pipes(t_all *all, t_pipi *pipi);
void				free_arr(void **arr, int size);
void				free_double_char(char ***arr);
void				free_env(t_envlst **env);
void				free_pipi(t_pipi **pp);
int					ft_allowed_chars(char c);
int					ft_dollar(t_all *all, char *line);
char				*ft_com_parser(char *line, t_all *all, char *temp);
int					ft_change_pipes(t_all *all, char *line);
int					ft_change_redir(t_all *all, char **line);
int					ft_check_redir(char *line, t_all *all);
void				ft_init_env(char **env, t_all *all);
int					ft_fd(t_all *all);
char				*ft_not_line(char c);
int					ft_parse_argument(char *line, t_all *all, t_args *args);
int					ft_parse_dollar(t_all *all, char *line, int *i);
int					ft_parse_line(char *line);
void				ft_print_capt(int fd, int fl);
char				*ft_realloc_r(char *str, char c);
char				*ft_quotes_deleting(char *str, t_all *all);
int					func_do_trick(char **args, t_all *all);
void				get_command(char *s, t_all *all);
int					get_flag(char *line, int *i, char c);
int					get_key_value(char *str, char **key, char **value);
int					get_next_line(int fd, char **line);
int					get_path(t_all *all, char *path, char *ex_name);
void				init_all(t_all **all);
void				init_obj(void **p, t_cmd type);
int					inside_quotes(char *str, char *end, char c);
int					is_any_quote(char c);
int					is_export(t_all *all);
char				*line_cleaner(char *line, t_all *all, char *temp);
int					manage_cmds(t_all *all);
int					manage_execve(t_all *all, char *bin, char **args);
int					ms_cd(t_all *all);
int					ms_def(t_all *all);
int					ms_echo(t_all *all);
int					ms_env(t_all *all);
int					ms_exit(t_all *all);
int					ms_export(t_all *all);
int					ms_pwd(void);
int					ms_self(t_all *all);
int					ms_unset(t_all *all);
void				myint(int sig);
void				parse_env(char *env, char **key, char **value);
char				**pop_str(char **arr, char *key);
void				pipi_add_back(t_pipi **lst, t_pipi *p_new);
t_pipi				*pipi_new(t_all *all);
int					print_empty_export(char **env);
void				process_tilda(t_all *all);
int					process_quotes(char **str);
void				refresh_all(t_all **all, t_args *args);
char				*str_swap(char *str, char *old, int len, char *new_str);
void				set_old_pwd(t_all *all);
void				set_pwd(t_all *all);
int					t_parse_commands(t_all *all, char *line);

#endif

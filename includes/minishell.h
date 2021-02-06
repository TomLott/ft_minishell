/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:22 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/06 21:24:05 by jmogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>

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
    E_MALLOC,
    E_NO_LINE,
    E_SYNERR
}   t_err;

typedef struct		s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}					t_envlst;

typedef struct      s_args
{
    t_cmd           cmd;
    int             redir; /** 1 is '>'; 2 is ">>"; 3 is '<'*/
    char            *src;
    char            *dst;
    t_list          *args;
    void            *next;
}                   t_args;

typedef struct		s_all
{
	t_envlst		*env;
	char			*line;
	t_cmd			cmd;
	char			*arg;
    int				redir;
    int				cmd_len;
    int				pipe;
	t_list			*grbg;
	t_err           err;
	t_list			*args;
}					t_all;

void				do_error(t_all *all);
void				do_malloc(t_all *all, void **p, t_cmd type);
char				*ft_com_parser(char *line, t_all *all);
void				ft_init_env(char **env, t_all *all);
int                 ft_parse_argument(char *line, t_all *all, t_args *args);
int					ft_parse_line(char *line);
void				ft_print_capt(int fd);
void				get_command(char *s, t_all *all);
int                 get_flag(char *line, int *i, char c);
int					get_next_line(int fd, char **line);
void				init_obj(void **p, t_cmd type);
void				manage_cmds(t_all *all);
void				ms_env(t_all *all);
void				ms_unset(t_all *all);
void				parse_argument(char *com, t_all *all);
void				parse_env(char *env, char **key, char **value);
void				refresh_all(t_all **all);
int					t_parse_commands(t_all *all, char *line);

#endif

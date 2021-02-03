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
    EXIT
}               t_cmd;


typedef struct s_all
{
    char **env;
    char *line;
    t_cmd cmd;
    char *arg;
}               t_all;

int				get_next_line(int fd, char **line);
void            ft_print_capt(int fd);
void            refresh_all(t_all **all);
void            get_command(char *s, int *i, t_all *all);
char            *ft_com_parser(char *line);
char            **parse_arguments(char *arg, t_all *all);
int             t_parse_commands(t_all *all, char *line);
int             ft_parse_line(char *line);

#endif

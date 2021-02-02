#ifndef FT_MINISHELL_MINISHELL_H
# define FT_MINISHELL_MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef enum
{
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

#endif

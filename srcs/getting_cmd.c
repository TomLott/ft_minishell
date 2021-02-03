#include "../includes/minishell.h"

char        *ft_com_parser(char *line)
{
    char *temp;
    int i;
    int j;

    i = 0;
    j = 0;
    temp = malloc(1000);

    while(line[i] && line[i] != ' ')
    {
        if (line[i] == '\\' && line[i + 1] && ++i)
            temp[j++] = line[i++];
        else if (line[i] == '\"' && ++i)
            while (line[i] && line[i] != '\"')
                temp[j++] = line[i++];
        else if (line[i] == '\'' && ++i)
            while (line[i] && line[i] != '\'')
                temp[j++] = line[i++];
        else
            temp[j++] = line[i++];
        if (line[i] == '\'' || line[i] == '\"')
            i++;
    }
    temp[j] = '\0';
    return (temp);
}


void        get_command(char *s, int *i, t_all *all)
{
    char *temp;

    temp = ft_com_parser(s);
    printf("finished com - |%s|\n", temp);
    if (!ft_strncmp(temp, "pwd", 3) && (*i = 3))
        all->cmd = PWD;
    else if (!ft_strncmp(temp, "cd", 2) && (*i = 2))
        all->cmd = CD;
    else if (!ft_strncmp(temp, "echo", 4) && (*i = 4))
        all->cmd = ECHO;
    else if (!ft_strncmp(temp, "export", 6) && (*i = 6))
        all->cmd = EXPORT;
    else if (!ft_strncmp(temp, "unset", 5) && (*i = 5))
        all->cmd = UNSET;
    else if (!ft_strncmp(temp, "env", 3) && (*i = 3))
        all->cmd = ENV;
    else if (!ft_strncmp(temp, "exit", 4) && (*i = 4))
        all->cmd = EXIT;
    else if (!ft_strncmp(temp, "minishell", 9) && (*i = 9))
        all->cmd = SELF;
    else
        all->cmd = DEF;
}

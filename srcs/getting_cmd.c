#include "minishell.h"

int         ft_check_redir(char *line, t_all *all)
{
  //  printf("%c - char\n", line[all->cmd_len]);
    if (line[all->cmd_len] == '>')
    {
        if (line[all->cmd_len + 1] == '>')
            all->redir = 2;
        else
            all->redir = 1;
        all->cmd_len += all->redir;
    }
    else if (line[all->cmd_len] == '<')
    {
        all->redir = -1;
        all->cmd_len++;
    }
    else if (line[all->cmd_len] == '|')
    {
        all->pipe = 1;
        all->cmd_len++;
        return (1);
    }
    return (all->redir);
}


char        *ft_com_parser(char *line, t_all *all)
{
    char *temp;
    int j;

    j = 0;
    temp = malloc(1000);
  //  printf("%d\n", all->cmd_len);
  //  printf("%s - line\n", line);
    while(line[all->cmd_len] && line[all->cmd_len] != ' ')
    {
        if (line[all->cmd_len] == '\\' && line[all->cmd_len + 1] && ++all->cmd_len)
            temp[j++] = line[all->cmd_len++];
        else if (line[all->cmd_len] == '\"' && ++all->cmd_len)
        {
            while (line[all->cmd_len] && line[all->cmd_len] != '\"')
            {
                //printf("%c - char in quotes\n", line[all->cmd_len]);
                temp[j++] = line[all->cmd_len++];
            }
            (line[all->cmd_len] == '\"') ? all->cmd_len++ : 1;
        }
        else if (line[all->cmd_len] == '\'' && ++all->cmd_len)
        {
            while (line[all->cmd_len] && line[all->cmd_len] != '\'')
                temp[j++] = line[all->cmd_len++];
            (line[all->cmd_len] == '\'') ? all->cmd_len++ : 1;
        }
        else if (ft_check_redir(line, all) && ++j)
        {
            (all->redir == 2) ? j++ : 1;
            break;
        }
        else
            temp[j++] = line[all->cmd_len++];
        
       // printf("end of cycle\n");
    }
    temp[j] = '\0';
    return (temp);
}


void        get_command(char *s, int *i, t_all *all)
{
    char *temp;

    temp = ft_com_parser(s, all);
   // printf("finished com - %s\npipi = %d\n", temp, all->pipe);
    if (!ft_strcmp(temp, "pwd") && (*i = 3))
        all->cmd = PWD;
    else if (!ft_strcmp(temp, "cd") && (*i = 2))
        all->cmd = CD;
    else if (!ft_strcmp(temp, "echo") && (*i = 4))
        all->cmd = ECHO;
    else if (!ft_strcmp(temp, "export") && (*i = 6))
        all->cmd = EXPORT;
    else if (!ft_strcmp(temp, "unset") && (*i = 5))
        all->cmd = UNSET;
    else if (!ft_strcmp(temp, "env") && (*i = 3))
        all->cmd = ENV;
    else if (!ft_strcmp(temp, "exit") && (*i = 4))
        all->cmd = EXIT;
    else if (!ft_strcmp(temp, "minishell") && (*i = 9))
        all->cmd = SELF;
    else
        all->cmd = DEF;
}

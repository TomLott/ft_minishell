#include "minishell.h"

void        ft_redirect_parse(t_args *args, char *line)
{
    int i;
    t_args *tmp;
    char *terminat;

    tmp = args;
    terminat = line;
    i = 0;
    while(*line && (*line != -1 && *line != -2 && *line != -3))
        line++;
    if (*line == -3)
        line++;
    *line = '\0';
    line++;
    args->src = (ft_strtrim(ft_strtrim(ft_strdup(terminat), "\""), "\'"));
    args->dst = (ft_strtrim(ft_strtrim(ft_strdup(line), "\""), "\'"));
    while(args->dst[i] && args->dst[i] != ' ')
        i++;
    free(terminat);
    terminat = args->dst;
    args->dst[i] = '\0';
    args->dst = ft_strdup(args->dst + i + 1);
    free(terminat);
}

void        ft_do_list(char **line, t_args *args)
{
    int     i;
    t_list  *tmp;

    i = 1;
    args->args = malloc(sizeof(t_list));
    tmp = args->args;
    tmp->content = line[0];
    tmp->next = NULL;
    while(line[i])
    {
        ft_lstadd_back(&tmp,ft_lstnew(line[i]));
        i++;
    }
}

int         ft_parse_argument(char *line, t_all *all, t_args *args)
{
    int i;
    int flag;
    char **temp;

    i = 0;
    flag = 0;
    if (!line)
        return (1);
    if (ft_strrchr(line, -1) || ft_strrchr(line, -2) || ft_strchr(line, -3))
        ft_redirect_parse(args, line);
    else
    {
        while (line[i]) {
            if (line[i] == '\'' && (flag = 1))
                flag = get_flag(line, &i, '\'');
            else if (line[i] && line[i] == '\"' && (flag = 1))
                flag = get_flag(line, &i, '\"');
            if ((line[i] && line[i] == '\0') || flag == 1)
                return (-1); /** syntax error*/
            if (line[i] == ' ')
                line[i] = -1;
            i++;
        }
        temp = ft_split(line, -1);
        ft_do_list(temp, args);
    }
    return (1);
}


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
    int flag;

    j = 0;
    temp = malloc(1000);
    while(line[all->cmd_len] && line[all->cmd_len] != ' ')
    {
        if (line[all->cmd_len] == '\\' && line[all->cmd_len + 1] && ++all->cmd_len)
            temp[j++] = line[all->cmd_len++];
        else if (line[all->cmd_len] == '\"' && ++all->cmd_len)
        {
            while (line[all->cmd_len] && line[all->cmd_len] != '\"')
                temp[j++] = line[all->cmd_len++];

            (line[all->cmd_len] == '\"') ? all->cmd_len++ : (flag = -1);
        }
        else if (line[all->cmd_len] == '\'' && ++all->cmd_len)
        {
            while (line[all->cmd_len] && line[all->cmd_len] != '\'')
                temp[j++] = line[all->cmd_len++];
            (line[all->cmd_len] == '\'') ? all->cmd_len++ : (flag = -1);
        }
        else if (ft_check_redir(line, all) && ++j)
        {
            (all->redir == 2) ? j++ : 1;
            break;
        }
        else
            temp[j++] = line[all->cmd_len++];
    }
    temp[j] = '\0';
    return (flag == -1 ) ? NULL : temp;
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

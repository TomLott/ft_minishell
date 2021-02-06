#include "minishell.h"

void        ft_redirect_parse(t_args *args, char *line, t_all *all)
{
    int i;
    char *terminat;


    if (all->redir != 0)
    {
        args->dst = ft_strtrim(ft_strdup(line), " ");
        printf("here is dest %s\n", args->dst);
        return ;
    }
    terminat = line;
    i = 0;
    while(*line && (*line != -1 && *line != -2 && *line != -3))
        line++;
    *line = '\0';
    if (*line == -3)
    {
        line++;
        *line = '\0';
    }
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
    args->dst = NULL;
    args->src = NULL;
    if (!line)
        return (1);
    if (all->redir || ft_strrchr(line, -1) || ft_strrchr(line, -2) || ft_strchr(line, -3))
        ft_redirect_parse(args, line, all);
    else
    {
        while (line[i]) {
            if (line[i] == '\'' && (flag = 1))
                flag = get_flag(line, &i, '\'');
            else if (line[i] && line[i] == '\"' && (flag = 1))
                flag = get_flag(line, &i, '\"');
            if ((line[i] && line[i] == '\0') || flag == 1)
                return (1); /** syntax error*/
            if (line[i] == ' ')
                line[i] = -1;
            i++;
        }
        temp = ft_split(line, -1);
        ft_do_list(temp, args);
    }
    return (0);
}


int         ft_check_redir(char *line, t_all *all)
{
  //  printf("%c - char\n", line[all->cmd_len]);
    if (line[all->cmd_len] == -3)
    {
        if (line[all->cmd_len + 1] == -3)
        {
            all->redir = 2;
            all->cmd_len += 2;
        }
    }
    else if (line[all->cmd_len] == -1)
    {
        all->redir = 1;
        all->cmd_len++;
    }
    else if (line[all->cmd_len] == -2)
    {
        all->redir = 3;
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
   // if (line[0] == '$')
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
    return (flag == -1 ) ? "a" : temp;
}

void        get_command(char *s, t_all *all)
{
    char *temp;

    temp = ft_com_parser(s, all);
	if (ft_strcmp(temp, "pwd"))
        all->cmd = PWD;
    else if (ft_strcmp(temp, "cd"))
        all->cmd = CD;
    else if (ft_strcmp(temp, "echo"))
        all->cmd = ECHO;
    else if (ft_strcmp(temp, "export"))
        all->cmd = EXPORT;
    else if (ft_strcmp(temp, "unset"))
        all->cmd = UNSET;
    else if (ft_strcmp(temp, "env"))
        all->cmd = ENV;
    else if (ft_strcmp(temp, "exit"))
        all->cmd = EXIT;
    else if (ft_strcmp(temp, "minishell"))
        all->cmd = SELF;
	else
		all->cmd = DEF;
}

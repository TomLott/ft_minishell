#include "minishell.h"

void ft_redir_after_command(t_all *all, t_args *args, char *line)
{
    int     i;
    char    *terminat;

    i = 0;
    terminat = line;
    line = ft_strtrim(line, " ");
    free(terminat);
    while (line[i] && line[i] != ' ')
        i++;
    line[i] = '\0';
    i++;
    args->dst = ft_strdup(line);
    all->arg = ft_strdup(line + i);
}

char *do_wise_trim(char *line)
{
    char *temp;
    char *new_line;

    temp = line;
    new_line = ft_strdup(line);
   //e free(temp);
    temp = new_line;
    new_line = ft_strtrim((new_line), " ");
    free(temp);
    temp = new_line;
    new_line = ft_strtrim((new_line), "\'");
    free(temp);
    temp = new_line;
    new_line = ft_strtrim((new_line), "\"");
    free(temp);
    //ft_strtrim((ft_strtrim(ft_strtrim(ft_strdup(terminat), "\""), "\'")), " ");
    return (new_line);
}

void        ft_redirect_parse(t_args *args, char *line, t_all *all)
{
    int i;
    char *terminat;

    if (all->redir != 0)
    {
        ft_redir_after_command(all, args, line);
        return ;
    }
    terminat = line;
    i = 0;
    while(*line && (*line != -1 && *line != -2 && *line != -3))
        line++;
    *line = '\0';
    if (*line == -3 && ++line)
        *line = '\0';
    line++;
    args->src = ft_strtrim(terminat, " ");
    args->dst = ft_strtrim(line, " ");
    while(args->dst[i] && args->dst[i] != ' ')
        i++;
    free(terminat);
    terminat = args->dst;
    args->dst[i++] = '\0';
    all->arg = ft_strdup(args->dst + i);
    args->dst = ft_strdup(args->dst);
    //free(terminat);
}

t_redir	*ft_lstnew_r(void *content, int redir)
{
	t_redir	*ans;

	if (0x0 == (ans = malloc(sizeof(t_redir))))
		return (0x0);
    ans->redir = redir;
	ans->next = 0x0;
	ans->cont = content;
	return (ans);
}

void	ft_lstadd_back_r(t_redir **lst, t_redir *new)
{
	t_redir	*prev;

	if (*lst == 0x0)
	{
		*lst = new;
		return ;
	}
	prev = *lst;
	while (prev->next)
		prev = prev->next;
	prev->next = new;
}

/*
void        ft_redirect_parse(t_args *args, char *line, t_all *all)
{
    int i;
    char *terminat;

    printf("here we are now %s\n", line);

    if (all->redir != 0)
        ft_lstadd_back_r(&all->l_red, ft_lstnew_r(NULL, all->redir));
    while (1)
    {
        terminat = line;
        i = 0;
        while(*line && (*line != -1 && *line != -2 && *line != -3))
            line++;
        if (*line)
    }
    *line = '\0';
    if (*line == -3 && ++line)
        *line = '\0';
    line++;
    args->src = ft_strtrim(terminat, " ");
    args->dst = ft_strtrim(line, " ");
    while(args->dst[i] && args->dst[i] != ' ')
        i++;
    free(terminat);
    terminat = args->dst;
    args->dst[i++] = '\0';
    all->arg = ft_strdup(args->dst + i);
    args->dst = ft_strdup(args->dst);
    //free(terminat);
}*/

int         ft_parse_argument(char *line, t_all *all, t_args *args)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (!line)
        return (1);
    if (all->redir || ft_strrchr(line, -1) || ft_strrchr(line, -2) || ft_strchr(line, -3))
    {
        ft_redirect_parse(args, line, all);
        line = all->arg;
	//	printf("line is %s\n", line);
    }
 //   line = char	*line_cleaner(all->arg);
    while (line[i])
    {
        if (line[i] == '\'' && (flag = 1))
            flag = get_flag(line, &i, '\'');
        else if (line[i] && line[i] == '\"' && (flag = 1))
            flag = get_flag(line, &i, '\"');
        if ((line[i] && line[i] == '\0') || flag == 1)
            return (1); /** syntax error*/
        if (line[i] == ' ')
            line[i] = -5;
        i++;
    }
 //   printf("here is line %s\n", line);
 //   printf("here is line GOSHA ! WHAT IS HERE?! %s\n", line);
	all->args.args = ft_split(line, -5);
    //ft_do_list(temp, args);
    return (0);
}


int         ft_check_redir(char *line, t_all *all)
{
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
    temp = malloc(4096);
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

int			ft_strlen_for_arg(char *line)
{
    int		j;
	int		i;
    int		flag;

    j = 0;
	i = 0;
    while(line && line[i] && line[i] != ' ')
    {
        if (line[i] == '\\' && line[i + 1] && ++i)
            j++;
        else if (line[i] == '\"' && ++i)
        {
            while (line[i] && line[i++] != '\"')
                j++;
            (line[i] == '\"') ? i++ : (flag = -1);
        }
        else if (line[i] == '\'' && ++i)
        {
            while (line[i] && line[i++] != '\'')
                j++;
            (line[i] == '\'') ? i++ : (flag = -1);
        }
        else
		{
			i++;
            j++;
		}
		if (flag == -1)
		{
			j = 0;
			break ;
		}
    }
    return (j);
}

char        *ft_quotes_deleting(char *line, t_all *all)
{
    char	*temp;
    int		j;
	int		i;
    int		flag;

    j = 0;
    i = 0;
    temp = malloc(ft_strlen_for_arg(line));
    while(line && line[i] && line[i] != ' ')
    {
        if (line[i] == '\\' && line[i + 1] && ++i)
            temp[j++] = line[i++];
        else if (line[i] == '\"' && ++i)
        {
            while (line[i] && line[i] != '\"')
                temp[j++] = line[i++];
            (line[i] == '\"') ? i++ : (flag = -1);
        }
        else if (line[i] == '\'' && ++i)
        {
            while (line[i] && line[i] != '\'')
                temp[j++] = line[i++];
            (line[i] == '\'') ? i++ : (flag = -1);
        }
        else if (ft_check_redir(line, all) && ++j)
        {
            (all->redir == 2) ? j++ : 1;
            break;
        }
        else
            temp[j++] = line[i++];
    }
    temp[j] = '\0';
    return (flag == -1 ) ? "z" : temp;
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
	{
        all->def_cmd = ft_strdup(temp);
        all->cmd = DEF;
    }
	free(temp);
}

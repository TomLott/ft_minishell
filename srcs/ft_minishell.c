#include "minishell.h"

//int main(int ar, char **argv)
//{
//    pid_t pid = fork();
//    srand(getpid());
//    int t = rand()%4;
//    printf("sleep time=%d pid=%d\n", t, pid);
//    sleep(t);
//    printf("fork() return %d\n", pid);
//
//}

void ft_init_env(char **env, t_all *all)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    all->env = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while(env[i])
    {
        //all->env[i] = ft_strdup(env[i]);
        i++;
    }
    all->env[i] = NULL;
}

void myint(int sig) {
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        ft_print_capt(1);
        signal(SIGINT, myint);
    }
}

int get_flag(char *line, int *i, char c)
{
    int flag;

    flag = 1;
    printf("get_flag\n");
    (*i)++;
    while (line[(*i)] != c && line[*i + 1])
    {
        (*i)++;
    }
    if (line[(*i)] == c)
        return (0);
    return (1);
}

int ft_parse_line(char *line)
{
    int i;
    int flag;

    i = 0;
    flag = 0;

    while (line[i])
    {
        printf("%s\n", line);
        if (line[i] == '\'' && (flag = 1))
            flag = get_flag(line, &i, '\'');
        else if (line[i] && line[i] == '\"' && (flag = 1))
            flag = get_flag(line, &i, '\"');
        if ((line[i] && line[i] == '\0' ) || flag == 1)
            return (-1); /** syntax error*/
        if (line[i] == ';')
            line[i] = -1; /** we change semicolons to (-1) by ASCII to split commands by (-1) */
        i++;
    }
    return (1);
}

t_cmd *get_command(char *s, int *i)
{
    if (!ft_strncmp(s, "pwd ", 4))
        return (ft_strdup("pwd"));
    else if (!ft_strncmp(s, "cd", 2))
        return (ft_strdup("cd"));
    else if (!ft_strncmp(s, "echo ", 5))
        return (ft_strdup("echo"));
    else if (!ft_strncmp(s, "export ", 7))
        return (ft_strdup("export "));
    else if (!ft_strncmp(s, "unset", 5))
        return (ft_strdup("unset"));
    else if (!ft_strncmp(s, "env ", 4))
        return (ft_strdup("env"));
    else if (!ft_strncmp(s, "exit", 4))
        return (ft_strdup("exit"));
    else
        return (NULL);
}


char *hook_command(char *com, t_all *all)
{
    char *argument;
    int i;

    i = 0;
    if (!(all->cmd = get_command(com, &i)))
        return (NULL);
    argument = ft_strdup(com + ft_strlen(all->cmd));
    printf("%s - command\n,%s - argument\n", all->cmd, argument);
    return(argument);
}

int ft_parse_commands(t_all *all, char *line)
{
    char **commands;
    int i;
    int flag;

    i = 0;
    if (ft_parse_line(all->line) == -1)
        printf("ERROR\n");
    commands = ft_split(all->line, -1);
    while(commands[i])
    {
        commands[i] = ft_strtrim(commands[i], " ");
        all->arg = hook_command(commands[i], all);
        free(commands[i]);
        i++;
    }
    free(commands);
    return (1);
}


void get_data(t_all *all)
{

    //get_next_line(0, &all->line); 
    all->line = ft_strdup("echo \"hello;world\""); /*use for test commands. Remove after*/
    ft_parse_commands(all, all->line);
    //free(line);
}

int main(int argc, char **argv, char **env)
{
    t_all *all;

    all = (t_all *)malloc(sizeof(t_all));
    ft_init_env(env, all);
    while(1)
    {
        ft_print_capt(1);
        signal(SIGINT, myint);
        get_data(all);
        break; /*remove*/
    }

}

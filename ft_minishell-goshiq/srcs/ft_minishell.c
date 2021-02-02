#include "../includes/minishell.h"

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

char **parse_argument(char *arg)
{
    char **temp;

    /**тут нужно заменить все пробелы между ковычками*/
}

void hook_command(char *com, t_all *all)
{
    int i;
    char **temp;

    i = 0;
    get_command(com, &i, all);
    if (i + 1 < ft_strlen(com))
        all->arg = ft_strdup(com + i + 1);
    temp = parse_argument(all->arg);
    printf("%u - command\n%s - argument\n", all->cmd, all->arg);
}

int ft_parse_commands(t_all *all, char *line)
{
    char **commands;
    int i;
    int flag;
    char *temp;

    i = 0;
    if (ft_parse_line(all->line) == -1)
        printf("ERROR\n");
    commands = ft_split(all->line, -1);
    while(commands[i])
    {
        refresh_all(&all);
        temp = commands[i];
        commands[i] = ft_strtrim(commands[i], " ");
        hook_command(commands[i], all);
        free(temp);
        i++;
    }
    free(commands);
    return (1);
}


void get_data(t_all *all)
{

    get_next_line(0, &all->line); 
    //all->line = ft_strdup("echo \"hello;world\""); /*use for test commands. Remove after*/
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

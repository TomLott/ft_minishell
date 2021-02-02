#include "../includes/minishell.h"

char        **parse_arguments(char *arg, t_all *all)
{
    char **temp;
    char *for_free;

    for_free = all->arg;
    ft_parse_line(all->arg, ' ');
    free(for_free);
    temp = ft_split(all->arg, -1);
    int i = 0;
    while(temp[i])
    {
        printf("temp - %s\n", temp[i]);
        i++;
    }
    return (temp);


    /**тут нужно заменить все пробелы между ковычками*/
    
}
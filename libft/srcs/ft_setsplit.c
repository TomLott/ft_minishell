#include "libft.h"

static size_t ft_counter(const char *s, char *set)
{
    size_t count;

    count = 0;
    while(*s)
    {
        if (!(ft_strchr(set, *s)))
            count++;
        while (!ft_strchr(set, *s) && *(s + 1))
            s++;
        s++;
    }
    return (count);
}

static size_t strlen_split(const char *s, char *set)
{
    size_t i;

    i = 0;
    while (!ft_strchr(set, *s) && *s)
    {
        s++;
        i++;
    }
    return (i);
}

static void ft_free_sp(char **s)
{
    int i;

    i = 0;
    while(s[i])
    {
        free(s[i]);
        s[i] = NULL;
        i++;
    }
    free(s);
    s = NULL;
}

char **ft_setsplit(const char *s, char *set)
{
    char **split;
    size_t i;
    size_t j;
    size_t k;

    if (!s)
        return (NULL);
    printf("hihi\n");
    i = ft_counter(s, set);
    if (!(split = (char **)malloc(sizeof(char *) * (i + 1))))
        return (NULL);
    j = 0;
    k = 0;
    printf("im here\n");
    while (j < i)
    {
        printf("haha\n");
        if (!(split[j] = (char *)malloc(sizeof(char *) * (strlen_split(&s[k], set) + 1))))
            ft_free_sp(split);
        while (ft_strchr(set, s[k]))
            k++;
        ft_strlcpy(split[j], &s[k], strlen_split(&s[k], set) + 1);
        while (!ft_strchr(set, s[k]) && s[k])
            k++;
        j++;
    }
    split[j] = NULL;
    printf("done\n");
    return (split);
}
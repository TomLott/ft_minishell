#include <stdio.h>
#include <stdlib.h>

char *ft_parser(char *line)
{
     char *temp;
     int i;
     int j;

    i = 0;
    j = 0;
    temp = malloc(1000);

    printf("%s\n", line);
    while(line[i] && line[i] != ' ')
    {
        if (line[i] == '\\' && line[i + 1] && ++i)
        {
            printf("%d %c\n", i, line[i]);
            temp[j++] = line[i++];}
        if (line[i] == '\"' && ++i)
            while (line[i] && line[i] != '\"')
                temp[j++] = line[i++];
        else
            temp[j++] = line[i++];
    }
    temp[j] = '\0';
    return (temp);
    // while (line[i] && line[i] != ' ')
    // {
    //     if (line[i] == '\"' && ++i)
    //         while (line[i] && (line[i] != '\"' && line[i - 1] != '\\'))
    //         {
    //             printf("first %c %d\n", line[i], i);
    //             temp[j++] = line[i++];}
    //     else
    //     {
    //         temp[j++] = line[i++];
    //     }
        
    // }
    // temp[j] = '\0';
    // return (temp);
}

int main(int argc, char **argv)
{
    printf("%s\n", ft_parser(argv[1])); 
}
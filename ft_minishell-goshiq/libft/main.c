#include <stdio.h>

char **ft_setsplit(const char *s, char *set);

int main()
{
	char **split;
	char *s1 = "hello;world";
	int i = 0;
	
	split = ft_setsplit(s1, ";");
	while(split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

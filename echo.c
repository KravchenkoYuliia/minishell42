#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return 0;
	while (str[i])
		i++;
	return i;
}

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t                  i;
        unsigned char   *str1;
        unsigned char   *str2;

        i = 0;
        str1 = (unsigned char *)s1;
        str2 = (unsigned char *)s2;
        if (n == 0)
                return (0);
        while (i < n - 1 && str1[i] == str2[i] && str1[i] && str2[i])
                i++;
        return (str1[i] - str2[i]);
}


void	ft_echo(char** argv)
{
	int i = 1;
	int start = 1;
	if (ft_strncmp(argv[i], "-n", 3) == 0)
		start = 2;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-n", 3) == 0)
			i++;
		if (i != start)
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3) != 0)
		printf("\n");
}


int main()
{
	char *argv[5] = {"echo", "Bonjour", "Hello", "TEST",  NULL};
	
	if (ft_strncmp("echo", argv[0], ft_strlen("echo") + 1) == 0)
		ft_echo(argv);

	return 0;	
}

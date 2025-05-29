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

// 0 -> not_option (print) / 1 -> option (ignore)
int	ft_is_option(char* arg)
{
	int i = 1;

	if (arg[0] != '-')
		return 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}



int	ft_echo(char** argv)
{
	int n_flag = 0;
	int i = 1;
	
	if (!argv[i])
		printf("\n");
	while (ft_is_option(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}


int main()
{
	char *args[11] = {"echo",  "-n",  "-n",  "-nnnnnnnnnnnnnnnn",  "-nbla",  "Hello",  "Bonjour",  "-nn",  " -n",  "end", NULL};
	if (ft_strncmp("echo", args[0] , ft_strlen("echo") + 1) == 0)
	{
		if ((ft_echo(args)) != 0)
			printf("Error\n");
	}

	return 0;	
}

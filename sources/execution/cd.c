#include <stdio.h>
#include <unistd.h>



int     ft_strncmp(char *s1, char *s2, size_t n)
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

char*	ft_get_home_path(char** env)
{
	int	i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_cd(char* directory, char** env)
{
	int	i;
       
	if (!directory)
	{
		directory = ft_get_home_path(env);
		printf("%s\n", directory);
		i = chdir(directory);
		printf("%d\n", i);
		if (i != 0)
			return -1;
	}
	i = chdir(directory);
	if (i != 0)
		return -1;
	return 0;
}

int main(int ac, char** av, char** env)
{

	if (ac < 2)
		return 0;
	if (ft_strncmp(av[1], "cd", 3) == 0)
	{
		if (av[2] == NULL)
		{
			ft_cd(av[2], env);
				return 0;
		}
		if (av[3] != NULL)
		{
			printf("babyshell: %s: too many arguments\n", av[1]);
			return 0;
		}
		ft_cd(av[2], env);
	}

}

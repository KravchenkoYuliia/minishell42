#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int	ft_check_quotes(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
			i++;
	}
	return (0);
}

int	ft_check_if_quote_closed(char* line)
{
	int i = 0;
	int q = 0;
	while (line[i])
	{
		if (line[i] == 34)
			q++;
		i++;
	}
	return (q);
}

void	ft_handle_quotes(char* line)
{
	int	i = ft_check_if_quote_closed(line);
	if (i % 2 == 0)
		printf("Good, we can work with it\n");
	else
		printf("Error. Code stops here\n");
}

int main()
{
	char* line = readline("babyshell: ");

	int i = ft_check_quotes(line);
	if (i == 1)
		ft_handle_quotes(line);
	if (i == 0)
		printf("NO quotes\n");
}

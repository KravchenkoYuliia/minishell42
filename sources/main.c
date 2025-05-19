
#include "minishell.h"


static bool	ft_check_unclosed_quotes(char *str)
{
	int 	i;
	int		sp;
	int		db;

	i = 0;
	sp = 0;
	db = 0;
	while (str[i])
	{
		if (str[i] == 39 && db == 0)
			sp++;
		else if (str[i] == 34 && sp == 0)
			db++;
		if (sp % 2 == 0)
			sp = 0;
		if ( db % 2 == 0)
			db = 0;
		i++;
	}
	if (sp % 2 != 0 || db % 2 != 0)
		return (false);
	return (true);
}
static 


int main(int ac, char **av)
{
	char* line;
	(void)av;

	if (ac != 1)
		return(0);
	printf("%s\n", getenv("PATH"));
	while (1)
	{
		line = readline("babyshell: ");
		if (!ft_check_unclosed_quotes(line))
			return (1);
		
		free(line);
	}
	return (0);
}

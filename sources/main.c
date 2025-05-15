
#include "minishell.h"


bool	ft_check_quotes(char *str)
{
	int 	i;
	t_quote	quote;

	i = 0;
	quote.sp = 0;
	quote.db = 0;
	while (str[i])
	{
		if ((str[i] == 34 && quote.sp != 0) || (str[i] == 39 && quote.db != 0))
			return (false);
		if (str[i] == 39)
			quote.sp++;
		else if (str[i] == 34)
			quote.db++;
		i++;
	}
	if (quote.sp % 2 != 0 || quote.db % 2 != 0)
		return (false);
	return (true);
}

int main()
{
	char* line;
	
	while (1)
	{
		line = readline("babyshell: ");
		if (ft_check_quotes(line))
			printf ("All is good my dood\n");
		else
			printf("quotes no good ouinouin\n");
		if (line[0] == 'C')
			exit(EXIT_SUCCESS);
		free(line);
	}
	return (0);
}

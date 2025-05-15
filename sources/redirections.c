/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:27 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/15 16:33:01 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>






//#include "minishell.h"

void	ft_redirect_input(char *infile)
{
	int	fd;

	if (access(infile, R_OK) == -1)
	{
		printf("babyshell: infile: No such file or directory\n");
		//free tout
		exit(EXIT_FAILURE);
	}
	if (access(infile, X_OK) == -1)
	{
		printf("babyshell: infile: Permission denied\n");
		//free tout
		exit(EXIT_FAILURE);
	}
	if ((fd = open(infile, O_RDONLY)) == -1)
	{
		//tout free;
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int main()
{
        ft_redirect_input("infile");
        printf("test\n");
}


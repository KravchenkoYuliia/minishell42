/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 13:22:51 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_std_fileno(t_minishell *shell)
{
	dup2(shell->save_stdin, STDIN_FILENO);
	dup2(shell->save_stdout, STDOUT_FILENO);
	close(shell->save_stdin);
	close(shell->save_stdout);
}

void	ft_write_stdout(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

int	ft_charset(char *str, char c)
{
	int	i;

	i = 0 ;
	while (str[i])
	{
		if (str[i] == c)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

char	*ft_add_str2(char *line, char *str2, int i)
{
	int	j;

	j = 0;
	while (str2[j])
	{
		if (j != 0 && str2[j - 1] == '=')
			break ;
		line[i] = str2[j];
		i++;
		j++;
	}
	line[i] = '\"';
	i++;
	while (str2[j])
	{
		line[i] = str2[j];
		i++;
		j++;
	}
	line[i] = '\"';
	i++;
	line[i] = '\0';
	return (line);
}

char	*ft_strjoin_export(char *str1, char *str2)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = ft_strlen(str1) + ft_strlen(str2) + 3;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	while (str1[i])
	{
		line[i] = str1[i];
		i++;
	}
	line[i] = '\0';
	line = ft_add_str2(line, str2, i);
	return (line);
}

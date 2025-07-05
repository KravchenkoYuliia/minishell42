/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 07:57:40 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 16:04:02 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_expand(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*line;

	i = 0;
	j = 0;
	len = ft_strlen(str) + 2;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
	{
		free(str);
		return (NULL);
	}
	if (str)
	{
		while (str && str[i])
		{
			line[i] = str[i];
			i++;
		}
		free(str);
	}
	line[i] = c;
	i++;
	line[i] = '\0';
	return (line);
}

char    *ft_strjoin_expand_str(char *s1, char *s2)
{
        int             i;
        int             j;
        int             len;
        char    *history;

        i = 0;
        j = 0;
        len = ft_strlen(s1) + ft_strlen(s2) + 1;
        history = (char *)malloc(sizeof(char) * len);
        if (!history)
	{
		free(s1);
		free(s2);
                return (NULL);
	}
        ft_strcpy(history, s1);
        i = ft_strlen(history);
        free(s1);
        if (s2)
        {
                while (s2[j])
                {
                        history[i] = s2[j];
                        i++;
                        j++;
                }
		//free(s2);
        }
        history[i] = '\0';
        return (history);
}

char	*ft_get_result(char *expand_me, int start, char *result)
{
	while (expand_me[start])
	{
		result = ft_strjoin_expand(result, expand_me[start]);
		start++;
	}
	return (result);
}

char	*ft_getenv_variable(char *expand_me, int start)
{
	int		i;
	char	*temp;
	char	*expanded;
	char	*result;

	i = 0;
	temp = NULL;
	expanded = NULL;
	result = NULL;
	while (expand_me[start] && ft_isalnum(expand_me[start]))
	{
		temp = ft_strjoin_expand(temp, expand_me[start]);
		start++;
	}
	expanded = getenv(temp);
	free(temp);
	result = ft_strjoin_expand_str(result, expanded);
	if (result && start < ft_strlen(expand_me))
		result = ft_get_result(expand_me, start, result);
	//free(expand_me);
	return (result);
}


char	*ft_expand_line_heredoc(t_minishell *shell, char *expand_me)
{
	int		i;
	char	*line;

	i = 0;
	(void)shell;
	line = NULL;
	if (expand_me[0] != '$')
	{
		while (expand_me[i] && expand_me[i] != '$')
		{
			line = ft_strjoin_expand(line, expand_me[i]);
			if (!line)
				return (NULL);
			i++;
		}
	}
	if (expand_me[i] == '$')
	{
		line = ft_strjoin_heredoc(line, ft_getenv_variable(expand_me, i + 1));
		if (!line)
			return (NULL);
	}
	else
		line[ft_strlen(line)] = '\0';
	free(expand_me);
	return (line);
}

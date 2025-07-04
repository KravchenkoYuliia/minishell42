/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 07:57:40 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/04 19:41:38 by yukravch         ###   ########.fr       */
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
	result = ft_strjoin_heredoc(result, expanded);
	if (result && start < ft_strlen(expand_me))
	{
		result = ft_get_result(expand_me, start, result);
		free(expand_me);
	}
	return (result);
}

char	*ft_unquote_lim_heredoc(t_minishell *shell, char *limiter)
{
	shell->quote_lim = ft_quote_or_not_quote(limiter);
	if (shell->quote_lim == true)
		limiter = ft_unquote_limiter(limiter);
	return (limiter);
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
			i++;
		}
	}
	if (expand_me[i] == '$')
		line = ft_strjoin_heredoc(line, ft_getenv_variable(expand_me, i + 1));
	else
		line[ft_strlen(line)] = '\0';
	return (line);
}

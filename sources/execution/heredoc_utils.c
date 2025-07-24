/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:22:46 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 14:54:33 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*history;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	history = (char *)malloc(sizeof(char) * len);
	if (!history)
		return (NULL);
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
	}
	history[i] = '\0';
	return (history);
}

char	*ft_name_the_heredoc_file(t_minishell *shell, int index)
{
	int		i;
	char	*name;
	char	*path;

	i = 0;
	(void)index;
	(void)shell;
	while (i < INT_MAX)
	{
		name = ft_itoa(i);
		path = ft_strjoin("../temp/", name);
		if (access(path, F_OK) == -1)
		{
			free(name);
			return (path);
		}
		free(path);
		free(name);
		i++;
	}
	return (NULL);
}

void	ft_check_signals(t_minishell *shell, char *lim_tmp, char *line)
{
	if (g_flag == CTRLC_ALERT)
	{
		if (shell->quote_lim == true)
			free(lim_tmp);
		close(shell->fd);
		ft_free_all(&shell);
		exit(CTRLC_ALERT);
	}
	if (!line)
	{
		ft_ctrl_d_heredoc_msg(shell->prompt_count, lim_tmp);
		if (shell->quote_lim == true)
			free(lim_tmp);
		close(shell->fd);
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:22:46 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 16:52:43 by lfournie         ###   ########.fr       */
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

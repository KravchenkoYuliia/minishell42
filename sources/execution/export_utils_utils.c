/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:53:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 15:03:42 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_find_oldpwd_in_env(t_minishell *shell)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		if (!ft_strncmp(temp->line, "OLDPWD", 7))
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	ft_export_oldpwd(t_minishell *shell)
{
	t_env	*new;
	char	*line;

	line = ft_strdup("OLDPWD=");
	if (!line)
		ft_malloc_failed(shell, ft_strlen("OLDPWD="), "ft_export_oldpwd");
	new = ft_lstnew_env(line);
	ft_lstadd_back_env(&shell->env, new);
}

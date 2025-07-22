/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:25:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/22 16:23:39 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_lstnew_redirect_heredoc(t_minishell *shell, int index)
{
	t_redirect	*lst;
	char	*fd_name;

	fd_name = ft_itoa(index);
	lst = (t_redirect *)malloc(sizeof(t_redirect));
	if (!lst)
		return (NULL);
	lst->heredoc_fd = shell->heredoc_fd[index];
	lst->heredoc_fd_name = fd_name;
	lst->file_name = NULL;
	lst->type = HEREDOC;
	lst->next = NULL;
	return (lst);
}

t_redirect	*ft_lstnew_redirect(void *content, int type)
{
	t_redirect	*lst;

	lst = (t_redirect *)malloc(sizeof(t_redirect));
	if (!lst)
		return (NULL);
	lst->file_name = content;
	lst->heredoc_fd = 0;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}

t_redirect	*ft_lstlast_redirect(t_redirect *lst)
{
	t_redirect	*temp;

	temp = lst;
	while (temp && temp->next != NULL)
			temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*temp;

	temp = ft_lstlast_redirect(*lst);
	if (!temp)
			*lst = new;
	else
			temp->next = new;
}

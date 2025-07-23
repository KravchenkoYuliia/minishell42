/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:25:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 18:04:50 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_lstnew_redirect_heredoc(t_minishell *shell, int index,
		char *heredoc_file_name)
{
	(void)index;
	(void)shell;
	t_redirect	*lst;

	lst = (t_redirect *)malloc(sizeof(t_redirect));
	if (!lst)
		return (NULL);
	lst->file_name = heredoc_file_name;
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

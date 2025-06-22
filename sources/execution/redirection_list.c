/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:25:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/22 13:20:32 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_lstnew_redirect(void *content, int type)
{
        t_redirect	*lst;
	int		*pipe;

	pipe = NULL;
        lst = (t_redirect *)malloc(sizeof(t_redirect));
        if (!lst)
                return (NULL);
        if (type == HEREDOC)
	{
		pipe = (int *)content;
		lst->heredoc_pipe[0] = pipe[0];
		lst->heredoc_pipe[1] = pipe[1];
		lst->file_name = NULL;
	}
	else if (type == INPUT || type == OUTPUT || type == APPEND)
	{
		lst->file_name= content;
		lst->heredoc_pipe[0] = 0;
		lst->heredoc_pipe[1] = 0;
	}
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
        t_redirect   *temp;

        temp = ft_lstlast_redirect(*lst);
        if (!temp)
                *lst = new;
        else
                temp->next = new;
}


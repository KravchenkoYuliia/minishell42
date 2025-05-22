/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:39:37 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/22 10:48:11 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_lstlast_tok(t_token *lst)
{
	t_token	*s_temp;

	s_temp = lst;
	while (s_temp && s_temp->next != NULL)
		s_temp = s_temp->next;
	return (s_temp);
}

void	ft_lstadd_back_tok(t_token **lst, t_token *new)
{
	t_token	*s_temp;

	s_temp = ft_lstlast_tok(*lst);
	if (!s_temp)
		*lst = new;
	else
		s_temp->next = new;	
}

t_token	*new_token_nd(char *value, int type, int incr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->incr = incr;
	token->next = NULL;
	return(token);
}

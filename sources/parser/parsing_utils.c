/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:39:37 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/28 11:19:00 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_redirs_lim(char c)
{
	if (c == 39 || c == 34 || c == 32 || c == 124 || c == 60 || c == 62)
		return (false);
	return (true);
}

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
		return (free(value), NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(value), free(token), NULL);
	token->type = type;
	token->incr = incr;
	token->next = NULL;
	return(free(value), token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:12:59 by yukravch          #+#    #+#             */
/*   Updated: 2024/11/24 13:33:09 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*s_temp;

	while (*lst)
	{
		s_temp = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		*lst = s_temp;
	}
}

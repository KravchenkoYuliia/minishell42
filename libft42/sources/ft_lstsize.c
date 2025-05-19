/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:16:18 by yukravch          #+#    #+#             */
/*   Updated: 2024/11/24 12:36:58 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*structure_temp;
	size_t	count;

	structure_temp = lst;
	count = 0;
	while (structure_temp)
	{
		structure_temp = structure_temp->next;
		count++;
	}
	return (count);
}

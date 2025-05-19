/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:31:34 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:22:48 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ft_isalpha(ch) || ft_isdigit(ch))
		return (1);
	return (0);
}

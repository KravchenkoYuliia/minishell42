/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_and_init_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:56:24 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 15:41:09 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_only_white_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 13 && input[i] != 32)
			return (false);
		i++;
	}
	return (true);
}


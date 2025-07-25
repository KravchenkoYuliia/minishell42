/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:32:12 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 15:47:09 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser_err_handler(t_token *token_lst, int err_code)
{
	if (err_code == 1)
	{
		ft_error_msg(NULL, SHL_NAME_ERR, "malloc: ",
			"Token list memory allocation has failed");
		free_token_list(token_lst);
	}
}

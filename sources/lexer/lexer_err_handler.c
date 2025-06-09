/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:49 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/09 14:05:45 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_err_handler(int err_code)
{
	printf("toupetishell🤏​: ");
	if (err_code == 1)
		printf("unclosed quotes\n");
	if (err_code == 2)
		printf("syntax error near unexpected token '|'\n");
	if (err_code == 3)
		printf("syntax error near unexpected token 'new_line'\n");
}

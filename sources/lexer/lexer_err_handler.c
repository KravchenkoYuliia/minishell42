/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:49 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/21 13:38:23 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_err_handler(int err_code)
{
	printf("syntax error : ");
	if (err_code == 1)
		printf("unclosed quotes\n");
	if (err_code == 2)
		printf("wrong usage of '|'\n");
	if (err_code == 3)
		printf("");
	if (err_code == 4)
		printf("");
	if (err_code == 5)
		printf("");
	if (err_code == 6)
		printf("");
}
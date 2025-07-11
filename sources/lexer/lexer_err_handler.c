/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:49 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/10 10:26:12 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_err_handler(int err_code, char c)
{
	printf("%s: ", SHELL_NAME_ERROR);
	if (err_code == 1)
		printf("syntax error: unclosed quotes\n");
	if (err_code == 2)
		printf("syntax error near unexpected token '|'\n");
	if (err_code == 3)
		printf("syntax error near unexpected token '%c'\n", c);
}

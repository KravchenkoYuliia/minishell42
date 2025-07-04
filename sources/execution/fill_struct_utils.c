/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:44:10 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/04 18:10:37 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_put_word_to_struct(t_minishell *shell,
		int i_struct, int i_args, t_token *temp)
{
	shell->cmd[i_struct]->args[i_args] = ft_strdup(temp->value);
	i_args++;
	if (i_args == shell->cmd[i_struct]->nb_of_words)
		shell->cmd[i_struct]->args[i_args] = NULL;
	return (i_args);
}

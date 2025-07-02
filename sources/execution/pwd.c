/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:03:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 16:06:43 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_pwd(t_minishell *shell, int index)
{
        char    buffer[PATH_MAX];

        (void) shell;
        (void) index;
        ft_bzero(buffer, PATH_MAX);
        if (getcwd(buffer, PATH_MAX) == NULL)
                return (ERROR);
        ft_write_stdout(buffer);
        ft_write_stdout("\n");
        return (SUCCESS);
}

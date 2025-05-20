/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/20 09:54:20 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft42/includes/ft_printf.h"
# include "../libft42/includes/get_next_line.h"
# include "../libft42/includes/libft.h"

typedef struct s_token
{
	char	*value;
	int		type;
	void	*next;
}			t_token;

enum s_type
{
	CMD,
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
};

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>

void	ft_redirect_input(char *infile);


#endif

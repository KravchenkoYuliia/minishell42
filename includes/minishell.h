/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/21 14:13:54 by lfournie         ###   ########.fr       */
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

enum e_type
{
	CMD,
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
};

# include <errno.h>
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
void	lexer_err_handler(int err_code);

//lexer
/////////////////
bool	ft_lexer(char *input);
bool	ft_check_unclosed_quotes(char *str);
bool 	ft_check_pipes(char *input);
bool 	ft_check_redir_heredoc(char *input);
bool 	ft_check_redir_append(char *input);
bool 	ft_check_redir_input(char *input);
bool 	ft_check_redir_output(char *input);
/////////////////

//execution
///////////////////////////////////////
void	ft_execution(t_token *tokens);
void	ft_exit_msg(char *msg);
//////////////////////////////////////






#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/23 10:51:04 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft42/includes/ft_printf.h"
# include "../libft42/includes/get_next_line.h"
# include "../libft42/includes/libft.h"

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

typedef struct s_token
{
	char	*value;
	int		type;
	int		incr;
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

typedef struct s_cmd_struct{

	char	**args;
	char	*input;
	char	*output;
	int	append;
	int	heredoc;
	int	pipe;


} t_cmd_struct;


//lexer
/////////////////
bool	ft_lexer(char *input);
bool	ft_check_unclosed_quotes(char *input);
bool 	ft_check_pipes(char *input);
bool 	ft_check_redir_heredoc(char *input);
bool 	ft_check_redir_append(char *input);
bool 	ft_check_redir_input(char *input);
bool 	ft_check_redir_output(char *input);
void	lexer_err_handler(int err_code);
/////////////////

//parser
////////////////
t_token *ft_parser(char *input);
t_token	*ft_if_simple_quotes(char *input, int start);
t_token	*ft_if_double_quotes(char *input, int start);
t_token	*ft_if_command(char *input, int start);
t_token	*ft_if_pipe(char *input, int start);
t_token	*ft_if_heredoc(char *input, int start);
t_token	*ft_if_input(char *input, int start);
t_token	*ft_if_append(char *input, int start);
t_token	*ft_if_output(char *input, int start);
t_token	*new_token_nd(char *value, int type, int incr);
t_token	*ft_lstlast_tok(t_token *lst);
void	ft_lstadd_back_tok(t_token **lst, t_token *new);
void	parser_err_handler(int err_code);
////////////////

//execution
/////////////////
void	ft_execution(t_token *tokens);
void	ft_exit_msg(char *msg);
/////////////////

//free_handler
////////////////
void free_token_list(t_token *head);
void    ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop);
////////////////

#endif

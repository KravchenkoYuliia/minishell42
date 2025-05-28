/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 12:38:20 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1
#define SUCCESS 0

# include "../libft42/includes/ft_printf.h"
# include "../libft42/includes/get_next_line.h"
# include "../libft42/includes/libft.h"

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
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
	//enum e_type	type;	
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

typedef struct s_exec{

	t_cmd_struct	**cmd;
	int		nb_of_cmd;
	int	pipe[2];
	int	save_stdin;
	int	save_stdout;
} t_exec;

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
/////////////////
t_token *ft_parser(char *input);
t_token	*ft_parsing_a(char *input, int i);
t_token	*ft_parsing_b(char *input, int i);
t_token	*ft_if_quotes(char *input, int start);
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
void	set_buf_redirs(char *input, int start, char *value_buf, int buf_start);
bool	ft_redirs_lim(char c);
/////////////////

//execution
/////////////////
void	ft_execution(t_token *tokens);
void	ft_exit_msg(char *msg);
void    ft_child_error_msg(char *msg);
int     ft_count_cmds(t_token *tokens);
void    ft_malloc_struct_foreach_cmd(t_cmd_struct ***struct_for_cmds, int nb_of_cmd);
void    ft_initialize_struct_foreach_cmd(t_cmd_struct **cmds, int nb);
void    ft_fill_struct_foreach_cmd(t_token *tokens, t_cmd_struct **cmds, int nb);
void    ft_check_if_build_in_cmd(t_exec *exec, int i);
void    ft_exit(t_exec *exec, int str_index);
int     ft_child_process(t_exec *exec, int i);
int     ft_child_for_last_cmd(t_exec *exec, int i);
void    ft_save_STD_FILENO(t_exec *exec);
void    ft_init_exec(t_exec **exec, t_cmd_struct **struct_for_cmd, int nb_of_cmd);
/////////////////

//free_handler
/////////////////
void free_token_list(t_token *head);
void    ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop);
/////////////////

#endif

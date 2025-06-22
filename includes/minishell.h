/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/22 13:52:49 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1
# define SUCCESS 0
# define SHELL_NAME "toupetishell🤏: "
# define SHELL_NAME_ERROR "toupetishell🤏"

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

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
# include <limits.h>


typedef struct s_env t_env;
typedef struct s_export t_export;
typedef struct s_token t_token;
typedef struct  s_redirect t_redirect;


typedef struct s_token
{
	char	*value;
	//enum e_type	type;	
	int		type;
	int		incr;
	t_token	*next;
}			t_token;

enum e_type
{
	WORD,
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
};

typedef struct s_cmd_struct{

	int	nb_of_words;
	char	**args;
	t_redirect	*input_list;
	t_redirect	*output_list;
	char	*input;
	char	*output;
	int	heredoc_pipe[2];
	int	append;
	int	heredoc;
	int	pipe;


} t_cmd_struct;

typedef struct	s_redirect{

	char		*file_name;
	int		heredoc_pipe[2];
	int		type;
	t_redirect	*next;

} t_redirect;

typedef	struct	s_env{

	char	*line;
	t_env	*next;

} t_env;

typedef struct s_minishell{

	char	*input;
	t_token	*token_lst;
	int	exit_status;
	
	t_env	*env;
	t_cmd_struct	**cmd;
	int		nb_of_cmd;
	int	pipe[2];
	int	save_stdin;
	int	save_stdout;
	char	*history;
	bool	heredoc_in_input;


} t_minishell;




//lexer
/////////////////
bool	ft_lexer(char *input);
bool	ft_check_unclosed_quotes(char *input);
bool 	ft_check_pipes(char *input);
int		ft_check_redirs(char *input);
void	lexer_err_handler(int err_code, char c);
/////////////////

//parser
/////////////////
t_token *ft_parser(char *input);
t_token	*ft_parsing_a(char *input, int i);
t_token	*ft_parsing_b(char *input, int i);
t_token	*ft_if_quotes_a(char *input, int start);
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
void	ft_if_quotes_b(char *input, int start, char *value_buf, int buf_start);
bool	ft_redirs_lim(char c);
/////////////////

//expander
/////////////////
void	ft_expander(t_minishell *shell);
void	ft_expand_var(t_minishell **shell);
bool	ft_is_expandable(char *value, int i);
/////////////////

//execution
/////////////////
void	ft_fill_env(t_minishell *shell, t_env **env_list, char **env);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(void *content);
void	ft_print_env(t_env *env);



void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index);
char	*ft_strjoin_heredoc(char *s1, char *s2);
t_redirect	*ft_lstnew_redirect(void *content, int type);
t_redirect	*ft_lstlast_redirect(t_redirect *lst);
void	ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);



int	ft_execution(t_minishell *shell);
void	ft_init_struct_foreach_cmd(t_minishell *shell);
void	ft_get_nb_of_cmd(t_minishell *shell);
void	ft_total_exit(char *msg, t_minishell *shell, int stop);
void	ft_error_msg(char *shell_name, char *cmd, char *msg);
void	ft_get_nb_of_words(t_minishell *shell);
void	ft_parent_process(t_minishell *shell);
void	ft_save_STD_FILENO(t_minishell *shell);
void    ft_change_pwd(t_env *env, char *directory);
bool	ft_is_option(char *args);
char	*ft_get_home_path(t_env *env);
int	ft_just_export(t_env *env);
int	ft_export_value(t_minishell *shell, int index);
bool	ft_unset_or_not_unset(char *env_line, char **args);
char	*ft_strjoin_export(char *str1, char *str2);
int	ft_charset(char *str, char c);
char	*ft_copy_name_inenv(char *line);
bool	ft_name_exists_already(t_env *env, char *name, char *line);
void	ft_change_valueof_name(t_env *env, char *line);
void	ft_simple_cmd(t_minishell *shell, int index);
char	*ft_find_absolute_path(t_minishell *shell, int index);
int	ft_redirections_simple_cmd(t_minishell *shell, int index);
int	ft_check_infile(t_minishell *shell, int index);
void	ft_child_loop(t_minishell *shell, int index, int pipe[2]);
int	ft_input_redir_simple_cmd(t_minishell *shell, int index);
int	ft_output_redir_simple_cmd(t_minishell *shell, int index);
void	ft_redir_in_pipe(int pipe[2]);
void	ft_execute_one_cmd(t_minishell *shell, char *cmd, int index);
void	ft_execute_cmd_withpipe(t_minishell *shell, char *cmd, int index);
void	ft_simple_cmd_withpipe(t_minishell *shell, int index);
int	ft_export_forempty_env(t_minishell *shell);	

int	ft_env(t_minishell *shell, int index);
int	ft_echo(t_minishell *shell, int index);
int	ft_cd(t_minishell *shell, int index);
int	ft_pwd(t_minishell *shell, int index);
int	ft_export(t_minishell *shell, int index);
int	ft_unset(t_minishell *shell, int index);
int	ft_exit(t_minishell *shell, int index);

/////////////////

//free_handler
/////////////////
void	free_token_list(t_token *head);
void	ft_free_env(t_env *head);
void	ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop);
void	ft_free_args(char **array);
/////////////////

#endif

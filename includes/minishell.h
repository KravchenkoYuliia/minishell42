/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/11 11:21:44 by yukravch         ###   ########.fr       */
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
	char	input[PATH_MAX];
	char	output[PATH_MAX];
	int	append;
	int	heredoc;
	int	pipe;


} t_cmd_struct;


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

//execution
/////////////////
void	ft_fill_env(t_env **env_list, char **env);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(void *content);
void	ft_print_env(t_env *env);





int	ft_execution(t_minishell *shell);
void	ft_init_struct_foreach_cmd(t_minishell *shell);
void	ft_get_nb_of_cmd(t_minishell *shell);
void	ft_exit_free(char *msg, t_minishell *shell, int stop);
void	ft_error_msg(char *shell_name, char *msg);
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



int	ft_env(t_minishell *shell, int index);
int	ft_echo(t_minishell *shell, int index);
int	ft_cd(t_minishell *shell, int index);
int	ft_pwd(t_minishell *shell, int index);
int	ft_export(t_minishell *shell, int index);
int	ft_unset(t_minishell *shell, int index);
int	ft_exit(t_minishell *shell, int index);


/*
void	ft_exit_msg(char *msg);
void    ft_child_error_msg(char *msg);
void    ft_malloc_struct_foreach_cmd(t_cmd_struct ***struct_for_cmds, int nb_of_cmd);
void    ft_fill_struct_foreach_cmd(t_token *tokens, t_cmd_struct **cmds, int nb);
int	ft_check_if_build_in_cmd(t_exec *exec, int i);
int	ft_exit(t_exec *exec, int str_index);
int     ft_child_process(t_exec *exec, int i);
int     ft_child_for_last_cmd(t_exec *exec, int i);
void    ft_save_STD_FILENO(t_exec *exec);
int		ft_isdigit_str(char *str);
int	ft_cd(t_exec* exec, int str_index);
int	ft_pwd(t_exec* exec, int str_index);*/
/////////////////

//free_handler
/////////////////
void	free_token_list(t_token *head);
void	ft_free_env(t_env *head);
void	ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop);
/////////////////

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 11:51:26 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define SHELL_NAME "toupetishell: "
# define SHELL_NAME_ERROR "toupetishell"

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
# include <asm/termbits.h>
# include <sys/ioctl.h>

extern volatile sig_atomic_t	flag;

typedef struct s_token
{
	char			*value;
	int				type;
	int				incr;
	struct s_token	*next;
}	t_token;

enum e_type
{
	SUCCESS,
	ERROR,
	WORD,
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
	SIGINT_NEW_LINE,
	CHILD,
	PARENT,
	CTRLC_ALERT,
	CTRLC_OFF,
};

typedef struct s_cmd_struct
{
	int					nb_of_words;
	char				**args;
	struct s_redirect	*input_list;
	struct s_redirect	*output_list;
	char				*input;
	char				*output;
	int					heredoc_pipe[2];
	int					append;
	int					heredoc;
	int					pipe_flag;
	int					pipe[2];
}	t_cmd_struct;

typedef struct s_redirect
{
	char				*file_name;
	int					heredoc_pipe[2];
	int					type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	int				prompt_count;
	char				*input;
	t_token				*token_lst;
	int					exit_status;	
	t_env				*env;
	char				**env_execve;
	t_cmd_struct		**cmd;
	int					nb_of_cmd;
	int					pipe[2];
	int					save_stdin;
	int					save_stdout;
	char				*history;
	bool				heredoc_in_input;
	struct sigaction	sig;
	int	process;
}	t_minishell;

///signals///////////////////
void		ft_ctrl_c(int signal);
void		ft_ctrl_d(t_minishell *shell);
void		ft_ctrl_d_heredoc_msg(int line, char *limiter);
void		ft_ctrl_c_child(int sign);
////////////////////////////////

//lexer
/////////////////
bool		ft_lexer(char *input);
bool		ft_check_unclosed_quotes(char *input);
bool		ft_check_pipes(char *input);
int			ft_check_redirs(char *input);
void		lexer_err_handler(int err_code, char c);
/////////////////

//parser
/////////////////
t_token		*ft_parser(char *input, int i);
t_token		*ft_parsing_a(char *input, int i);
t_token		*ft_parsing_b(char *input, int i);
t_token		*ft_if_quotes_a(char *input, int start);
t_token		*ft_if_command(char *input, int start);
t_token		*ft_if_pipe(char *input, int start);
t_token		*ft_if_heredoc(char *input, int start);
t_token		*ft_if_input(char *input, int start);
t_token		*ft_if_append(char *input, int start);
t_token		*ft_if_output(char *input, int start);
t_token		*new_token_nd(char *value, int type, int incr);
t_token		*ft_lstlast_tok(t_token *lst);
void		ft_lstadd_back_tok(t_token **lst, t_token *new);
void		parser_err_handler(t_token *token_lst, int err_code);
int		set_buf_redirs(char *i, int s, char *v_b, int b_s);
void		ft_if_quotes_b(char *i, int s, char *v_b, int b_s);
bool		ft_redirs_lim(char c);
/////////////////

//expander
/////////////////
void		ft_expander(t_minishell *shell);
void		ft_expand_a(t_minishell *shell, char *var, int index);
void		ft_expand_b(t_minishell **shell, char *var, int index);
char		*ft_get_env(char *var, t_env *env, int exit_status);
int			ft_is_expandable(char *value);
bool		ft_is_unquotable(int type, char *value);
bool		ft_is_splitable(char *value);
void		ft_word_split(t_minishell **shell);
char		*ft_unquote(t_minishell **shl, char *value, int i, int j);
/////////////////

//execution
/////////////////
void		ft_write_stdout(char *msg);
void		ft_fill_env(t_minishell *shell, t_env **env_list, char **env);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void *content);
void		ft_print_env(t_env *env);
void		ft_handle_shlvl_in_list(t_env *env);
void		ft_handle_shlvl_in_array(char **env);
int			ft_export_forempty_env(t_minishell *shell);	
int		ft_fork_heredoc(t_minishell *shell, char *limiter, int index);
void		ft_handle_heredoc(t_minishell *shell, char *limiter, int index);
char		*ft_strjoin_heredoc(char *s1, char *s2);
t_redirect	*ft_lstnew_redirect(void *content, int type);
t_redirect	*ft_lstlast_redirect(t_redirect *lst);
void		ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);
int			ft_execution(t_minishell *shell);
int		ft_init_struct_foreach_cmd(t_minishell *shell);
void		ft_get_nb_of_cmd(t_minishell *shell);
void	ft_total_exit(t_minishell *shell);
void		ft_error_msg(char *shell_name, char *cmd, char *msg);
void		ft_get_nb_of_words(t_minishell *shell);
void		ft_parent_process(t_minishell *shell);
void		ft_save_std_fileno(t_minishell *shell);
void		ft_change_pwd(t_env *env, char *directory);
bool		ft_is_option(char *args);
char		*ft_get_home_path(t_env *env);
int			ft_just_export(t_env *env);
int			ft_export_value(t_minishell *shell, int index);
int		ft_option_check(t_minishell *shell, int index, int i);
bool		ft_unset_or_not_unset(char *env_line, char **args);
char		*ft_strjoin_export(char *str1, char *str2);
int			ft_charset(char *str, char c);
char		*ft_copy_name_inenv(char *line);
bool		ft_name_exists_already(t_env *env, char *name, char *line);
void		ft_change_valueof_name(t_env *env, char *line);
char		*ft_find_absolute_path(t_minishell *shell, int index);
void		ft_execute_one_cmd(t_minishell *shell, char *cmd, int index);
void		ft_simple_cmd(t_minishell *shell, int index);
void		ft_child_loop(t_minishell *shell, int index);
void		ft_simple_cmd_withpipe(t_minishell *shell, int index);
int		ft_copy_env_for_execve(t_minishell *shell);
int		ft_malloc_env_for_execve(char ***env, int nb);
int			ft_count_var_in_env(t_env *env);
int			ft_redirections(t_minishell *shell, int index);
int			ft_redir_input(t_minishell *shell, int index);
int			ft_redir_output(t_minishell *shell, int index);
int			ft_check_infile(char *input);
int			ft_env(t_minishell *shell, int index);
int			ft_echo(t_minishell *shell, int index);
int			ft_cd(t_minishell *shell, int index);
int			ft_pwd(t_minishell *shell, int index);
int			ft_export(t_minishell *shell, int index);
int			ft_unset(t_minishell *shell, int index);
int			ft_exit(t_minishell *shell, int index);
char	*ft_expand_line_heredoc(char *expand_me);
char	*ft_quotes(char *has_quotes, char *result);
bool	ft_quote_or_not_quote(char *limiter);
char	*ft_unquote_limiter(char *unquote_me);


/////////////////

//free_handler
/////////////////
void		free_token_list(t_token *head);
void		ft_free_env(t_env *head);
void		ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop);
void		ft_free_args(char **array);
void		free_redir_list(t_redirect *head);
void		ft_free_all(t_minishell **shell);
/////////////////

#endif

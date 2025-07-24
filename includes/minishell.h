/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:55:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 12:00:57 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define CTRLC_ALERT 130

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

extern volatile sig_atomic_t	g_flag;

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
	EXIT_FLAG,
	WORD,
	PIPE,
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
	CHILD,
	PARENT,
	SIGIGN,
	NEW_PROMPT,
	CTRLC_OFF,
	SIG_QUIT,
};

typedef struct s_redirect
{
	char				*file_name;
	int					type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd_struct
{
	int					nb_of_words;
	char				**args;
	t_redirect			*input_list;
	t_redirect			*output_list;
	char				*input;
	char				*output;
	int					append;
	int					heredoc;
	int					pipe_flag;
	int					pipe[2];
}	t_cmd_struct;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	bool	need_to_add_oldpwd;
	int				prompt_count;
	char				*input;
	t_token				*token_lst;
	int					exit_status;	
	t_env				*env;
	char				**env_execve;
	t_cmd_struct		**cmd;
	int					nb_of_cmd;
	int					save_stdin;
	int					save_stdout;
	int	fd;
	struct sigaction	sig;
	struct sigaction	sig_quit;
	int	process;
	bool	quote_lim;
	bool	malloc_fail;
	int		malloc_fail_size;
}	t_minishell;

////////////////////////////
////////main////////////////

void close_them_please(t_cmd_struct** cmds);
void close_it_please(t_cmd_struct* cmds);


char	*ft_cut_input(char *cut_me);
bool	ft_find_heredoc(t_token *token_lst);
void	ft_init_minishell(t_minishell *shell, char **env);
void	ft_init_for_every_prompt(t_minishell *shell);
void	ft_checking_input(t_minishell *shell);
void	ft_add_history_and_expand(t_minishell *shell);
bool	ft_new_prompt(t_minishell *shell);
bool	ft_parsing_check_error(t_minishell  *shell);
bool	ft_execution_check_error(t_minishell *shell);
bool	ft_only_white_space(char *input);

////////////////////////////
///signals///////////////////
void		ft_ctrl_c(int signal);
void		ft_ctrl_d(t_minishell *shell);
void		ft_ctrl_d_heredoc_msg(int line, char *limiter);
void		ft_ctrl_c_child(int sign);
void		ft_set_of_sig(t_minishell *shell, int type);
void		ft_set_sig_quit();
void		ft_sig_quit(int sign);
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
t_token		*ft_parser(t_minishell *shell, int i);
t_token		*ft_parsing_a(t_minishell *shell, int i);
t_token		*ft_parsing_b(t_minishell *shell, int i);
t_token		*ft_if_quotes_a(t_minishell *shell, int start);
t_token		*ft_if_command(t_minishell *shell, int start);
t_token		*ft_if_pipe(t_minishell *shell, int start);
t_token		*ft_if_heredoc(t_minishell *shell, int start);
t_token		*ft_if_input(t_minishell *shell, int start);
t_token		*ft_if_append(t_minishell *shell, int start);
t_token		*ft_if_output(t_minishell *shell, int start);
t_token		*ft_parser(t_minishell *shell, int i);
t_token		*ft_parsing_a(t_minishell *shell, int i);
t_token		*ft_parsing_b(t_minishell *shell, int i);
t_token		*ft_if_quotes_a(t_minishell *shell, int start);
t_token		*ft_if_command(t_minishell *shell, int start);
t_token		*ft_if_pipe(t_minishell *shell, int start);
t_token		*ft_if_heredoc(t_minishell *shell, int start);
t_token		*ft_if_input(t_minishell *shell, int start);
t_token		*ft_if_append(t_minishell *shell, int start);
t_token		*ft_if_output(t_minishell *shell, int start);
t_token		*new_token_nd(char *value, int type, int incr);
t_token		*ft_lstlast_tok(t_token *lst);
void		ft_lstadd_back_tok(t_token **lst, t_token *new);
void		parser_err_handler(t_token *token_lst, int err_code);
int		set_buf_redirs(char *i, int s, char *v_b, int b_s);
void		ft_if_quotes_b(char *i, int s, char *v_b, int b_s);
bool		rds_lim(char c);
bool	ft_if_symbol(char c);
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
char	*ft_strjoin_char(char *str, char c);
void		ft_fill_env(t_minishell *shell, t_env **env_list, char **env);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void *content);
void		ft_print_env(t_env *env);
void		ft_handle_shlvl(t_minishell *shell, t_env *env);
void		ft_handle_shlvl_in_array(t_minishell *shell, char **env);
int			ft_export_forempty_env(t_minishell *shell);	
int		ft_fork_heredoc(t_minishell *shell, char *limiter, int index);
char	*ft_name_the_heredoc_file(t_minishell *shell, int index);
void		ft_handle_heredoc(t_minishell *shell, char *limiter, int index);
int		ft_wait_heredoc_child(t_minishell *shell, pid_t pid);
char		*ft_strjoin_heredoc(char *s1, char *s2);
t_redirect	*ft_lstnew_redirect(void *content, int type);
t_redirect      *ft_lstnew_redirect_heredoc(t_minishell *shell, char *heredoc_file_name);
t_redirect	*ft_lstlast_redirect(t_redirect *lst);
void		ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);
int			ft_execution(t_minishell *shell);
int		ft_init_struct_foreach_cmd(t_minishell *shell);
int	ft_fill_redirection(t_minishell *shell, int i_struct, t_token *temp);
void	ft_put_input_to_struct(t_minishell *shell, int i_struct, t_token *temp);
void	ft_put_output_to_struct(t_minishell *shell, int i_struct, t_token *temp);
void	ft_put_append_to_struct(t_minishell *shell, int i_struct, t_token *temp);
void	ft_put_heredoc_to_struct(t_minishell *shell, int index, char *heredoc_file_name);
int	ft_put_word_to_struct(t_minishell *shell, int i_struct, int i_args, t_token *temp);
void	ft_fill_heredoc_history(t_minishell *shell, int index);
void		ft_get_nb_of_cmd(t_minishell *shell);
void	ft_total_exit(t_minishell *shell);
void		ft_error_msg(t_minishell *shell, char *shell_name, char *cmd, char *msg);
void		ft_get_nb_of_words(t_minishell *shell);
void		ft_save_std_fileno(t_minishell *shell);
void		ft_change_pwd(t_minishell *shell, t_env *env, char *directory);
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
int		ft_parent_process(t_minishell *shell);
int	ft_creating_child(t_minishell *shell, int index, pid_t pid);
int		ft_execute_one_cmd(t_minishell *shell, char *cmd, int index);
bool	ft_exec_built_in_cmd(t_minishell *shell, int index, char *cmd);
void	ft_cmd_checking(t_minishell *shell, int index, char *cmd);
int		ft_simple_cmd(t_minishell *shell, int index);
void		ft_simple_cmd_withpipe(t_minishell *shell, int index);
void		ft_child_loop(t_minishell *shell, int index);
void		ft_waiting_for_child(t_minishell *shell, int index, int nb, pid_t pid);
int		ft_copy_env_for_execve(t_minishell *shell);
int		ft_malloc_env_for_execve(char ***env, int nb);
int			ft_count_var_in_env(t_env *env);
int			ft_redirections(t_minishell *shell, int index);
int			ft_redir_input(t_minishell *shell, int index);
int			ft_redir_output(t_minishell *shell, int index);
int			ft_check_infile(t_minishell *shell, char *input);
int			ft_env(t_minishell *shell, int index);
int			ft_echo(t_minishell *shell, int index);
int			ft_cd(t_minishell *shell, int index);
int			ft_pwd(t_minishell *shell, int index);
int			ft_export(t_minishell *shell, int index);
int			ft_unset(t_minishell *shell, int index);
int			ft_exit(t_minishell *shell, int index);
char	*ft_expand_line_heredoc(t_minishell *shell, char *expand_me);
char	*ft_quotes(char *has_quotes, char *result);
bool	ft_quote_or_not_quote(char *limiter);
char	*ft_unquote_limiter(char *unquote_me);
char	*ft_unquote_lim_heredoc(t_minishell *shell, char *limiter);
void	ft_write_to_stderr(t_minishell *shell, char *msg1, char *arg, char *msg2);
bool	ft_find_oldpwd_in_env(t_minishell *shell);
void	ft_export_oldpwd(t_minishell *shell);
void	ft_syscall_ft_failed(t_minishell *shell, char *cmd);
bool	ft_check_var_name(char *name);
void	ft_unlink_heredoc_files(t_minishell *shell);
/////////////////

//free_handler
/////////////////
void		free_token_list(t_token *head);
void		ft_free_env(t_env *head);
void		ft_free_struct_foreach_cmd(t_cmd_struct **structs);
void		ft_free_args(char **array);
void		free_redir_list(t_redirect *head);
void		ft_free_all(t_minishell **shell);
void	ft_malloc_failed(t_minishell *shell, int nb, char *name);
void	ft_clear_after_cmd_exec(t_minishell *shell);
/////////////////

#endif

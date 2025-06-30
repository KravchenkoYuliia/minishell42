/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/30 13:45:29 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(t_minishell **shell, char **env)
{
	*shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!*shell)
		exit(EXIT_FAILURE);
	(*shell)->prompt_count = 0;
	(*shell)->token_lst = NULL;
	(*shell)->input = NULL;
	(*shell)->exit_status = 0;
	(*shell)->env = NULL;
	ft_fill_env(*shell, &(*shell)->env, env);
	(*shell)->env_execve = NULL;
	(*shell)->cmd = NULL;
	(*shell)->history = NULL;
	(*shell)->nb_of_cmd = 0;
	(*shell)->heredoc_in_input = true;
}

bool	ft_find_heredoc(t_token *token_lst)
{
	t_token	*temp;

	temp = token_lst;
	while (temp)
	{
		if (temp->type == HEREDOC)
			return (true);
		temp = temp->next;
	}
	return (false);
}

char	*ft_cut_input(char *cut_me)
{
	int		i;
	char	*new_input;
	char	**lines;

	i = 0;
	new_input = NULL;
	lines = ft_split(cut_me, '\n');
	while (lines[i])
		i++;
	if (i <= 1)
		return (cut_me);
	new_input = ft_strdup(lines[i - 1]);
	if (i > 1 && ft_strstr(lines[0], new_input))
		return (NULL);
	free(cut_me);
	ft_free_args(lines);
	return (new_input);
}

void	ft_minishell(t_minishell *shell)
{
	//t_token	*cursor;

	while (1)
	{
		shell->heredoc_in_input = true;
		shell->history = NULL;
		shell->input = readline(SHELL_NAME);
		if (!shell->input)
			ft_ctrl_d(shell);
		if (flag == CTRLC_ALERT)
		{
			flag = CTRLC_OFF;
			shell->exit_status = 130;
		}
		if (shell->exit_status == 130)
			shell->prompt_count += 1;
		shell->prompt_count += 1;
		shell->input = ft_cut_input(shell->input);
		if (shell->input && ft_lexer(shell->input))
		{
			shell->token_lst = ft_parser(shell->input);
			if (shell->input && *shell->input
				&& !ft_find_heredoc(shell->token_lst))
			{
				add_history(shell->input);
				shell->heredoc_in_input = false;
			}
			ft_expander(shell);
			/*cursor = shell->token_lst;
			while (cursor)
			{
				printf("value: %s, type: %d\n", cursor->value, cursor->type);
				cursor = cursor->next;
			}*/
			if (shell->token_lst)
			{

				if (ft_execution(shell) == SIGINT_NEW_LINE)
					add_history(shell->history);
			}
		}
		else
		{
			if (shell->input && *shell->input)
				add_history(shell->input);
			shell->exit_status = 2;
		}
	}
}

int	flag = CTRLC_OFF;

int	main(int ac, char **av, char **env)
{
	t_minishell		*shell;

	(void)av;
	shell = NULL;
	signal(SIGQUIT, SIG_IGN);
	ft_init_minishell(&shell, env);
	if (ac != 1)
		return (0);
	sigemptyset(&shell->sig.sa_mask);
	shell->sig.sa_handler = ft_ctrl_c;
	shell->sig.sa_flags = 0;
	sigaction(SIGINT, &shell->sig, NULL);
	ft_minishell(shell);
	return (0);
}

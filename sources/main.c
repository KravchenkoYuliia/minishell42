/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/21 10:00:11 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_lstlast_tok(t_token *lst)
{
	t_token	*s_temp;

	s_temp = lst;
	while (s_temp && s_temp->next != NULL)
		s_temp = s_temp->next;
	return (s_temp);
}

static void	ft_lstadd_back_tok(t_token **lst, t_token *new)
{
	t_token	*s_temp;

	s_temp = ft_lstlast_tok(*lst);
	if (!s_temp)
		*lst = new;
	else
		s_temp->next = new;	
}

static bool	ft_check_unclosed_quotes(char *str)
{
	int 	i;
	int		sp;
	int		db;

	i = 0;
	sp = 0;
	db = 0;
	while (str[i])
	{
		if (str[i] == 39 && db == 0)
			sp++;
		else if (str[i] == 34 && sp == 0)
			db++;
		if (sp % 2 == 0)
			sp = 0;
		if ( db % 2 == 0)
			db = 0;
		i++;
	}
	if (sp % 2 != 0 || db % 2 != 0)
		return (false);
	return (true);
}

static t_token *new_token_nd(char *value, int type)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return(token);
}

static t_token *new_prompt(char *input)
{
	t_token	*token_lst;
	t_token	*new_token;
	char	*value_buf;
	int		i;
	int		k;

	token_lst = NULL;
	i = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == 39)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			i++;
			k = 0;
			while (input[i] != 39)
			{
				value_buf[k] = input[i];
				i++;
				k++;
			}
			value_buf[k] = '\0';
			new_token = new_token_nd(value_buf, CMD);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 34)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			i++;
			k = 0;
			while (input[i] != 34)
			{
				value_buf[k] = input[i];
				i++;
				k++;
			}
			value_buf[k] = '\0';
			new_token = new_token_nd(value_buf, CMD);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (ft_isalnum(input[i]))
		{
			value_buf = ft_calloc(100, 1);
			if (!value_buf)
				exit(EXIT_FAILURE);
			k = 0;
			while (ft_isalnum(input[i]))
			{
				value_buf[k] = input[i];
				i++;
				k++;
			}
			value_buf[k] = '\0';
			new_token = new_token_nd(value_buf, CMD);
			if (!new_token)
				return (NULL);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 124)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			value_buf[0] = 124;
			value_buf[1] = '\0';
			i++;
			k = 2;
			new_token = new_token_nd(value_buf, PIPE);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 60 && input[i + 1] == 60)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			value_buf[0] = 60;
			value_buf[1] = 60;
			i += 2;
			k = 2;
			while (input[i] == 32 || ft_isalnum(input[i]))
			{
				value_buf[k] = input[i];
				i++;
				k++;
			}
			value_buf[k] = '\0';
			new_token = new_token_nd(value_buf, HEREDOC);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 60 && input[i + 1] != 60)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			value_buf[0] = 60;
			value_buf[1] = '\0';
			i++;
			k = 2;
			new_token = new_token_nd(value_buf, INPUT);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 62 && input[i + 1] == 62)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			value_buf[0] = 62;
			value_buf[1] = 62;
			value_buf[3] = '\0';
			i += 2;
			k = 3;
			new_token = new_token_nd(value_buf, APPEND);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		else if (input[i] == 62 && input[i + 1] != 62)
		{
			value_buf = malloc(100);
			if (!value_buf)
				exit(EXIT_FAILURE);
			value_buf[0] = 62;
			value_buf[1] = '\0';
			i++;
			k = 2;
			new_token = new_token_nd(value_buf, OUTPUT);
			ft_lstadd_back_tok(&token_lst, new_token);
			free(value_buf);
		}
		i++;
	}
	return (token_lst);
}

static void free_token_list(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

int main(int ac, char **av)
{
	t_token	*token_lst;
	char	*input;
	(void)av;

	if (ac != 1)
	{
		return(0);
	}
	
	//printf("%s\n", getenv("PATH"));
	while (1)
	{
		input = readline("babyshell: ");
		if (!ft_check_unclosed_quotes(input))
			return (1);
		token_lst = NULL;
		token_lst = new_prompt(input);
		if (!token_lst)
			printf("OUPS");
		free_token_list(token_lst);
		if (input[0] == 'C')
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		free(input);
	}
	return (0);
}

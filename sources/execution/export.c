#include "test.h"


char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	len;
	char			*array;
	int				i;
	int				j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	array = malloc(sizeof(char) * len + 3);
	if (!array)
		return (NULL);
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		if (j != 0 && s2[j-1] == '=')
			break ;
		array[i] = s2[j];
		j++;
		i++;
	}
	array[i] = '\"';
	i++;
	while (s2[j])
	{
		array[i] = s2[j];
		j++;
		i++;
	}
	array[i] = '\"';
	i++;
	array[i] = '\0';
	return (array);
}

int	ft_charset(char *arg, char c)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == c)
			return 1;
		i++;
	}
	return 0;
}


void	ft_check_av(char* arg)
{
	if (ft_charset(arg, '=') == 0)
		return ;
}

int	ft_isalpha(char c)
{
	if (c >= 'a' && c <='z')
		return 1;
	else if (c >='A' && c <= 'Z')
		return 1;
	return 0;

}

void	ft_export_value(int ac, char **av, t_env **head)
{
	int i = 2;
	t_env*	new;
	char	*export_content;


	while (i < ac)
	{
		if (!ft_isalpha(av[i][0]))
			printf("blablaShell: export: `%s': not a valid identifier\n", av[i]);
		else if (ft_charset(av[i], '=') == 1)
		{
			export_content = ft_strdup(av[i]);
			new = ft_lstnew(export_content);
			ft_lstadd_back(head, new);
		}
		i++;
	}
	ft_print_list_char(*head);
}

void	ft_just_export(t_env *env_list)
{
	char*	new_content;
	t_env* current = env_list;

	while (current)
	{
		new_content = ft_strjoin("declare -x ", current->content);
		free(current->content);
		current->content = new_content;
		current = current->next;
	}
	ft_print_list_char(env_list);
}
int	ft_export(int ac, char** av, char** env)
{
	t_env*	env_list = NULL;
	int i = 2;

	ft_fill_env_list(env, &env_list);

	if (!av[i])
		ft_just_export(env_list);
	ft_export_value(ac, av, &env_list);
	return 0;
}

int	main(int ac, char** av, char** env)
{
	if (ac < 2)
		return 0;
	if (ft_strncmp(av[1], "export", 7) == 0)
	{
		ft_export(ac, av, env);

		ft_export(ac, av, env);
	}
}

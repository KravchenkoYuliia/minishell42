#include <stdio.h>
#include <stdlib.h>


typedef struct s_env t_env;

typedef struct s_env{

	char*	content;
	t_env*	next;

} t_env ;

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return 0;
	while (str[i])
		i++;
	return i;
}

char    *ft_strdup(char *s)
{
        char    *str;
        int             l;
        int             i;

        i = 0;
        l = ft_strlen(s) + 1;
        str = malloc(sizeof(char) * l);
        if (!str)
                return (NULL);
        while (s[i])
        {
                str[i] = s[i];
                i++;
        }
        str[i] = '\0';
        return (str);
}

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t                  i;
        unsigned char   *str1;
        unsigned char   *str2;

        i = 0;
        str1 = (unsigned char *)s1;
        str2 = (unsigned char *)s2;
        if (n == 0)
                return (0);
        while (i < n - 1 && str1[i] == str2[i] && str1[i] && str2[i])
                i++;
        return (str1[i] - str2[i]);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*s_temp;

	s_temp = lst;
	while (s_temp && s_temp->next != NULL)
		s_temp = s_temp->next;
	return (s_temp);
}


t_env  *ft_lstnew(void *content)
{
        t_env  *lst;

        lst = (t_env *)malloc(sizeof(t_env));
        if (!lst)
                return (NULL);
        lst->content = content;
        lst->next = NULL;
        return (lst);
}

void    ft_lstadd_back(t_env **lst, t_env *new)
{
        t_env  *s_temp;

        s_temp = ft_lstlast(*lst);
        if (!s_temp)
                *lst = new;
        else
                s_temp->next = new;
}

void    ft_print_list_char(t_env *list)
{
        while (list)
        {
                printf("%s", ((char *)(list->content)));
        	printf("\n");
                list = list->next;
        }
}

void	ft_change_last_line(t_env** env)
{
	t_env* temp = *env;
	char* content;

	content = ft_strdup("_=/usr/bin/env");
	while (temp)
	{
		if (temp->content[0] == '_')
		{
			free(temp->content);
			temp->content = content;
		}	
		temp = temp->next;
	}
}

void	ft_fill_env_list(char** env, t_env** env_list)
{

	int i = 0;
	t_env*	new;
	char*	content = NULL;
	
	while (env[i])
	{
		content = ft_strdup (env[i]);
		new = ft_lstnew(content);
		ft_lstadd_back(env_list, new);
		i++;
	}
	ft_change_last_line(env_list);

}

int	ft_env(char** env)
{
	t_env*	env_list = NULL;
	
	ft_fill_env_list(env, &env_list);
	ft_print_list_char(env_list);
	return 0;
}

int main(int ac, char** av, char** env)
{
	if (ac < 2)
		return 0;

	if (ft_strncmp(av[1], "env", 4) == 0)
		ft_env(env);

}

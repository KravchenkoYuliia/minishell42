#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_env t_env;

typedef struct s_env{

        char*   content;
        t_env*  next;

} t_env ;




int     ft_env(char** env);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_fill_env_list(char** env, t_env** env_list);
int     ft_strlen(char* str);
void    ft_free_list(t_env** list);
void    ft_print_list_char(t_env *list);
void    ft_lstadd_back(t_env **lst, t_env *new);
t_env   *ft_lstlast(t_env *lst);
t_env  *ft_lstnew(void *content);
char	*ft_strdup(char *str);




#endif

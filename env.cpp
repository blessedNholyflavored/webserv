#include <iostream>
#include <cstdlib>

typedef struct s_cgi
{
    

} t_cgi;


int main(int argc, char **argv, char **envp)
{
  for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);    
  }
  return 0;
}

//////////////////////////////////////////////
char    **ft_regroup_env(t_g *v)
{
    t_list    *tmp;
    char    **recup;
    int        len;
    int        i;

    tmp = v->list;
    if (v->env[0])
        tmp = tmp->next;
    len = ft_lstsize(tmp);
    recup = malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (tmp->next)
    {
        recup[i] = ft_strdup(tmp->line);
        i++;
        tmp = tmp->next;
    }
    recup[i] = ft_strdup(tmp->line);
    recup[i + 1] = 0;
    return (recup);
}

t_list    *init_lst(char **env, t_list *list)
{
    int        i;
    char    *name;
    char    *content;
    char    *line;

    name = NULL;
    content = NULL;
    i = -1;
    list = ft_lstnew(ft_strdup("toto"), ft_strdup("toto"), ft_strdup("toto"));
    while (env[++i])
    {
        name = malloc(sizeof(char) * (ft_lststrlen(env[i]) + 1));
        if (!ft_recup_name(name, env[i]))
            return (0);
        content = ft_strdup(env[i] + ft_strlen(name));
        line = ft_strdup(env[i]);
        ft_lstadd_back(&list, ft_lstnew(name, content, line));
    }
    return (list);
}

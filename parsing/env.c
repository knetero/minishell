/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:13:32 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:04:07 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_deleted_env_r(void)
{
	char	**envp;

	envp = malloc(sizeof(char *) * 2);
	if (!envp)
		return (NULL);
	envp[0] = ft_strdup("OLDPWD=");
	envp[1] = NULL;
	return (envp);
}

char	**fill_deleted_env(char	**envp)
{
	char	*cwd;

	envp = malloc(sizeof(char *) * 5);
	if (!envp)
		return (NULL);
	cwd = getcwd(NULL, 0);
	envp[0] = ft_strjoin(ft_strdup("PWD="), cwd);
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env");
	envp[3] = ft_strjoin(ft_strdup("PATH="), \
	_PATH_STDPATH);
	envp[4] = NULL;
	free(cwd);
	return (envp);
}

t_env	*ft_envnw(char *key)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_tmpliste));
	if (!list)
		return (NULL);
	list->key = key;
	list->value = NULL;
	list->next = NULL;
	return (list);
}

t_env	*fill_env(char	**envp, t_env *begin_env)
{
	t_env	*env;
	t_index	x;
	int		i;

	x.i = 0;
	i = 0;
	x.start = 0;
	env = NULL;
	if (!envp || !envp[0])
	{
		envp = fill_deleted_env(envp);
		i = 1;
	}
	help_envv(envp, &begin_env, env, x);
	if (i)
		ft_freetab(envp);
	return (begin_env);
}

void	ft_envclear(t_env **lst, void (*del)(void*))
{
	t_env	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->key);
		del((*lst)->value);
		free((*lst));
		(*lst) = p;
	}
	free(*lst);
}

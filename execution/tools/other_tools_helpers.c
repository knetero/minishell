/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:11:44 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 22:09:25 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exit_pipe(t_var *v)
{
	if (v->lst_size > 1)
	{
		g_global.status = 0;
		v->found++;
		return (1);
	}
	return (0);
}

char	*ft_strjoin_tab(char const *s1, char const *s2)
{
	char	*concat;
	size_t	len;

	if (!s1 || !s2)
	{
		if (s1)
		{
			return ((char *)s1);
		}
		return (NULL);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(len + 1);
	if (!concat)
		return (NULL);
	ft_memcpy(concat, s1, ft_strlen(s1));
	ft_memcpy(concat + ft_strlen(s1), s2, ft_strlen(s2));
	concat[len] = '\0';
	free((void *)s1);
	return (concat);
}

int	check_name_old(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

t_env	*return_old(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	cd_old(t_final *lst, t_env *env)
{
	t_env	*old;

	if (lst->cmd[0] && ft_strcmp(lst->cmd[1], "-") == 0)
	{
		old = return_old(env, "OLDPWD");
		if (old)
		{
			if (check_name_old(env, old->key))
				printf("%s\n", old->value);
			if (check_name_old(env, old->key))
				chdir(old->value);
		}
		else
		{
			g_global.status = 1;
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		}
		return (1);
	}
	return (0);
}

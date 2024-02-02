/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:02:16 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 03:52:52 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	replace_pwd(t_env *cd_b, t_env *cd_b_tmp, char *save_p, char *old_pwd)
{
	while (cd_b && cd_b->next)
	{
		if (ft_strcmp(cd_b->key, "PWD") != 0)
			cd_b = cd_b->next;
		else
		{
			free(cd_b->value);
			cd_b->value = ft_strdup(save_p);
			break ;
		}
	}
	while (cd_b_tmp && cd_b_tmp->next)
	{
		if (ft_strcmp(cd_b_tmp->key, "OLDPWD") != 0)
			cd_b_tmp = cd_b_tmp->next;
		else
		{
			free(cd_b_tmp->value);
			cd_b_tmp->value = ft_strdup(old_pwd);
			break ;
		}
	}
}

void	forward_dr(t_env *env, char *old_pwd, char *new_cwd)
{
	t_env	*tmp;

	tmp = env;
	while (env && env->next)
	{
		if (ft_strcmp(env->key, "PWD") != 0)
			env = env->next;
		else
		{
			if (place_dr(env, new_cwd) == 1)
				return ;
			break ;
		}
	}
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") != 0)
			tmp = tmp->next;
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
			break ;
		}
	}
}

void	back_dr(t_env *env, char *old_pwd)
{
	t_env	*cd_back;
	t_env	*cd_back_tmp;
	char	*save_pwd;

	save_pwd = getcwd(NULL, 0);
	if (save_pwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
		save_pwd = old_pwd;
		return ;
	}
	cd_back = env;
	cd_back_tmp = env;
	replace_pwd(cd_back, cd_back_tmp, save_pwd, old_pwd);
	free(save_pwd);
}

int	home_dr(t_env *env)
{
	t_env	*home_d;
	t_env	*tmp;

	home_d = env;
	tmp = env;
	while (home_d)
	{
		if (ft_strcmp(home_d->key, "HOME") != 0)
			home_d = home_d->next;
		else
		{
			if (chdir(home_d->value) == -1)
			{
				g_global.status = 1;
				perror("");
			}
			break ;
		}
	}
	if (!home_d)
		home_help();
	else
		set_pwd(env, home_d->value);
	return (0);
}

void	cd_built(t_final *lst, t_env *env, t_var *v)
{
	t_env	*tmp;
	char	*old_pwd;

	tmp = env;
	v->flag = 0;
	if (cd_old(lst, env) == 1)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		v->flag = 1;
		old_pwd = getenv("OLDPWD");
	}
	if (cd_home(lst, env) == 1)
	{
		if (old_pwd)
			free(old_pwd);
		return ;
	}
	else if (lst->cmd[0] && ft_strcmp(lst->cmd[1], "..") == 0)
		back_d(lst, env, old_pwd);
	else
		forward_d(lst, env, old_pwd, v->new_cwd);
	if (v->flag == 0)
		free(old_pwd);
}

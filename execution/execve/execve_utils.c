/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:41:58 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 22:10:39 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	duping(int _stdin, int _stdout, int save_stdin)
{
	dup2(_stdin, 0);
	if (_stdin != -1)
		close(_stdin);
	dup2(_stdout, 1);
	if (_stdout != -1)
		close(_stdout);
	if (save_stdin != -1)
		close(save_stdin);
}

char	**list_to_tab(t_env **env)
{
	t_env	*tmp;
	int		j;
	char	**tab;
	int		size;

	j = 0;
	tmp = (*env);
	size = ft_lstsize_env(*env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	while (tmp)
	{
		tab[j] = ft_strjoin_tab(ft_strdup(tmp->key), "=");
		tab[j] = ft_strjoin_tab(tab[j], tmp->value);
		j++;
		tmp = tmp->next;
	}
	tab[j] = NULL;
	return (tab);
}

char	*find_path(t_env *env)
{
	t_env	*tmp;
	char	*path;

	tmp = env;
	path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") != 0)
			tmp = tmp->next;
		else
		{
			path = tmp->value;
			break ;
		}
	}
	return (path);
}

char	**spliting_path(t_env *env, t_final *lst)
{
	t_env	*tmp;
	char	*path;
	char	**splited_path;
	int		i;

	i = 0;
	tmp = env;
	path = find_path(env);
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	while (splited_path[i])
	{
		splited_path[i] = ft_strjoin(splited_path[i], "/");
		splited_path[i] = ft_strjoin(splited_path[i], lst->cmd[0]);
		i++;
	}
	return (splited_path);
}

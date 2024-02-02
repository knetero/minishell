/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:18:35 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 22:11:46 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_path(char **splited_p, t_final *tmp, t_var *v)
{
	char	*str;

	path_not_found(tmp, splited_p, v);
	while (splited_p && splited_p[v->x])
	{
		if (((splited_p[v->x] && (access(splited_p[v->x], X_OK | R_OK) != -1))
				|| (access(tmp->cmd[0], X_OK | R_OK) != -1)
				|| (tmp->cmd[0][0] == '.' && tmp->cmd[0][1] == '/')))
		{
			str = splited_p[v->x];
			if (access(tmp->cmd[0], X_OK) != -1 
				|| (tmp->cmd[0][0] == '.' && tmp->cmd[0][1] == '/'))
				str = tmp->cmd[0];
			v->found++;
			ft_fork(tmp, str, v);
			if (v->fd[1] != -1)
				close(v->fd[1]);
			if (v->_stdin != -1)
				close(v->_stdin);
		}
		if (v->found)
			break ;
		v->x++;
	}
}

void	check_searchpath(char **splited_p, t_final *lst, t_var *v)
{
	if (ft_strcmp(lst->cmd[0], "") != 0)
		search_path(splited_p, lst, v);
}

int	builtin_or_command(t_final *tmp, char **splited_p, t_env **en, t_var *v)
{
	if (is_builtins(tmp) == 1) 
	{
		if (redirection(tmp) == 1)
			return (1);
		if (execution(tmp, en, v) == 1)
			return (1);
		v->found++;
	}
	else
		check_searchpath(splited_p, tmp, v);
	return (0);
}

void	executing_cmd(t_final *lst, t_env **env, t_var *v)
{
	t_final	*tmp;
	char	**splited_path;
	int		save[2];

	save[1] = dup(1);
	save[0] = dup(0);
	v->flag_rd = 0;
	tmp = lst;
	v->lst_size = ft_lstsize_lst(lst);
	while (tmp) 
	{
		v->_stdout = -1;
		splited_path = spliting_path(*env, tmp);
		v->x = 0;
		v->found = 0;
		if (tmp->next)
			piping(v);
		if (builtin_or_command(tmp, splited_path, env, v) == 0)
			check_if_found(tmp, splited_path, v);
		else
			ft_freetab(splited_path);
		v->_stdin = v->save_stdin;
		tmp = tmp->next;
	}
	save_fd(save[1], save[0]);
}

void	exec_command(t_final *lst, t_env **env)
{
	t_var	v;

	v.env_tab = list_to_tab(env);
	v._stdin = -1;
	v.fd[0] = -1;
	v.fd[1] = -1;
	v.save_stdin = -1;
	executing_cmd(lst, env, &v);
	ft_freetab(v.env_tab);
}

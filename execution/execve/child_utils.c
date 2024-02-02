/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:07:18 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 17:09:27 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	path_not_found(t_final *tmp, char **splited_p, t_var *v)
{
	if (!splited_p)
	{
		v->found++;
		v->child_pid = fork();
		if (v->child_pid == 0)
		{
			if (execve(tmp->cmd[0], tmp->cmd, v->env_tab) == -1)
			{
				my_error(tmp);
				exit(127);
			}
		}
	}
}

void	piping(t_var *v)
{
	if (pipe(v->fd) == -1)
		ft_putstr_fd("Error in pipe\n", 2);
	v->_stdout = v->fd[1];
	v->save_stdin = v->fd[0];
}

void	ft_fork(t_final *tmp, char *str, t_var *v)
{
	v->child_pid = fork();
	if (v->child_pid == 0)
	{
		if_found(tmp, str);
		duping(v->_stdin, v->_stdout, v->save_stdin);
		if (redirection(tmp) == 1)
		{
			v->found++;
			exit(1);
		}
		if (execve(str, tmp->cmd, v->env_tab) == -1)
		{
			my_error(tmp);
			exit(126);
		}
		exit (0);
	}
}

void	my_error_rd(void)
{
	ft_putstr_fd("Minishell:", 2);
	ft_putstr_fd(" ", 2);
	perror("");
}

void	if_found(t_final *tmp, char *str)
{
	if (access(str, R_OK) == -1)
	{
		my_error(tmp);
		exit(127);
	}
	else
	{
		if (access(str, X_OK) == -1)
		{
			my_error(tmp);
			exit(126);
		}
	}
}

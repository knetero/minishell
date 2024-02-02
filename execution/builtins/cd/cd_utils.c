/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:42:59 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 08:10:44 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	home_help(void)
{
	g_global.status = 1;
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

void	forward_d(t_final *lst, t_env *env, char *old_pwd, char *new_cwd)
{
	if (chdir(lst->cmd[1]) == -1)
		my_perror(lst);
	else
		forward_dr(env, old_pwd, new_cwd);
}

void	back_d(t_final *lst, t_env *env, char *old_pwd)
{
	if (chdir(lst->cmd[1]) == -1)
		perror("");
	else
		back_dr(env, old_pwd);
}

void	p_error(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}

void	my_error(t_final *lst)
{
	ft_putstr_fd("Minishell:", 2);
	if (lst->cmd[0])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[0], 2);
		ft_putstr_fd(": ", 2);
	}
	perror("");
}

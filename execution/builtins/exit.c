/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:25:22 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/18 18:23:54 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	p_error_exit(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	ft_putstr_fd(":", 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}

int	parse_arg_e(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' || s[i] == '-')
			i++;
		if (ft_isdigit(s[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

int	get_size(t_final *lst)
{
	int	i;

	i = 2;
	while (lst->cmd && lst->cmd[i])
		i++;
	return (i);
}

void	exit_built(t_final *lst, t_var *v)
{
	v->y = 2;
	printf("exit\n");
	if (lst->cmd[0] && !lst->cmd[1])
	{
		free_lst(lst);
		exit(0);
	}
	if (lst->cmd[0] && lst->cmd[1])
	{
		v->y = get_size(lst);
		if (parse_arg_e(lst->cmd[1]) == 1)
		{
			p_error_exit(lst, ": numeric argument required\n", 1);
			exit(255);
		}
		else if (v->y > 2)
		{
			g_global.status = 127;
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			return ;
		}
		exit(ft_atoi(lst->cmd[1]));
	}
}

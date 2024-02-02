/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:41:05 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/18 21:37:49 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	search_env(t_env *env, char *search)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	free_and_exit(char **tab)
{
	ft_freetab(tab);
	return ;
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	cd_parse(t_final *lst)
{
	if (ft_strcmp(lst->cmd[0], "Cd") == 0
		|| ft_strcmp(lst->cmd[0], "cD") == 0
		|| ft_strcmp(lst->cmd[0], "CD") == 0)
		return (1);
	return (0);
}

void	p_error_export(t_final *lst, char *s, int j)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	if (lst->cmd[j])
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(lst->cmd[j], 2);
	}
	ft_putstr_fd(s, 2);
}

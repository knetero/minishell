/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:03:19 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/18 21:11:39 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_lst(t_final *lst)
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

t_redirect	*ft_lstlast_red(t_redirect *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	loop_arg(t_final *lst, int i, int j)
{
	while (lst->cmd[i][j])
	{
		if (parse_unset(lst, i, j) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	echo_home(t_final *lst)
{
	char	*s;

	s = getenv("HOME");
	if (ft_strcmp(lst->cmd[1], "~") == 0)
	{
		if (!s)
			return (ft_putstr_fd("HOME not set\n", 2), 1);
		printf("%s\n", s);
		return (1);
	}
	return (0);
}

int	check_name(t_final *lst)
{
	if (ft_strcmp(lst->cmd[1], "unset") == 0)
		return (1);
	return (0);
}

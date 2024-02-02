/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:36:08 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/19 03:48:05 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_in(char *string, char c)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_token(char *string)
{
	if (ft_strcmp(string, ">>") == 0 || ft_strcmp(string, "<<") == 0)
		return (1);
	else if (ft_strcmp(string, ">") == 0 || ft_strcmp(string, "<") == 0)
		return (1);
	else if (ft_strcmp(string, "><") == 0 || ft_strcmp(string, "<>") == 0)
		return (-1);
	return (0);
}

int	iss_token(char *string, int q)
{
	if ((ft_strcmp(string, ">>") == 0
			|| ft_strcmp(string, "<<") == 0) && q == 0)
		return (1);
	else if ((ft_strcmp(string, ">") == 0
			|| ft_strcmp(string, "<") == 0) && q == 0)
		return (1);
	else if ((ft_strcmp(string, "><") == 0
			|| ft_strcmp(string, "<>") == 0) && q == 0)
		return (-1);
	else
		return (0);
}

int	is_id(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	cmd_len(t_tmpliste	*prev)
{
	t_tmpliste	*cur;
	int			i;

	i = 0;
	cur = prev;
	while (cur && (cur->quotes != -2))
	{
		if (cur->arg != NULL && cur->quotes != -1 && cur->quotes != -1)
			i++;
		cur = cur->next;
	}
	return (i);
}

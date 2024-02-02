/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:14:42 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:04:02 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstad_back(t_tmpliste **lst, t_tmpliste *new)
{
	t_tmpliste	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	add_final_back(t_final **lst, t_final *new)
{
	t_final	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	ft_redct_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*tmp;

	tmp = (*lst);
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_tmpliste	*add_node(t_tmpliste *prev, char *content)
{
	t_tmpliste	*node;
	t_tmpliste	*tmp;

	if (!prev)
		return (NULL);
	node = ft_lstnw(content, 0);
	tmp = prev->next;
	prev->next = node;
	node->next = tmp;
	return (node);
}

t_tmpliste	*add_node_(t_tmpliste *prev, char *s, int q)
{
	t_tmpliste	*node;
	t_tmpliste	*tmp;

	if (!prev)
		return (NULL);
	node = ft_lstnw(s, q);
	tmp = prev->next;
	prev->next = node;
	node->next = tmp;
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:19:38 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 01:29:30 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_deletenode(t_tmpliste **begin_list, t_tmpliste *node)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = *begin_list;
	prev = NULL;
	if (cur == node)
	{
		*begin_list = node->next;
		free(node->arg);
		free(node);
		return ;
	}
	while (cur != NULL)
	{
		if (cur == node)
		{
			prev->next = cur->next;
			free(cur->arg);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_deletespace(t_tmpliste **begin_list)
{
	t_tmpliste	*cur;

	cur = *begin_list;
	if (cur == NULL)
		return ;
	while (cur->next != NULL)
	{
		if ((cur)->quotes == -1 && (cur)->next->quotes == -1)
			cur = rm_node(begin_list, cur->next);
		else
			cur = cur->next;
	}
}

void	delete_empty(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = cur;
	while (cur)
	{
		if ((cur->next) && (cur->next->arg == NULL))
			cur = rm_node(tmp, cur->next);
		else
			cur = cur->next;
		prev = cur;
	}
}

void	deletesp(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = cur;
	while (cur)
	{
		prev = cur;
		if (cur->quotes == -1 && cur->next
			&& (iss_token(cur->next->arg, cur->next->quotes) == 1
				|| cur->next->quotes == -2))
			cur = rm(tmp, cur);
		else if (cur->quotes == -2 || iss_token(cur->arg, cur->quotes) == 1)
		{
			if ((cur->next) && cur->next->quotes == -1)
				cur = rm(tmp, cur->next);
			else
				cur = cur->next;
		}
		else
			cur = cur->next;
	}
}

t_tmpliste	*rm_node(t_tmpliste **begin_list, t_tmpliste *node)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = *begin_list;
	prev = NULL;
	if (cur == node)
	{
		*begin_list = node->next;
		free(node->arg);
		free(node);
		return (*begin_list);
	}
	while (cur != NULL)
	{
		if (cur == node)
		{
			prev->next = cur->next;
			free(cur->arg);
			free(cur);
			return (prev);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

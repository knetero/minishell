/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:56:11 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 00:30:53 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handel_pipe(t_tmpliste *tmp)
{
	t_tmpliste	*cur;

	cur = tmp;
	if (cur != NULL && cur->quotes == -2)
		return (0);
	return (help_syntax(cur, tmp));
}

t_tmpliste	*rm(t_tmpliste **begin_list, t_tmpliste *node)
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
			return (prev->next);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

int	lstsize(t_tmpliste *lst)
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

void	ft_join(t_tmpliste **tmp, int fd)
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;

	cur = (*tmp);
	prev = NULL;
	while (cur)
	{
		prev = cur;
		if (cur->quotes != -1 && cur->quotes != -2)
		{
			cur = cur->next;
			if (cur != NULL)
				fd = cur->fd;
			while (cur && (cur->quotes != -1 && cur->quotes != -2 
					&& iss_token(cur->arg, cur->quotes) == 0))
			{
				prev->arg = ft_strjoin(prev->arg, cur->arg);
				prev->fd = fd;
				ft_deletenode(tmp, prev->next);
				cur = prev->next;
			}
		}
		else
			cur = cur->next;
	}
}

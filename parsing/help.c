/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:44:18 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 13:30:11 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_1(t_s *s)
{
	s->s = ft_itoa(g_global.status);
	s->len = s->len - 2 + ft_strlen(s->s);
	s->i += 2;
	free(s->s);
	s->s = NULL;
	return (s->i);
}

int	do_2(t_s *s, char	*arg, t_env *env)
{
	s->start = ++s->i;
	while (is_id(arg[s->i]) == 1)
		s->i++;
	if (s->i > s->start)
	{
		s->s = ft_substr(arg, s->start, (s->i - s->start));
		s->str = getenv_(s->s, env);
		s->len = s->len - ft_strlen(s->s) + ft_strlen(s->str) - 1;
		free(s->str);
		free(s->s);
	}
	return (s->i);
}

t_tmpliste	*ft_lstnw(char *content, int quotes)
{
	t_tmpliste	*list;

	list = (t_tmpliste *)malloc(sizeof(t_tmpliste));
	if (!list)
		return (NULL);
	list->arg = content;
	list->quotes = quotes;
	list->fd = -1;
	list->redct = NULL;
	list->next = NULL;
	return (list);
}

bool	balanced_quotes(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			s = ft_strchr(str + i + 1, str[i]);
			if (s != NULL)
			{
				str = s;
				i = 0;
			}
			else
			{
				printf("Minishell : unbalanced quotation \n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_stclear(t_tmpliste **lst, void (*del)(void*))
{
	t_tmpliste	*p;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		free((*lst)->arg);
		(*lst)->arg = NULL;
		if ((*lst)->redct)
		{
			if ((*lst)->redct->file)
				free((*lst)->redct->file);
			free((*lst)->redct);
		}
		free((*lst));
		(*lst) = p;
	}
	free(*lst);
	(*lst) = NULL;
}

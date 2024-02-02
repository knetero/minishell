/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:40:18 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:03:38 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirection(t_tmpliste **begin_list, int k)
{
	t_tmpliste	*cur;
	int			i;
	char		*tmp;

	cur = *begin_list;
	i = 0;
	while (cur)
	{
		if (cur->quotes == 0)
		{
			tmp = ft_strdup(cur->arg);
			free(cur->arg);
			cur->arg = ft_check_cmd(tmp, &i);
			cur = ft_check_redirect(tmp, cur, &i, k);
			free(tmp);
			i = 0;
		}
		cur = cur->next;
	}
}

t_tmpliste	*ft_red1(char	*arg, int	*i, t_tmpliste	*red, int k)
{
	t_tmpliste	*node;

	node = NULL;
	if (arg[*i] && (arg[*i] == '>' || arg[*i] == '<'))
	{
		(*i)++;
		if (arg[(*i)] && (arg[*i] == '>' || arg[*i] == '<'))
		{
			node = add_node(red, ft_substr(arg, (*i) - 1, 2));
			k = ++(*i);
		}
		else
		{
			node = add_node(red, ft_substr(arg, (*i) - 1, 1));
			k = (*i);
		}
		while (arg[(*i)] && not_in("|><", arg[(*i)]) == 0)
			(*i)++;
		if ((*i) > k)
			node = add_node(node, ft_substr(arg, k, (*i) - k));
	}
	return (node);
}

t_redirect	*ft_rednw(int token)
{
	t_redirect	*list;

	list = (t_redirect *)malloc(sizeof(t_redirect));
	if (!list)
		return (NULL);
	list->token = token;
	list->file = NULL;
	list->next = NULL;
	return (list);
}

void	collect_red(t_tmpliste	**tmp)
{
	t_tmpliste	*cur;
	int			i;

	i = 0;
	cur = (*tmp);
	while (cur)
	{
		if (cur->arg && (cur->quotes == 0 && (cur->arg[0] == '>'
					|| cur->arg[0] == '<')))
		{
			if (cur->arg[1] == '>' || cur->arg[1] == '<')
				i = collect_help1(&cur);
			else
				i = collect_help(&cur, cur->arg, cur->quotes);
			cur->redct->file = ft_substr(cur->arg, i, ft_strlen(cur->arg));
			free(cur->arg);
			cur->arg = NULL;
			cur = cur->next;
		}
		else
			cur = cur->next;
	}
}

int	collect_help(t_tmpliste	**cur, char	*s, int q)
{
	char	*key;

	key = ft_substr(s, 0, 1);
	(*cur)->redct = ft_rednw(gett_token(key, q));
	free(key);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfinal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:51 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 01:28:30 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expandd_2(t_ex	*ex, char	*s, t_env	*env)
{
	char	*key;

	ex->start = ++ex->i;
	while (s[ex->i] && is_id(s[ex->i]) == 1)
		ex->i++;
	if (ex->i > ex->start)
	{
		key = ft_substr(s, ex->start, ex->i - ex->start);
		ex->expnd = getenv_(key, env);
		free(key);
		if (ex->expnd != NULL)
		{
			ex->x = 0;
			while (ex->expnd[ex->x])
				ex->res[ex->j++] = ex->expnd[ex->x++];
			free(ex->expnd);
		}
	}
	return (ex->i);
}

int	expand_2(t_ex	*ex, char	*s, t_env	*env, t_tmpliste *cur)
{
	char	*key;

	ex->start = ++ex->i;
	while (s[ex->i] && is_id(s[ex->i]) == 1)
		ex->i++;
	if (ex->i > ex->start)
	{
		key = ft_substr(s, ex->start, ex->i - ex->start);
		ex->expnd = getenv_(key, env);
		free(key);
		if (ex->expnd != NULL)
		{
			ex->x = 0;
			while (ex->expnd[ex->x])
				ex->res[ex->j++] = ex->expnd[ex->x++];
			cur->quotes = -4;
			free(ex->expnd);
		}
	}
	return (ex->i);
}

t_final	*fill_final(t_tmpliste **tmp)
{
	t_tmpliste	*cur;
	t_final		*fhead;
	int			len;

	cur = (*tmp);
	fhead = NULL;
	len = cmd_len(cur);
	while (cur)
	{
		cur = help_final(&fhead, cur, len);
		if (cur != NULL)
			cur = cur->next;
		else
			return (fhead);
		len = cmd_len(cur);
	}
	return (fhead);
}

t_final	*new_final(int len)
{
	t_final	*list;

	list = (t_final *)malloc(sizeof(t_final));
	if (!list)
		return (NULL);
	list->cmd = malloc(sizeof(char *) * (len + 1));
	if (!list->cmd)
		return (NULL);
	list->fd = -1;
	list->rdct = NULL;
	list->next = NULL;
	return (list);
}

char	*getenv_(char	*key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

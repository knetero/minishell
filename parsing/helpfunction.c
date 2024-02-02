/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:00:25 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:03:16 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

void	help_envv(char	**envp, t_env **begin_env, t_env	*env, t_index	x)
{
	while (envp && envp[x.i])
	{
		x.j = 0;
		while (envp[x.i] && envp[x.i][x.j] && envp[x.i][x.j] != '=')
			x.j++;
		env = ft_envnw(ft_substr(envp[x.i], 0, x.j));
		x.start = ++x.j;
		while (envp[x.i][x.j] && envp[x.i][x.j] != '\0')
			x.j++;
		env->value = ft_substr(envp[x.i], x.start, x.j - x.start);
		if (ft_strcmp(env->key, "SHLVL") == 0 && ft_atoi(env->value) >= 1)
			env->value = dup_value(env->value);
		ft_add_env(begin_env, env);
		x.i++;
	}
}

int	ft_if(char *s, int i)
{
	if (s[i] != '$' || (s[i] == '$' && !s[i + 1]) 
		|| (s[i] == '$' && s[i + 1]
			&& ((s[i + 1] == '$') || is_id(s[i + 1]) == 0)))
	{
		return (0);
	}
	else
		return (1);
}

void	help_heredoc(t_strct *s, t_tmpliste **tmp, t_env *env, int q)
{
	while (s->cur)
	{
		if (s->cur->quotes == 0 && ft_strcmp(s->cur->arg, "<<") == 0)
		{
			s->prev = s->cur;
			s->cur = s->cur->next;
			s->str = ft_strdup("");
			while (s->cur && (s->cur->quotes != -2 && s->cur->quotes != -1
					&& iss_token(s->cur->arg, s->cur->quotes) != 1))
			{
				s->str = ft_strjoin(s->str, s->cur->arg);
				if (s->cur->quotes > 0)
					q = s->cur->quotes;
				s->cur = rm(tmp, s->cur);
			}
			s->cur = add_node_(s->prev, s->str, q);
			if (s->cur != NULL)
			{
				ft_hendel_heredoc(s->cur, env);
				s->cur = s->cur->next;
			}
		}
		else
			s->cur = s->cur->next;
	}
}

int	if_help(t_tmpliste *cur)
{
	if ((cur == NULL || cur->quotes == -2)
		|| (cur->quotes == -1 && cur->next->quotes == -2))
		return (0);
	else
		return (1);
}

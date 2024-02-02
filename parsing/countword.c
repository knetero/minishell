/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:23:59 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 13:27:41 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countwords(const char *str, char c)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && c == str[i])
			i++;
		if (str[i])
			k++;
		while (str[i] && c != str[i])
			i++;
	}
	return (k);
}

char	*expand(char	*s, t_env *env)
{
	t_ex	*ex;
	char	*res;

	ex = malloc(sizeof(t_ex));
	ex->i = 0;
	ex->j = 0;
	ex->start = 0;
	ex->len = nw_lenght(s, env);
	ex->res = malloc(sizeof(char) * (ex->len + 1));
	if (ex->res == NULL)
		return (NULL);
	while (s[ex->i])
	{
		if (s[ex->i] != '$' || (s[ex->i] == '$' && !s[ex->i + 1])
			|| (s[ex->i] == '$' && s[ex->i + 1]
				&& ((s[ex->i + 1] == '$') || is_id(s[ex->i + 1]) == 0)))
			ex->res[ex->j++] = s[ex->i++];
		else if (s[ex->i] == '$' && s[ex->i + 1] && s[ex->i + 1] == '?')
			expand_1(ex);
		else if (s[ex->i] == '$')
			expandd_2(ex, s, env);
	}
	ex->res[ex->j] = '\0';
	res = ft_strdup(ex->res);
	return (free(s), free(ex->res), free(ex), res);
}

void	show_final(t_final	*f)
{
	int	i;

	i = 0;
	while (f)
	{
		i = 0;
		while (f->cmd[i] != NULL)
		{
			printf("----cmd %d: %s\n", i, f->cmd[i]);
			i++;
		}
		while (f->rdct != NULL)
		{
			printf("**red (%d): %d    (%s)  fd :(%d)\n", i,
				f->rdct->token, f->rdct->file, f->fd);
			f->rdct = f->rdct->next;
		}
		f = f->next;
	}
}

void	delete_final(t_final **fin)
{
	t_final		*tmp;
	t_final		*f;

	f = (*fin);
	while (f)
	{
		tmp = f->next;
		free(f->cmd);
		free(f);
		f = tmp;
	}
}

void	ft_isexpand(t_tmpliste **lst)
{
	t_help		help;
	t_tmpliste	*cur;

	cur = (*lst);
	help.i = 0;
	while (cur)
	{
		if (cur->quotes == -4 && countwords(cur->arg, ' ') > 1)
		{
			help.s = ft_split(cur->arg, ' ');
			while (help.s[help.i])
			{
				if (help.i == 0)
				{
					free(cur->arg);
					cur->arg = ft_strdup(help.s[help.i]);
				}
				else
					cur = add_node(cur, ft_strdup(help.s[help.i]));
				help.i++;
			}
			ft_freetab(help.s);
		}
		cur = cur->next;
	}
}

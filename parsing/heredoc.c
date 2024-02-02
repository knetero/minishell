/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:10:27 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:04:13 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(t_tmpliste **tmp, t_env	*env)
{
	t_strct	s;
	int		q;

	q = 0;
	s.cur = (*tmp);
	help_heredoc(&s, tmp, env, q);
	g_global.exitc = 1;
}

int	ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env)
{
	char	*line;
	int		fildes[2];
	char	*save;

	pipe(fildes);
	while (g_global.exitc)
	{
		signal (SIGINT, c_inheredoc);
		line = readline(">");
		if (ft_strcmp(line, h_doc->arg) == 0 || line == NULL)
			break ;
		if (h_doc->quotes == 0)
			line = expand(line, env);
		save = line;
		line = ft_strjoin(save, "\n");
		write(fildes[1], line, ft_strlen(line));
		free(line);
	}
	if (ft_strcmp(line, h_doc->arg) == 0 || line == NULL)
		free(line);
	close(fildes[1]);
	h_doc->fd = fildes[0];
	signal (SIGINT, c_handler);
	return (fildes[0]);
}

void	ft_expanding(t_tmpliste **tmp, t_env	*env)
{
	t_tmpliste	*cur;

	cur = (*tmp);
	if (!cur)
		return ;
	while (cur)
	{
		if (cur->arg && (cur->quotes == 0 || cur->quotes == 2))
			cur->arg = expandd(cur->arg, env, cur);
		cur = cur->next;
	}
}

char	*expandd(char *s, t_env *env, t_tmpliste *cur)
{
	t_ex	*x;
	char	*res;

	x = malloc(sizeof(t_ex));
	if (!x)
		return (NULL);
	x->i = 0;
	x->j = 0;
	x->start = 0;
	x->len = nw_lenght(s, env);
	x->res = malloc(sizeof(char) * (x->len + 1));
	if (!x->res)
		return (NULL);
	while (s[x->i])
	{
		if (s[x->i] == '$' && s[x->i + 1] && s[x->i + 1] == '?')
			x->i = expand_1(x);
		else if (ft_if(s, x->i) == 0)
			x->res[x->j++] = s[x->i++];
		else if (s[x->i] == '$')
			x->i = expand_2(x, s, env, cur);
	}
	x->res[x->j] = '\0';
	res = ft_strdup(x->res);
	return (free(s), free(x->res), free(x), res);
}

int	expand_1(t_ex	*ex)
{
	ex->x = 0;
	ex->expnd = ft_itoa(g_global.status);
	while (ex->expnd[ex->x])
		ex->res[ex->j++] = ex->expnd[ex->x++];
	ex->i += 2;
	free(ex->expnd);
	return (ex->i);
}

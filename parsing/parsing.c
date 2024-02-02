/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:24:07 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 15:04:55 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_cmd(char *arg, int	*i)
{
	int		start;
	char	*cmd;

	cmd = NULL;
	start = (*i);
	while ((arg[*i] && arg[*i] != '>' && arg[*i] != '<'))
		(*i)++;
	if ((*i) > start)
		cmd = ft_substr(arg, start, (*i) - start);
	return (cmd);
}

t_tmpliste	*ft_check_redirect(char	*arg, t_tmpliste	*red, int	*i, int k)
{
	t_tmpliste	*tmp;

	if ((*i) == sstrlen(arg))
		return (red);
	tmp = red;
	while (arg[*i])
		tmp = ft_red1(arg, i, tmp, k);
	return (tmp);
}

t_tmpliste	*ft_splt(char *ss)
{
	int			i;
	t_tmpliste	*head;

	head = NULL;
	i = 0;
	while (ss && ss[i])
	{
		if (ss[i] == ' ' || ss[i] == '|')
			ft_spacepipe(&head, ss, &i);
		else if (ss[i] == '\'' || ss[i] == '\"')
			ft_quotes(&head, ss, &i);
		else
			ft_string(&head, ss, &i);
		i++;
	}
	free (ss);
	return (head);
}

void	ft_spacepipe(t_tmpliste **head, char *s, int *i)
{
	t_tmpliste	*liste;
	char		*ss;

	liste = NULL;
	ss = ft_substr(s, *i, 1);
	if (s[*i] == ' ')
		liste = ft_lstnw(ft_strdup(ss), -1);
	else if (s[*i] == '|')
		liste = ft_lstnw(ft_strdup(ss), -2);
	free(ss);
	ft_lstad_back(head, liste);
}

void	ft_quotes(t_tmpliste **head, char *s, int *i)
{
	int			start;
	t_tmpliste	*liste;

	liste = NULL;
	start = (*i)++;
	while (s[*i] != s[start] && s[*i])
		(*i)++;
	if (s[start] == '\'')
		liste = ft_lstnw(ft_substr(s, start + 1, *i - start - 1), 1);
	else
		liste = ft_lstnw(ft_substr(s, start + 1, *i - start - 1), 2);
	ft_lstad_back(head, liste);
}

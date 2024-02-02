/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:31:30 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 20:03:05 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_string(t_tmpliste **head, char *s, int *i)
{
	t_tmpliste	*liste;
	int			start;

	liste = NULL;
	start = *i;
	while (s[*i] != ' ' && s[*i] != '|' && s[*i] != '\0' && s[*i] != '\''
		&& s[*i] != '\"')
		(*i)++;
	liste = ft_lstnw(ft_substr(s, start, (*i) - start), 0);
	ft_lstad_back(head, liste);
	(*i)--;
}

bool	syntax_error(t_tmpliste *tmp)
{
	if (handel_pipe(tmp) == 0)
	{
		g_global.status = 258;
		printf("minishell: Syntax Error\n");
		return (0);
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	sstrlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

bool	help_syntax(t_tmpliste *cur, t_tmpliste *tmp)
{
	while (cur)
	{
		if (cur->quotes == -2)
		{
			cur = cur->next;
			if (if_help(cur) == 0)
				return (0);
		}
		else if (is_token(tmp->arg) == 1 && tmp->quotes == 0)
		{
			tmp = tmp->next;
			if (tmp && tmp->quotes == -1)
				tmp = tmp->next;
			if (!tmp || ((tmp->quotes == 0
						&& iss_token(tmp->arg, tmp->quotes) == 1)
					|| tmp->quotes == -2))
				return (0);
		}
		else
		{
			cur = cur->next;
			tmp = cur;
		}
	}
	return (1);
}

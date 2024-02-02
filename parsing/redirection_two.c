/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:43:37 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 15:43:12 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_error(t_tmpliste	*liste)
{
	t_tmpliste	*cur;

	cur = liste;
	while (cur)
	{
		if (iss_token(cur->arg, cur->quotes) == -1)
		{
			g_global.status = 258;
			printf("minishell: Syntax Error\n");
			return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

t_redirect	*copy_red(int token, char	*file)
{
	t_redirect	*list;

	list = (t_redirect *)malloc(sizeof(t_redirect));
	if (!list)
		return (NULL);
	list->token = token;
	list->file = file;
	list->next = NULL;
	return (list);
}

t_final	*ft_help1(t_tmpliste *liste, t_env **env)
{
	t_final	*f;
	int		fd;

	fd = -1;
	f = NULL;
	deletesp(&liste);
	ft_heredoc(&liste, *env);
	ft_expanding(&liste, *env);
	ft_join(&liste, fd);
	collect_red(&liste);
	ft_isexpand(&liste);
	f = fill_final(&liste);
	exec_command(f, env);
	exit_status();
	delete_final(&f);
	return (f);
}

t_tmpliste	*help_final(t_final	**fhead, t_tmpliste	*cur, int len)
{
	t_redirect	*nw;
	t_final		*final;
	int			i;

	i = 0;
	final = new_final(len);
	while (cur && cur->quotes != -2)
	{
		if (cur->arg != NULL && cur->quotes != -1)
		{
			final->cmd[i++] = cur->arg;
		}
		else if (cur->redct != NULL)
		{
			if (cur->redct->token == HEREDOC && cur->fd != -1)
				final->fd = cur->fd;
			nw = cur->redct;
			ft_redct_back(&final->rdct, nw);
		}
		cur = cur->next;
	}
	final->cmd[len] = NULL;
	add_final_back(fhead, final);
	return (cur);
}

bool	ft_help(char	*input, t_env	**env)
{
	int			k;
	t_tmpliste	*liste;
	char		*ss;

	k = 0;
	liste = NULL;
	ss = ft_strtrim(input, " \t");
	if (ft_strcmp(ss, "") != 0)
		add_history(ss);
	free(input);
	if (balanced_quotes(ss) == 1)
	{
		liste = ft_splt(ss);
		ft_deletespace(&liste);
		ft_redirection(&liste, k);
		delete_empty(&liste);
		if (syntax_error(liste) == 0 || red_error(liste) == -1)
			return (ft_stclear(&liste, free), 0);
		else
			ft_help1(liste, env);
		ft_stclear(&liste, free);
	}
	else
		free(ss);
	return (1);
}

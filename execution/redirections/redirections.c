/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:30:16 by abazerou          #+#    #+#             */
/*   Updated: 2023/08/20 17:07:55 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	out_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
	{
		g_global.status = 1;
		return (my_error_rd(), 1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	input_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_RDONLY, 0777);
	if (fd == -1)
	{
		g_global.status = 1;
		return (my_error_rd(), 1);
	}
	if (access(lst->rdct->file, R_OK) == -1)
	{
		g_global.status = 1;
		return (my_error_rd(), 1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	appand_red(t_final *lst)
{
	int	fd;

	fd = open(lst->rdct->file, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
	{
		g_global.status = 1;
		return (my_error_rd(), 1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

void	herdoc_red(t_final *lst)
{
	t_redirect	*red;

	red = lst->rdct;
	red = ft_lstlast_red(red);
	dup2(lst->fd, 0);
	close(lst->fd);
}

int	redirection(t_final *lst)
{
	if (lst->rdct)
	{
		while (lst->rdct)
		{
			if (lst->rdct->token == OUT)
			{
				if (out_red(lst) == 1)
					return (1);
			}
			else if (lst->rdct->token == IN)
			{
				if (input_red(lst) == 1)
					return (1);
			}
			else if (lst->rdct->token == APPEND)
			{
				if (appand_red(lst) == 1)
					return (1);
			}
			else if (lst->rdct->token == HEREDOC)
				herdoc_red(lst);
			lst->rdct = lst->rdct->next;
		}
	}
	return (0);
}

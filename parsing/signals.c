/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:39:47 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 22:36:53 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
	{
	}
	if (WIFSIGNALED(status))
	{
		if (g_global.flag == 1)
			g_global.status = 1;
		if (status == 2)
			g_global.status = 128 + status;
		else if (status == 3)
			g_global.status = 128 + status;
	}
	if (WIFEXITED(status) && g_global.status == 0)
		g_global.status = WEXITSTATUS(status);
}

void	c_handler(int signum)
{
	(void)signum;
	g_global.status = 1;
	if (waitpid(0, NULL, WNOHANG))
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		return ;
	}
}

int	get_token(char	*s)
{
	if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, ">") == 0)
		return (OUT);
	else if (ft_strcmp(s, "<") == 0)
		return (IN);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	return (-1);
}

int	gett_token(char	*s, int q)
{
	if (ft_strcmp(s, ">>") == 0 && q == 0)
		return (APPEND);
	else if (ft_strcmp(s, ">") == 0 && q == 0)
		return (OUT);
	else if (ft_strcmp(s, "<") == 0 && q == 0)
		return (IN);
	else if (ft_strcmp(s, "<<") == 0 && q == 0)
		return (HEREDOC);
	return (-1);
}

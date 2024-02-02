/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:35:59 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 22:35:59 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_exit(void)
{
	printf("\033[11C");
	printf("\033[1A");
	printf("exit\n");
	exit(0);
}

void	c_inheredoc(int num)
{
	if (num == SIGINT)
	{
		g_global.status = 1;
		g_global.flag = 1;
		ioctl(0, TIOCSTI, "\4");
		g_global.exitc = 0;
	}
}

char	*dup_value(char	*value)
{
	int	k;

	k = ft_atoi(value);
	free(value);
	return (ft_itoa(k + 1));
}

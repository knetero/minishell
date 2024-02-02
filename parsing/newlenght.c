/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlenght.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:48:39 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 00:44:01 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nw_lenght(char	*arg, t_env	*env)
{
	t_s	*s;
	int	len;

	s = malloc(sizeof(t_s));
	if (!s)
		return (0);
	s->i = 0;
	s->start = 0;
	s->len = ft_strlen(arg);
	if (!arg)
		return (-1);
	while (arg[s->i])
	{
		if (arg[s->i] == '$' && arg[s->i + 1] && arg[s->i + 1] == '?')
			s->i = do_1(s);
		else if (arg[s->i] == '$')
			s->i = do_2(s, arg, env);
		else
			s->i++;
	}
	len = s->len;
	free(s);
	return (len);
}

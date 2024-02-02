/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:56:48 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/20 22:36:36 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	g_global;

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env_struct;
	t_env		*begin_env;

	(void)av;
	begin_env = NULL;
	g_global.status = 0;
	g_global.exitc = 1;
	g_global.flag = 0;
	if (ac != 1)
		return (printf("No such file or directory\n"), 1);
	rl_catch_signals = 0;
	signal(SIGINT, &c_handler);
	signal(SIGQUIT, &quit_handler);
	env_struct = fill_env(envp, begin_env);
	while (1)
	{
		input = readline("Minishell$ ");
		if (input == NULL)
			write_exit();
		ft_help(input, &env_struct);
	}
	ft_envclear(&env_struct, free);
	return (0);
}

int	collect_help1(t_tmpliste	**cur)
{
	int		i;
	char	*key;

	free((*cur)->redct);
	key = ft_substr((*cur)->arg, 0, 2);
	(*cur)->redct = ft_rednw(gett_token(key, (*cur)->quotes));
	free(key);
	i = 2;
	return (i);
}

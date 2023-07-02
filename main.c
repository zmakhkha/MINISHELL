/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-fil <ayel-fil@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:52:21 by zmakhkha          #+#    #+#             */
/*   Updated: 2023/07/02 17:30:58 by ayel-fil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_global	g_glob = {.g_ctrl_c = 0, .g_ctrl_s = 0, .g_status = 0};
// void	l(void)
// {
// 	system("leaks minishell");
// }

// void	detect(void	*res)
// {
// 		// puts("\n");
// 		printf("\nHADA: %p,\n", res);
// 		// puts("\n");
// }

void	ft_child_handler(int signal)
{
	if (getpid() != getppid())
	{
		if (signal == SIGINT || signal == SIGTERM)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			exit(0);
		}
	}
}

void	ft_main_handler(int signal)
{
	rl_catch_signals = 0;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_child(void)
{
	struct sigaction	signal;

	signal.sa_handler = (void (*)(int))ft_child_handler;
	sigemptyset(&signal.sa_mask);
	signal.sa_handler = ft_child_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_signal_main(void)
{
	struct sigaction	signal;

	signal.sa_handler = (void (*)(int))ft_main_handler;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_signal_ignore(void)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	sigemptyset(&signal.sa_mask);
	// signal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal, NULL);
}

int	main(int ac, char **av, char **env)
{
	rl_catch_signals = 0;
	rl_initialize();
	ft_signal_main();
	if (ac != 1 || av[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	ft_prompt(env);
	return (0);
}

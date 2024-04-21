/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichompo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:09:36 by jichompo          #+#    #+#             */
/*   Updated: 2024/04/21 14:09:38 by jichompo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h> // need to remove

void	ft_reset(byte_t	*char_receive, pid_t *client_pid)
{
	write (1, &char_receive->c, 1);
	if (char_receive->c == '\0')
		*client_pid = 0;
	char_receive->i = 0;
	char_receive->c = 0;
}

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static byte_t			char_receive;
	static pid_t			client_pid;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != 0 && client_pid != info->si_pid)
	{
		kill(SIGUSR2, info->si_pid);
		return ;
	}
	char_receive.c = char_receive.c << 1;
	if (signum == SIGUSR1)
		char_receive.c = char_receive.c | 1;
	char_receive.i++;
	if (char_receive.i == 8)
		ft_reset(&char_receive, &client_pid);
	kill (SIGUSR1, info->si_pid);
}

int	main(void)
{
	struct sigaction	sa;
	
	printf("Server's PID is: %d\n", getpid()); // need change to ft_printf
	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, (void *)0);
	sigaction(SIGUSR2, &sa, (void *)0);
	while (1)
		;	
}

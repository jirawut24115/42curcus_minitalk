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

void	ft_reset(t_byte	*char_receive, pid_t *client_pid)
{
	write (1, &char_receive->c, 1);
	if (char_receive->c == '\0')
		*client_pid = 0;
	char_receive->i = 0;
	char_receive->c = 0;
}

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static t_byte			char_receive;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != 0 && client_pid != info->si_pid)
		ft_reset(&char_receive, &client_pid);
	if (client_pid == 0)
		client_pid = info->si_pid;
	char_receive.c = char_receive.c << 1;
	if (signum == SIGUSR1)
		char_receive.c = char_receive.c | 1;
	char_receive.i++;
	if (char_receive.i == 8)
		ft_reset(&char_receive, &client_pid);
	kill (info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server's PID is: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, (void *)0);
	sigaction(SIGUSR2, &sa, (void *)0);
	while (1)
		;
}

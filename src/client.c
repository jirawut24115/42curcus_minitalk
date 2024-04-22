/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichompo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:38:48 by jichompo          #+#    #+#             */
/*   Updated: 2024/04/21 16:38:55 by jichompo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_status;

void	ft_continue(int signum)
{
	g_status = 1;
	(void)signum;
}

void	ft_send_char(char c, pid_t pid)
{
	int	index;

	index = 7;
	while (index >= 0)
	{
		if (c >> index & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		index--;
		while (g_status == 0)
			;
		g_status = 0;
	}
}

void	ft_send_msg(char *str, pid_t pid)
{
	while (*str)
	{
		ft_send_char(*str, pid);
		str++;
	}
	ft_send_char('\0', pid);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	g_status = 0;
	if (argc != 3)
		return (write(2, "Error\n", 6));
	pid = atoi(argv[1]);
	signal(SIGUSR1, ft_continue);
	ft_send_msg(argv[2], pid);
}

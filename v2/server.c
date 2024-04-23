/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichompo <jichompo@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:09:36 by jichompo          #+#    #+#             */
/*   Updated: 2024/04/24 00:15:01 by jichompo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h> //need to remove

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

t_pid	*queue;

void enqueue(pid_t pid)
{
	t_pid *new_node = malloc(sizeof(t_pid));
	new_node->pid = pid;
	new_node->next = NULL;
	if (!queue)
		queue = new_node;
	else
	{
		t_pid *temp = queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

pid_t dequeue()
{
	if (!queue)
		return 0;
	t_pid *temp = queue;
	pid_t pid = temp->pid;
	queue = queue->next;
	free(temp);
	return pid;
}

void	ft_reset(t_byte	*char_receive, pid_t *client_pid)
{
	write (1, &char_receive->c, 1);
	if (char_receive->c == '\0')
	{
		if (queue)
		{
			*client_pid = dequeue();
			kill(*client_pid, SIGUSR1);
		}
		else
			*client_pid = 0;
	}
	char_receive->i = 0;
	char_receive->c = 0;
}

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static t_byte			char_receive;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != info->si_pid)
		enqueue(info->si_pid);
	if (client_pid != info->si_pid && client_pid != 0)
		return ;
	if (client_pid == 0)
		{
			ft_reset(&char_receive, &client_pid);
			return ;
		}
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
	queue = (void *)0;

	printf("Server's PID is: %d\n", getpid()); // need change to ft_printf
	// ft_putstr_fd("Server's PID is: ", 1);
	// ft_putnbr_fd(getpid(), 1);
	// ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, (void *)0);
	sigaction(SIGUSR2, &sa, (void *)0);
	while (1)
		;
}

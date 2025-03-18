/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:34:34 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/18 20:59:05 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
When the monitor thread exits, it may show some memory leaks 
with tools like Valgrind because Valgrind is very strict. 
However, we can be assured by the documentation of pthread_detach 
that the memory will be freed when the thread exits.

https://man7.org/linux/man-pages/man3/pthread_detach.3.html
https://stackoverflow.com/questions/39195448/getting-leaks-even-after
-pthread-detach
*/

void	*monitor_thread(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		if (get_current_time() - philosopher->last_meal_time \
		> philosopher->config->time_to_die)
		{
			philosopher->current_state = dead;
			sem_wait(philosopher->config->print_semaphor);
			printf("[%lld] %d %s\n", get_current_time() \
			- philosopher->config->start_time, philosopher->id, "died");
			free_all(philosopher->config);
			exit(1);
		}
		if (philosopher->config->number_of_times_each_philosopher_must_eat \
			!= -1 && philosopher->nb_time_eaten == \
			philosopher->config->number_of_times_each_philosopher_must_eat)
		{
			philosopher->current_state = finished;
			break ;
		}
		ft_usleep(5);
	}
	return (NULL);
}

void	handle_philosopher_exit(t_config *config, int *finished_philo)
{
	int		status;
	pid_t	pid;
	int		i;

	pid = waitpid(-1, &status, 1);
	if (pid > 0)
	{
		if (((status) & 0xff00) >> 8 == 1)
		{
			i = 0;
			while (i < config->nb_philosophers)
			{
				kill(config->child_pids[i], SIGKILL);
				i++;
			}
		}
		(*finished_philo)++;
	}
}

/* This code waits for any child process to change state 
without blocking (WNOHANG).

The status variable contains more information than just the exit status,
so it is masked with 0xff00 and then shifted right by 8 bits to extract 
the actual exit status. (same as WEXITSTATUS(status))
*/

int	monitor_process(t_config *config)
{
	int		finished_philo;

	finished_philo = 0;
	while (42)
	{
		handle_philosopher_exit(config, &finished_philo);
		if (finished_philo == config->nb_philosophers)
			break ;
		ft_usleep(50);
	}
	return (0);
}

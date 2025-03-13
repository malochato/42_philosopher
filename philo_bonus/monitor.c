/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:34:34 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/14 00:27:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_thread(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		if (get_current_time() - philosopher->last_meal_time > philosopher->config->time_to_die)
		{
			philosopher->current_state = dead;
			sem_wait(philosopher->config->print_semaphor);
			printf("[%lld] %d %s\n", get_current_time() - philosopher->config->start_time, philosopher->id, "died");			
			free_all(philosopher->config);
			exit(1);
		}
		if (philosopher->config->number_of_times_each_philosopher_must_eat != -1 && \
			philosopher->nb_time_eaten == \
			philosopher->config->number_of_times_each_philosopher_must_eat)
		{
			philosopher->current_state = finished;
			return (NULL);
		}
		ft_usleep(5);
	}
	return (NULL);
}

int monitor_process(t_config *config)
{
	int     i;
	pid_t   pid;
	int     finished_philo;
	int     status;

	finished_philo = 0;
	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0)
		{
			if (WIFSIGNALED(status))
			{
				printf("ERROR: Process %d was killed by signal %d\n", pid, WTERMSIG(status));
			}
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < config->nb_philosophers)
				{
					kill(config->child_pids[i], SIGKILL);
					printf("Killed %d\n", config->child_pids[i]);
					i++;
				}
				break;
			}
			finished_philo++;
		}
		if (finished_philo == config->nb_philosophers)
			break;
		ft_usleep(50);
	}
	return (0);
}

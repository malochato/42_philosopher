/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:34:34 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/13 21:39:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_on_the_little_philosopher(t_config *config)
{
	int			i;
	int			finished_philo;

	i = 0;
	finished_philo = 0;
	while (i < config->nb_philosophers)
	{
		if (config->philosophers[i]->current_state == finished)
		{
			finished_philo++;
		}
		else if (get_current_time() \
			- config->philosophers[i]->last_meal_time > config->time_to_die)
		{
			sem_wait(config->print_semaphor);
			printf("[%lld] %d %s\n", get_current_time() \
			- config->start_time, config->philosophers[i]->id, "died");
			config->philo_dead = 1;
			sem_post(config->print_semaphor);
			return (42);
		}
		i++;
	}
	return (finished_philo);
}

/* 
Busy waiting, or spinning:
occurs when a program repeatedly checks a condition in a loop.
This can lead to inefficient use of CPU resources.
So it is important to use a sleep function to avoid this.

Also the subject specifies that the program should have less 
than 10 ms of delay after a philosopher dies.
I put 5 ms to be sure, that this condition is respected.
*/


int monitor(t_config *config)
{
	int     i;
	pid_t   pid;
	int     finished_philo;
	int     status;

	(void)finished_philo;
	while (1)
	{

		pid = waitpid(-1, &status, WNOHANG);
		printf("pid: %d\n", pid);
		if (pid > 0)
		{
			if (WIFEXITED(status))
            {
                printf("Process %d finished with status %d\n", pid, WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("Process %d was killed by signal %d\n", pid, WTERMSIG(status));
            }


			i = 0;
			while (i < config->nb_philosophers)
			{
				kill(config->child_pids[i], SIGKILL);
				printf("Killed %d\n", config->child_pids[i]);
				i++;
			}
			break;
		}
		ft_usleep(50);
	}
	return (0);
}
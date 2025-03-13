/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/14 00:23:56 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_zzz(t_philosopher *philosopher)
{
	philosopher->current_state = sleeping;
	need_to_talk(philosopher, "is sleeping");
	ft_usleep(philosopher->config->time_to_sleep);
}

void	think(t_philosopher *philosopher)
{
	philosopher->current_state = thinking;
	need_to_talk(philosopher, "is thinking");
}

/* 
on peut avoir un deadlock si tous les philos prennent une fourchette 
comment eviter ce probleme ?
*/
void	eat(t_philosopher *philosopher)
{

/* 	int forks_left;
	sem_getvalue(philosopher->config->forks, &forks_left);
	printf("Forks left: %d\n", forks_left); */


	
	sem_wait(philosopher->config->forks);
	sem_wait(philosopher->config->forks);
	need_to_talk(philosopher, "has taken a fork");
	need_to_talk(philosopher, "has taken a fork");


	philosopher->current_state = eating;
	need_to_talk(philosopher, "is eating");
	philosopher->last_meal_time = get_current_time();
	ft_usleep(philosopher->config->time_to_eat);
	philosopher->nb_time_eaten++;



	sem_post(philosopher->config->forks);
	sem_post(philosopher->config->forks);
}

int	routine(t_philosopher *philosopher)
{
	if (pthread_create(&philosopher->thread, NULL, (void *)monitor_thread, philosopher))
	{
		ft_putstr_fd("Error: pthread_create failed\n", 2);
		return (1);
	}
	
	if (philosopher->config->nb_philosophers == 1)
	{
		need_to_talk(philosopher, "has taken a fork");
		ft_usleep(philosopher->config->time_to_die);
		return (1);
	}	
	while (philosopher->current_state != finished && philosopher->current_state != dead) 
	{
		eat(philosopher);
		if (philosopher->config->number_of_times_each_philosopher_must_eat \
		== philosopher->nb_time_eaten)
			break ;
		sleep_zzz(philosopher);
		think(philosopher);
	}
	
	if (pthread_join(philosopher->thread, NULL))
	{
		ft_putstr_fd("Error: pthread_join failed\n", 2);
		return (1);
	}
	free_all(philosopher->config);
	return (0);
}

/* 
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
philosopher->nb_time_eaten == philosopher->config->number_of_times_each_philosopher_must_eat)
		{
			philosopher->current_state = finished;
			return (NULL);
		}
		ft_usleep(50);
	}
	return (NULL);
} */
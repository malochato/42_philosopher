/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/18 20:41:10 by malde-ch         ###   ########.fr       */
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

int	init_monitor_thread(t_philosopher *philosopher)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_thread, philosopher))
	{
		ft_putstr_fd("Error: pthread_create failed\n", 2);
		return (1);
	}
	if (pthread_detach(thread) != 0)
	{
		ft_putstr_fd("Error: pthread_detach failed\n", 2);
		return (1);
	}
	return (0);
}

int	routine(t_philosopher *philosopher)
{
	if (init_monitor_thread(philosopher))
		return (1);
	if (philosopher->config->nb_philosophers == 1)
	{
		need_to_talk(philosopher, "has taken a fork");
		ft_usleep(philosopher->config->time_to_die);
		return (1);
	}
	while (philosopher->current_state != finished)
	{
		eat(philosopher);
		if (philosopher->config->number_of_times_each_philosopher_must_eat \
		== philosopher->nb_time_eaten)
			break ;
		sleep_zzz(philosopher);
		think(philosopher);
	}
	return (0);
}

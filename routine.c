/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/11 01:30:48 by malde-ch         ###   ########.fr       */
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
By alternating the order in which philosophers pick up the forks,
this ensures that no philosophers are waiting for the same fork 
at the same time. This prevents the circular wait condition.
 */

void	take_fork(t_philosopher *philosopher)
{
	int	left_fork;
	int	right_fork;

	left_fork = philosopher->id - 1;
	right_fork = philosopher->id % philosopher->config->nb_philosophers;
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->config->forks[right_fork]);
		need_to_talk(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->config->forks[left_fork]);
		need_to_talk(philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philosopher->config->forks[left_fork]);
		need_to_talk(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->config->forks[right_fork]);
		need_to_talk(philosopher, "has taken a fork");
	}
}

void	eat(t_philosopher *philosopher)
{
	take_fork(philosopher);
	philosopher->current_state = eating;
	need_to_talk(philosopher, "is eating");
	philosopher->last_meal_time = get_current_time();
	ft_usleep(philosopher->config->time_to_eat);
	philosopher->nb_time_eaten++;
	pthread_mutex_unlock(&philosopher->config->forks[philosopher->id - 1]);
	pthread_mutex_unlock(&philosopher->config->forks \
	[philosopher->id % philosopher->config->nb_philosophers]);
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->config->nb_philosophers == 1)
	{
		need_to_talk(philosopher, "has taken a fork");
		ft_usleep(philosopher->config->time_to_die);
		return (NULL);
	}
	while (philosopher->config->philo_dead == 0)
	{
		eat(philosopher);
		if (philosopher->config->number_of_times_each_philosopher_must_eat \
		== philosopher->nb_time_eaten)
			break ;
		sleep_zzz(philosopher);
		think(philosopher);
	}
	philosopher->current_state = finished;
	return (NULL);
}

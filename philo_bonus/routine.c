/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/13 21:42:45 by malde-ch         ###   ########.fr       */
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

	int forks_left;
	sem_getvalue(philosopher->config->forks, &forks_left);
	printf("Forks left: %d\n", forks_left);
	sem_wait(philosopher->config->forks);
	need_to_talk(philosopher, "has taken a fork");
	sem_wait(philosopher->config->forks);
	need_to_talk(philosopher, "has taken a fork");


	philosopher->current_state = eating;
	need_to_talk(philosopher, "is eating");
	philosopher->last_meal_time = get_current_time();
	ft_usleep(philosopher->config->time_to_eat);
	philosopher->nb_time_eaten++;



	sem_post(philosopher->config->forks);
	sem_post(philosopher->config->forks);
}

void	*routine(t_philosopher	*philosopher)
{
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

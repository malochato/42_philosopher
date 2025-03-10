/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 22:35:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	need_to_talk(t_philosopher *philosopher, char *str)
{
	t_config *config;

	config = philosopher->config;
/*  	if (philosopher->id != 1)
		return (0); */
	pthread_mutex_lock(&config->print_mutex);
	if (config->philo_dead)
	{
		pthread_mutex_unlock(&config->print_mutex);
		return ;
	}
	printf("[%lld] %d %s\n", get_current_time() - config->start_time, philosopher->id, str);
	pthread_mutex_unlock(&config->print_mutex);
}


void	sleep_zZz(t_philosopher *philosopher)
{
	philosopher->current_state = sleeping;
	need_to_talk(philosopher, "is sleeping");
	ft_usleep(philosopher->config->time_to_sleep);
}

void think(t_philosopher *philosopher)
{
	philosopher->current_state = thinking;
	need_to_talk(philosopher, "is thinking");
}

void take_fork(t_philosopher *philosopher)
{
	int left_fork;
	int right_fork;

	left_fork = philosopher->id - 1;
	right_fork = philosopher->id % philosopher->config->number_of_philosophers;

	/* pthread_mutex_lock(&philosopher->config->forks[right_fork]);
	need_to_talk(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->config->forks[left_fork]);
	need_to_talk(philosopher, "has taken a fork"); */


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

void eat(t_philosopher *philosopher)
{
	

	philosopher->current_state = eating;
	take_fork(philosopher);
	need_to_talk(philosopher, "is eating");
	ft_usleep(philosopher->config->time_to_eat);
	philosopher->last_meal_time = get_current_time();
	philosopher->time_eaten++;
	pthread_mutex_unlock(&philosopher->config->forks[philosopher->id - 1]);
	pthread_mutex_unlock(&philosopher->config->forks[philosopher->id % philosopher->config->number_of_philosophers]);
}

void	*routine(void *arg)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)arg;
	if(philosopher->config->number_of_philosophers == 1)
	{
		need_to_talk(philosopher, "has taken a fork");
		ft_usleep(philosopher->config->time_to_die);
		return(NULL);
	}
	while (philosopher->config->philo_dead == 0)
	{
		eat(philosopher);
		if (philosopher->config->number_of_times_each_philosopher_must_eat == philosopher->time_eaten)
			break ;
		sleep_zZz(philosopher);
		think(philosopher);
	}
	philosopher->current_state = finished;
	return (NULL);
}

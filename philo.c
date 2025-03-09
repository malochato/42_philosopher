/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:01:43 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 00:23:14 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_config *config)
{
	int	i;

	config->forks = malloc(config->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!config->forks)
    {
        ft_putstr_fd("Error: malloc failed\n", 2);
        return (1);
    }
	i = 0;
    while (i < config->number_of_philosophers)
    {
        pthread_mutex_init(&config->forks[i], NULL);
        i++;
    }
	return (0);
	
}


int	init_config(int argc, char **argv, t_config *config)
{
	config->philosophers = NULL;
	if (parser(argc, argv, config))
		return (1);
	config->start_time = get_current_time();
	config->philo_dead = 0;
	pthread_mutex_init(&config->print_mutex, NULL);
	
	if (init_forks(config))
		return (1);


	config->philosophers = malloc(config->number_of_philosophers * sizeof(t_philosopher *));
	if (!config->philosophers)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (1);
	}
	if (create_philosophers(config))
		return (1);


	return (0);
}


int create_philosophers(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		config->philosophers[i] = malloc(sizeof(t_philosopher));
		if (!config->philosophers[i])
		{
			while(i > 0)
			{
				free(config->philosophers[i - 1]);
				i--;
			}
			ft_putstr_fd("Error: malloc failed\n", 2);
			return (1);
		}
		config->philosophers[i]->config = config;
		config->philosophers[i]->id = i + 1;
		config->philosophers[i]->current_state = thinking;
		config->philosophers[i]->last_meal_time = config->start_time;
		//config->philosophers[i]->number_of_meals = 0;
		config->philosophers[i]->finished = 0;


		pthread_mutex_init(&config->philosophers[i]->finished_mutex, NULL);
		i++;
	}
	return (0);
}


int	join_philosophers(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_join(config->philosophers[i]->thread, NULL) != 0)
		{
			ft_putstr_fd("Error: pthread_join failed\n", 2);
			return (1);
		}
		i++;
		printf("joined %d\n", i);
	}
	return (0);
}
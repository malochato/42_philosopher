/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:58:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 00:03:54 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long long get_current_time()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd("Error: gettimeofday failed\n", 2);
		return (-1);
	}
	//voire comment implementer cela dans le code
	//convertit les secondes en mili secondes
	// convertit les micros secondes en mili secondes
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}


int	start_diner(t_config *config)
{
	int i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		if (pthread_create(&config->philosophers[i]->thread, NULL, &routine, config->philosophers[i]) != 0)
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void free_all(t_config *config)
{
	int i;

	i = 0;
	if (config->forks)
	{
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_destroy(&config->forks[i]);
			i++;
		}
		free(config->forks);
	}
	i = 0;
	if (config->philosophers)
	{
		while (i < config->number_of_philosophers)
		{
			pthread_mutex_destroy(&config->philosophers[i]->finished_mutex);
			free(config->philosophers[i]);
			i++;
		}
		free(config->philosophers);
	}
	free(config);
}

int main(int argc, char **argv)
{
	t_config *config;

	config = malloc(sizeof(t_config));
	if (!config)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (1);
	}
	if (init_config(argc, argv, config))
	{
		free_all(config);
		return (1);
	}
	if (start_diner(config))
	{
		free_all(config);
		return (1);
	}
	if (join_philosophers(config))
	{
		free_all(config);
		return (1);
	}

	printf("number of philosopher: %d\n", config->number_of_philosophers);
	printf("time now: %lld\n", get_current_time());
	free_all(config);
	return (0);
}

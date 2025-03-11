/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:58:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/11 01:42:59 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_config *config)
{
	int	i;

	i = 0;
	if (config->forks)
	{
		while (i < config->nb_philosophers)
		{
			pthread_mutex_destroy(&config->forks[i]);
			i++;
		}
		free(config->forks);
	}
	i = 0;
	if (config->philosophers)
	{
		while (i < config->nb_philosophers)
		{
			pthread_mutex_destroy(&config->philosophers[i]->finished_mutex);
			free(config->philosophers[i]);
			i++;
		}
		free(config->philosophers);
	}
	free(config);
}

int	start_the_feast(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philosophers)
	{
		if (pthread_create(&config->philosophers[i]->thread, \
		NULL, &routine, config->philosophers[i]) != 0)
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			return (1);
		}
		i ++;
	}
	return (0);
}

int	join_philosophers(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philosophers)
	{
		if (pthread_join(config->philosophers[i]->thread, NULL) != 0)
		{
			ft_putstr_fd("Error: pthread_join failed\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (ft_putstr_fd("Error: malloc failed\n", 2), 1);
	if (init_config(argc, argv, config))
		return (free_all(config), 1);
	if (start_the_feast(config))
		return (free_all(config), 1);
	monitor(config);
	if (join_philosophers(config))
		return (free_all(config), 1);
	free_all(config);
	return (0);
}

/* 
The return value take only one value, 
but with the comma, the expression is still evaluated,
in our case free_all(config) is evaluated before the return.
 */
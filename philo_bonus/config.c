/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:01:43 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/13 20:12:07 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosophers(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nb_philosophers)
	{
		config->philosophers[i] = malloc(sizeof(t_philosopher));
		if (!config->philosophers[i])
		{
			while (i > 0)
			{
				free(config->philosophers[i - 1]);
				i--;
			}
			return (1);
		}
		config->philosophers[i]->config = config;
		config->philosophers[i]->id = i + 1;
		config->philosophers[i]->current_state = thinking;
		config->philosophers[i]->last_meal_time = config->start_time;
		config->philosophers[i]->nb_time_eaten = 0;
		config->philosophers[i]->finished = 0;
		i++;
	}
	return (0);
}

int init_sem(t_config *config)
{
	sem_unlink("/forks");
	config->forks = sem_open("/forks", O_CREAT, 0644, config->nb_philosophers);
	if (config->forks == SEM_FAILED)
	{
		ft_putstr_fd("Error: sem_open failed\n", 2);
		return (1);
	}

	sem_unlink("/print_semaphor");
	config->print_semaphor = sem_open("/print_semaphor", O_CREAT, 0644, 1);
	if (config->print_semaphor == SEM_FAILED)
	{
		ft_putstr_fd("Error: sem_open failed\n", 2);
		return (1);
	}
	return (0);
}


int	init_config(int argc, char **argv, t_config *config)
{
	config->philosophers = NULL;
	config->philo_dead = 0;
	config->start_time = get_current_time();
	if (parser(argc, argv, config))
		return (1);
	config->philosophers = malloc(config->nb_philosophers * \
	sizeof(t_philosopher *));
	if (!config->philosophers)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (1);
	}
	if (create_philosophers(config))
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (1);
	}
	if (init_sem(config))
		return (1);
	config->child_pids = malloc(sizeof(pid_t) * config->nb_philosophers);
	if (!config->child_pids)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:34:34 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 22:17:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_config *config)
{
	int			i;
	long long	time;
	int	finished_philo;

	while (1)
	{
		i = 0;
		finished_philo = 0;
		while (i < config->number_of_philosophers)
		{
			time = get_current_time();
			if (time == -1)
				return (1);
			if (config->philosophers[i]->current_state == finished)
			{
				finished_philo++;
			}
			else if (time - config->philosophers[i]->last_meal_time > config->time_to_die)
			{
				pthread_mutex_lock(&config->print_mutex);
				printf("[%lld] %d %s\n", get_current_time() - config->start_time, config->philosophers[i]->id, "died");
				config->philo_dead = 1;
				pthread_mutex_unlock(&config->print_mutex);
				return (1);
			}
			i++;
		}
		if (config->philo_dead || finished_philo == config->number_of_philosophers)
			break;
		ft_usleep(1);
	}
	return (0);
}

// busy waiting
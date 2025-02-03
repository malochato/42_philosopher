/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:01:43 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/03 14:01:48 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_philosophers(t_philo_config *config, t_philosopher **philosophers)
{
    int i;

    i = 0;
    while (i < config->number_of_philosophers)
    {
        philosophers[i] = malloc(sizeof(t_philosopher));
        if (!philosophers[i])
        {
            //free tout les autre philosopher cree avant.
            ft_putstr_fd("Error: malloc failed\n", 2);
            return (0);
        }
        philosophers[i]->config = config;
        philosophers[i]->id = i + 1;
        philosophers[i]->current_state = THINKING;
        philosophers[i]->last_meal_time = get_current_time();

        if (pthread_create(&philosophers[i]->thread, NULL, &routine, philosophers[i]) != 0)
        {
            //free tout les autre philosopher cree avant.
            ft_putstr_fd("Error: pthread_create failed\n", 2);
            return (0);
        }
        printf("Creating philosopher %d with last_meal at %lld\n", philosophers[i]->id, philosophers[i]->last_meal_time); 
        i++;
    }
    return (1);
}


void join_philosophers(t_philo_config *config, t_philosopher **philosophers)
{
    int i;

    i = 0;
    while (i < config->number_of_philosophers)
    {
        if (pthread_join(philosophers[i]->thread, NULL) != 0)
        {
            write(2, "Error: pthread_join failed\n", 28);
            return ;
        }
        i++;
    }
}
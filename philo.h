/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:34:19 by malde-ch          #+#    #+#             */
/*   Updated: 2025/01/27 15:34:21 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define PHILO_MAX 200

typedef struct s_philo_config
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_config;

t_philo_config	*parser(int argc, char **argv);

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_philo_state;

typedef struct s_philosopher
{
	int				id;
	t_philo_state	current_state;
	long long		last_meal_time;
	t_philo_config	*config;
	pthread_t		thread;
	pthread_mutex_t *print_mutex;
}	t_philosopher;


void ft_putstr_fd(char *str, int fd);

int create_philosophers(t_philo_config *config, t_philosopher **philosophers);
void join_philosophers(t_philo_config *config, t_philosopher **philosophers);

void    *routine(void *arg);
long long get_current_time();


#endif

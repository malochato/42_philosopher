/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:34:19 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/18 17:16:49 by malde-ch         ###   ########.fr       */
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

typedef struct s_philosopher	t_philosopher;

typedef enum e_philo_state
{
	thinking,
	eating,
	sleeping,
	finished
}	t_philo_state;

typedef struct s_config
{
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	t_philosopher	**philosophers;
	long long		start_time;
	int				philo_dead;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;

}	t_config;

typedef struct s_philosopher
{
	int				id;
	t_philo_state	current_state;
	long long		last_meal_time;
	t_config		*config;
	pthread_t		thread;

	pthread_mutex_t	*print_mutex;
	int				nb_time_eaten;

	int				finished;

}	t_philosopher;

//utils.c
void		ft_putstr_fd(char *str, int fd);
void		ft_usleep(long long time);
long long	get_current_time(void);

//config.c
int			init_config(int argc, char **argv, t_config *config);

//parser.c
int			parser(int argc, char **argv, t_config *config);

//monitor.c
int			monitor(t_config *config);

//routine.c
void		*routine(void *arg);
void		need_to_talk(t_philosopher *philosopher, char *str);

#endif

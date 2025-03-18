/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:34:19 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/18 20:33:30 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define PHILO_MAX 200

typedef struct s_philosopher	t_philosopher;

typedef enum e_philo_state
{
	thinking,
	eating,
	sleeping,
	finished,
	dead
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

	pid_t			*child_pids;

	sem_t			*forks;
	sem_t			*print_semaphor;

}	t_config;

typedef struct s_philosopher
{
	int				id;
	t_philo_state	current_state;
	long long		last_meal_time;
	t_config		*config;

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
int			monitor_process(t_config *config);
void		*monitor_thread(void *arg);

//routine.c
int			routine(t_philosopher *philosopher);
void		need_to_talk(t_philosopher *philosopher, char *str);

//main.c
void		free_all(t_config *config);
#endif

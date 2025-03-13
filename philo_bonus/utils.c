/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:07:25 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/14 00:26:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	need_to_talk(t_philosopher *philosopher, char *str)
{
	t_config	*config;

	config = philosopher->config;
	sem_wait(config->print_semaphor);
	printf("[%lld] %d %s\n", \
	get_current_time() - config->start_time, philosopher->id, str);
	sem_post(config->print_semaphor);
}

/*
 This function retrieves the current time in milliseconds.
 It uses the gettimeofday function to get the time in seconds and microseconds,
 then converts it to milliseconds .
 */

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd("Error: gettimeofday failed\n", 2);
		return (-1);
	}
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

/*
This function is more precise than usleep.
It checks the time every 10 ms.
This is referred to as granularity.
With this function, we have better control over the timing 
(finer granularity).
*/

void	ft_usleep(long long time)
{
	long long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(time / 10);
}

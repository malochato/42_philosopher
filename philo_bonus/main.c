/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:58:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/18 20:31:26 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	custom_sem_close(t_config *config)
{
	if (sem_close(config->forks) < 0)
		ft_putstr_fd("Error: sem_close failed\n", 2);
	if (sem_close(config->print_semaphor) < 0)
		ft_putstr_fd("Error: sem_close failed\n", 2);
}

void	custom_sem_unlink(void)
{
	if (sem_unlink("/forks") < 0)
		ft_putstr_fd("Error: sem_unlink failed\n", 2);
	if (sem_unlink("/print_semaphor") < 0)
		ft_putstr_fd("Error: sem_unlink failed\n", 2);
}

void	free_all(t_config *config)
{
	int	i;

	custom_sem_close(config);
	i = 0;
	if (config->philosophers)
	{
		while (i < config->nb_philosophers)
		{
			if (config->philosophers[i])
				free(config->philosophers[i]);
			i++;
		}
		free(config->philosophers);
	}
	if (config->child_pids)
		free(config->child_pids);
	free(config);
}

int	start_the_feast(t_config *config)
{
	int		i;
	pid_t	pid;
	int		ret;

	i = 0;
	while (i < config->nb_philosophers)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Error: fork failed\n", 2);
			free(config->child_pids);
			return (1);
		}
		if (pid == 0)
		{
			ft_usleep(i);
			ret = routine(config->philosophers[i]);
			free_all(config);
			exit(ret);
		}
		config->child_pids[i] = pid;
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
	monitor_process(config);
	free_all(config);
	custom_sem_unlink();
	return (0);
}

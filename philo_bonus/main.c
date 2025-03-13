/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:58:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/13 23:58:39 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_close_unlink(t_config *config)
{
	(void)config;
	if (sem_unlink("/forks") < 0)
		ft_putstr_fd("Error: sem_unlink failed\n", 2);
	if (sem_unlink("/print_semaphor") < 0)
		ft_putstr_fd("Error: sem_unlink failed\n", 2);
}


void	free_all(t_config *config)
{
	int	i;

	if (sem_close(config->forks) < 0)
		ft_putstr_fd("Error: sem_close failed\n", 2);
	if(sem_close(config->print_semaphor) < 0)
		ft_putstr_fd("Error: sem_close failed\n", 2);
	i = 0;
	if (config->philosophers)
	{
		while (i < config->nb_philosophers)
		{
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
    int	i;
    pid_t	pid;
	int	ret;


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

    printf("Allocating memory for config\n");
    config = malloc(sizeof(t_config));
    if (!config)
        return (ft_putstr_fd("Error: malloc failed\n", 2), 1);
    printf("Initializing config\n");
    if (init_config(argc, argv, config))
        return (free_all(config), 1);
    printf("Starting the feast\n");
    if (start_the_feast(config))
        return (free_all(config), 1);
    printf("Monitoring\n");
    monitor_process(config);
    printf("Freeing all resources\n");
    sem_close_unlink(config);
	free_all(config);
    printf("Exiting program\n");
    return (0);
}


/* int	main(int argc, char **argv)
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
} */

/* 
The return value take only one value, 
but with the comma, the expression is still evaluated,
in our case free_all(config) is evaluated before the return.
 */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:21:16 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 00:21:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr <= 57 && *nptr >= 48)
	{
		nb = nb * 10 + (*nptr - 48);
		nptr++;
	}
	return (sign * nb);
}

int check_content(char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

int	check_arguments(int argc, char **argv)
{
    int	i;

    i = 1;
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0 || !check_content(argv[i]))
        {
            ft_putstr_fd("Error: All arguments must be positive numbers smaller than MAX_INT\n", 2);
            return (1);
        }
        if (i == 1 && ft_atoi(argv[i]) >= PHILO_MAX + 1)
        {
            ft_putstr_fd("Error: Number of philosophers must be smaller than PHILO_MAX (200)\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int	parser(int argc, char **argv, t_config *config)
{
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Error: Invalid number of arguments\n", 2);
        return (1);
    }
    if (check_arguments(argc, argv))
        return (1);
    config->number_of_philosophers = ft_atoi(argv[1]);
    config->time_to_die = ft_atoi(argv[2]);
    config->time_to_eat = ft_atoi(argv[3]);
    config->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        config->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        config->number_of_times_each_philosopher_must_eat = -1;
    return (0);
}


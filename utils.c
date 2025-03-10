/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:07:25 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/10 22:01:23 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_putstr_fd(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

void	ft_usleep(long long time)
{
	//long long start;

	//start = get_current_time();
	
	usleep(time * 1000);
	
	//while (get_current_time() - start < time)
	//	usleep(100);
}


//convertion de micro a miliseconde
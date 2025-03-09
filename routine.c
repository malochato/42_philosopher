/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:18:18 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/09 23:52:59 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    *routine(void *arg)
{
    t_philosopher *philosopher;

    philosopher = (t_philosopher *)arg;
    printf("philosopher routine from %d\n", philosopher->id);
	sleep(1);
    return (NULL);
}

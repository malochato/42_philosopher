#include "philo.h"

long long get_current_time()
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        ft_putstr_fd("Error: gettimeofday failed\n", 2);
        return (-1);
    }
    //voire comment implementer cela dans le code
    //convertit les secondes en mili secondes
    // convertit les micros secondes en mili secondes
    return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}




int main(int argc, char **argv)
{
    t_philo_config *config;
    t_philosopher *philosophers[PHILO_MAX];


    config = parser(argc, argv);
    if (!config)
        return (1);
    create_philosophers(config, philosophers);
    join_philosophers(config, philosophers);

    printf("number of philosopher: %d\n", config->number_of_philosophers);
    printf("time now: %lld\n", get_current_time());
    return (0);
}
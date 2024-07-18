/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:14:34 by brpereir          #+#    #+#             */
/*   Updated: 2024/07/18 18:03:50 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void action_print(int id, char *msg, char *color)
{
	printf("%i: %s%s\n%s", id, color, msg, RESET);
}

void lone_philo(t_table	*table)
{
	action_print(1, "has taken a fork", GREEN);
	action_print(1, "has died", RED);
	free(table);
	exit(0);
}

void start_philo(t_philo *philo)
{
	int i = -1;
	while(++i < 3)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		action_print(philo->id, "has taken a fork", GREEN);
		action_print(philo->id, "has taken a fork", GREEN);
		usleep(1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		action_print(philo->id, "is thinking", "");
		usleep(2000);
		action_print(philo->id, "is sleeping", BLUE);
		usleep(3000);
	}
}

void	*init_philo(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *) arg;
	if (philo->id % 2)
		usleep(2000);	
	start_philo(philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		i;
	
	if (ac != 5 && ac != 6)
		return (0);
	i = -1;
	table = malloc(sizeof(t_table));
	table->n_philo = atoi(av[1]);
	table->tme_die = atoi(av[2]);
	table->tme_eat = atoi(av[3]);
	table->tme_sleep = atoi(av[4]);
	if(ac == 6)
		table->tme_mst_eat = atoi(av[5]);
	else
		table->tme_mst_eat = 0;
	if(table->n_philo == 1)
		lone_philo(table);
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	while(++i < table->n_philo)
	{	
		table->philos[i].id = i;
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[i + 1];
		pthread_create(&table->philos[i].t_id, NULL, init_philo, &table->philos[i]);
	}
	while(1)
		;
	return (0);
}

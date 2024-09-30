/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:59:43 by marvin            #+#    #+#             */
/*   Updated: 2024/09/30 10:12:07 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_init(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (printf("Invalid number of arguments\n"), 0);
	table->n_philo = ft_atoi(av[1]);
	table->tme_die = ft_atoi(av[2]);
	table->tme_eat = ft_atoi(av[3]);
	table->tme_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->max_eat = ft_atoi(av[5]);
	else
		table->max_eat = 0;
	table->finished = 0;
	if (pthread_mutex_init(&table->finish, NULL))
		return (printf("Mutex init error\n"), 0);
	table->start_time = gettime();
	if (!args_valid(table, ac))
		return (0);
	return (1);
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (printf("Malloc error\n"), 0);
	if (!threads_init(table))
		return (0);
	while (++i < table->n_philo)
		if (!philo_init(table, &table->philos[i], i))
			return (0);
	i = -1;
	while (++i < table->n_philo)
		if (pthread_create(&table->philos[i].t_id, NULL,
				init_philo, &table->philos[i]))
			return (printf("Error creating threads"), 0);
	return (1);
}

int	threads_init(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	if (pthread_mutex_init(&table->print, NULL))
		return (printf("Mutex init error\n"), 0);
	return (1);
}

int	philo_init(t_table *table, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->table = table;
	philo->eat_count = 0;
	philo->lst_eat = gettime();
	if (pthread_mutex_init(&philo->eat, NULL))
		return (printf("Mutex init error\n"), 0);
	if (pthread_mutex_init(&philo->l_eat, NULL))
		return (printf("Mutex init error\n"), 0);
	get_forks(table->forks, philo, i);
	return (1);
}

void	*init_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	set_value(&philo->l_eat, &philo->lst_eat, gettime());
	if (table->n_philo == 1)
		lone_philo(table);
	if (!(philo->id % 2))
		usleep(2000);
	if (table->n_philo != 1)
		start_philo(philo);
	return (NULL);
}

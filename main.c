/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:14:34 by brpereir          #+#    #+#             */
/*   Updated: 2024/07/31 18:24:45 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	t_table			*table;

	if (ac != 5 && ac != 6)
		return (0);
	data_init(&table, av, ac);
	if (!valid_input(table))
		exit(0);
	threads_init(table);
	table->start_time = gettime();
	start_simulation(table);
	while (ft_monitoring(table))
		;
	table->flag = 1;
	end_simulation(table);
	return (0);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		table->philos[i].lst_eat = gettime();
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].l_fork = &table->forks[i];
		if (i + 1 == table->n_philo)
			table->philos[i].r_fork = &table->forks[0];
		else
			table->philos[i].r_fork = &table->forks[i + 1];
		pthread_create(&table->philos[i].t_id,
			NULL, init_philo, &table->philos[i]);
	}
}

void	lone_philo(t_table *table)
{
	action_print(&table->philos[0], 1);
	ft_usleep(table->tme_die);
	action_print(&table->philos[0], 3);
	pthread_mutex_destroy(table->forks);
	pthread_mutex_destroy(table->write);
	free(table->philos);
	free(table->forks);
	free(table->write);
	free(table);
	exit(0);
}

void	start_philo(t_philo *philo)
{
	while (!is_dead(philo))
	{
		pthread_mutex_lock(philo->l_fork);
		action_print(philo, 1);
		pthread_mutex_lock(philo->r_fork);
		action_print(philo, 1);
		action_print(philo, 0);
		ft_usleep(philo->table->tme_eat);
		philo->eat_count++;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->lst_eat = gettime();
		action_print(philo, 2);
		ft_usleep(philo->table->tme_sleep);
		if(!philo->table->flag)
			action_print(philo, 4);
	}
}

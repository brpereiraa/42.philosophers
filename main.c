/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:14:34 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/26 17:10:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	t_table			*table;

	if (ac != 5 && ac != 6)
		return (0);
	if (data_init(&table, av, ac))
		exit(1);
	if (!valid_input(table, ac))
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
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].dead = 0;
		table->philos[i].eat_count = 0;
		get_forks(table->forks, &table->philos[i], i);
		pthread_create(&table->philos[i].t_id,
			NULL, init_philo, &table->philos[i]);
	}
}

void	lone_philo(t_table *table)
{
	action_print(&table->philos[0], 1);
	ft_usleep(table->tme_die);
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
		if (!philo->table->flag)
			action_print(philo, 4);
	}
}

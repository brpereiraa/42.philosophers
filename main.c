/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:14:34 by brpereir          #+#    #+#             */
/*   Updated: 2024/07/30 03:15:18 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void *lone_philo(void *arg)
{
	t_table *table;

	table = (t_table *) arg;
	action_print(&table->philos[0], 1);
	usleep(table->tme_die);
	action_print(&table->philos[0], 3);

	return NULL;
}

void start_philo(t_philo *philo)
{
	while(!is_dead(philo))
	{
		pthread_mutex_lock(philo->l_fork);
		action_print(philo, 1);
		pthread_mutex_lock(philo->r_fork);
		action_print(philo, 1);
		action_print(philo, 0);
		usleep(philo->table->tme_eat);
		philo->eat_count++;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->lst_eat = gettime();
		action_print(philo, 2);
		usleep(philo->table->tme_sleep);
	}
}

void	*init_philo(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *) arg;
	if (!(philo->id % 2))
		usleep(2000);	
	start_philo(philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table			*table;
	int				i;
	
	if (ac != 5 && ac != 6)
		return (0);
	i = -1;
	data_init(&table, av, ac);
	if(!valid_input(table))
		exit(0);
	threads_init(table);
	table->start_time = gettime();
	if(table->n_philo == 1)
	{
		table->philos[0].id = 0;
		table->philos[0].table = table;
		pthread_create(&table->philos[0].t_id, NULL, lone_philo, table);
		pthread_join(table->philos[0].t_id, NULL);
		free(table->philos);
		free(table);
		exit(0);
	}
	i = -1;
	while(++i < table->n_philo)
	{	
		table->philos[i].lst_eat = gettime();
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].l_fork = &table->forks[i];
		if(i + 1 == table->n_philo)
			table->philos[i].r_fork = &table->forks[0];
		else
			table->philos[i].r_fork = &table->forks[i + 1];
		pthread_create(&table->philos[i].t_id, NULL, init_philo, &table->philos[i]);
	}
	while(1)
		;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:50:16 by marvin            #+#    #+#             */
/*   Updated: 2024/09/29 17:50:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	action_print(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	action_print(philo, 1);
	action_print(philo, 0);
	set_value(&philo->l_eat, &philo->lst_eat, gettime());
	set_value(&philo->eat, &philo->eat_count, -1);
	ft_usleep(table->tme_eat, table);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = gettime();
	while ((gettime() - start) < milliseconds)
	{
		if (get_value(&table->finish, &table->finished))
			return ;
		usleep(500);
	}
	return ;
}

void	action_print(t_philo *philo, int flag)
{
	t_table	*table;
	int		id;
	int		time;

	id = philo->id;
	table = philo->table;
	time = gettime() - philo->table->start_time;
	if (get_value(&table->finish, &table->finished))
		return ;
	pthread_mutex_lock(&philo->table->print);
	if (flag == 0)
		printf("%i %i %sis eating\n%s", time, id, YELLOW, RESET);
	if (flag == 1)
		printf("%i %i %shas taken a fork\n%s", time, id, GREEN, RESET);
	if (flag == 2)
		printf("%i %i %sis sleeping\n%s", time, id, BLUE, RESET);
	if (flag == 3)
		printf("%i %i %sdied\n%s", time, id, RED, RESET);
	if (flag == 4)
		printf("%i %i is thinking\n%s", time, id, RESET);
	pthread_mutex_unlock(&philo->table->print);
}

void	get_forks(pthread_mutex_t *fork, t_philo *philo, int i)
{
	int	n_philo;

	n_philo = philo->table->n_philo;
	if (philo->id % 2 != 0)
	{
		philo->l_fork = &fork[(i + 1) % n_philo];
		philo->r_fork = &fork[i];
	}
	else
	{
		philo->l_fork = &fork[i];
		philo->r_fork = &fork[(i + 1) % n_philo];
	}
}

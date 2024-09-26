/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:44:51 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/27 00:34:54 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_finished(t_table *table)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (++i < table->n_philo)
	{
		flag = ((table->philos[i].eat_count == table->tme_mst_eat));
		if (!flag)
			break ;
	}
	if (flag)
	{
		pthread_mutex_lock(table->finished);
		table->finish = 1;
		pthread_mutex_unlock(table->finished);
		return (1);
	}
	return (0);
}

int	ft_monitoring(t_table *table)
{
	int	flag;
	int	tmp;
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		flag = (table->philos[i].eat_count == table->tme_mst_eat);
		pthread_mutex_lock(table->philos[i].eat);
		tmp = gettime() - table->philos[i].lst_eat;
		pthread_mutex_unlock(table->philos[i].eat);
		if (tmp >= table->tme_die && !flag)
		{
			action_print(&table->philos[i], 3);
			table->philos[i].dead = 1;
			table->finish = 1;
			return (0);
		}
	}
	if (check_finished(table))
		return (0);
	usleep(10);
	return (1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = gettime();
	while ((gettime() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	valid_input(t_table *table, int ac)
{
	if (table->n_philo < 1 || table->tme_die < -1
		|| table->tme_eat < 1 || table->tme_sleep < 1
		|| (table->tme_mst_eat < 1 && ac == 6))
	{
		printf("Invalid input\n");
		free(table);
		return (0);
	}
	return (1);
}

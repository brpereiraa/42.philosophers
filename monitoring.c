/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:44:51 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/25 15:09:20 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_monitoring(t_table *table)
{
	int flag;
	int	tmp;
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		flag = (table->philos[i].eat_count == table->tme_mst_eat && table->tme_mst_eat > 0);
		tmp = gettime() - table->philos[i].lst_eat;
		if (tmp > table->tme_die && !flag)
		{
			table->philos[i].dead = 1;
			action_print(&table->philos[i], 3);
			return (0);
		}
	}
	i = -1;
	while (++i < table->n_philo)
	{
		flag = ((table->philos[i].eat_count == table->tme_mst_eat ) && table->tme_mst_eat > 0);
		if (flag)
			break;
	}
	if(flag)
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

int	valid_input(t_table *table)
{
	if (table->n_philo == -1 || table->tme_die == -1
		|| table->tme_eat == -1 || table->tme_sleep == -1
		|| table->tme_mst_eat == -1)
	{
		printf("Invalid input\n");
		free(table);
		return (0);
	}
	return (1);
}

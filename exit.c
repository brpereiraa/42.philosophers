/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:49:26 by marvin            #+#    #+#             */
/*   Updated: 2024/09/30 10:09:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_thread_join(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		if (pthread_join(table->philos[i].t_id, NULL))
			return (printf("Error joining threads\n"), 0);
	return (1);
}

void	end_simulation(t_table *table, int flag)
{
	if (!ft_thread_join(table))
		return ;
	mtx_destroy(table);
	if (flag >= 2)
		free_structs(table);
}

void	mtx_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		pthread_mutex_destroy(&table->philos[i].eat);
		pthread_mutex_destroy(&table->philos[i].l_eat);
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->finish);
}

void	free_structs(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

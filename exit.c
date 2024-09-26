/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:12:58 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/26 16:38:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	end_simulation(t_table *table)
{
	mtx_destroy(table);
	free_structs(table);
	exit(0);
}

void	mtx_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(table->write);
}

void	free_structs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_join(table->philos[i].t_id, NULL);
	free(table->philos);
	free(table->forks);
	free(table->write);
	free(table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:49:26 by marvin            #+#    #+#             */
/*   Updated: 2024/09/29 17:49:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("Error: bad arguments\n"));
	if (!ft_init(ac, av, &table))
		return (1);
	if (!data_init(&table))
		return (1);
	while (ft_monitoring(&table))
		;
	end_simulation(&table, 2);
	return (0);
}

void	lone_philo(t_table *table)
{
	action_print(&table->philos[0], 1);
	ft_usleep(table->tme_die, table);
	action_print(&table->philos[0], 3);
}

void	start_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (ft_running(philo))
	{
		ft_eat(table, philo);
		action_print(philo, 2);
		ft_usleep(table->tme_sleep, table);
		action_print(philo, 4);
	}
}

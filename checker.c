/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/09/30 10:04:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	args_valid(t_table *table, int ac)
{
	if (table->n_philo == -1 || table->tme_die == -1
		|| table->tme_eat == -1 || table->tme_sleep == -1)
		return (printf("Invalid arguments\n"), 0);
	if (table->tme_die < 60 || table->tme_eat < 60 || table->tme_sleep < 60)
		return (printf("Times can't be lower than 60\n"), 0);
	if (table->n_philo < 1 || table->n_philo > 200)
		return (printf("Philos cant be more than 200 or less than 1\n"), 0);
	if (ac == 6 && table->max_eat < 1)
		return (printf("Number of times to eat must be higher than 0\n"), 0);
	return (1);
}

int	ft_running(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (get_value(&philo->eat, &philo->eat_count)
		>= table->max_eat && table->max_eat != 0)
		return (0);
	if (get_value(&table->finish, &table->finished))
		return (0);
	return (1);
}

int	ft_monitoring(t_table *table)
{
	return (!(check_dead(table) || check_full(table)));
}

int	check_dead(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		flag;
	int		time;

	i = -1;
	flag = 0;
	time = 0;
	while (++i < table->n_philo)
	{
		philo = &table->philos[0];
		flag = (get_value(&philo->eat, &philo->eat_count)
				== table->max_eat && table->max_eat != 0);
		time = gettime() - get_value(&philo->l_eat, &philo->lst_eat);
		if (time >= table->tme_die && !flag)
		{
			action_print(philo, 3);
			set_value(&table->finish, &table->finished, 1);
			return (1);
		}
	}
	return (0);
}

int	check_full(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		flag;

	i = -1;
	while (++i < table->n_philo)
	{
		philo = &table->philos[i];
		flag = (get_value(&philo->eat, &philo->eat_count)
				== table->max_eat && table->max_eat != 0);
		if (!flag)
			break ;
	}
	if (flag)
		return (set_value(&table->finish, &table->finished, 1), 1);
	return (0);
}

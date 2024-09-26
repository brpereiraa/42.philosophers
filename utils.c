/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:44:55 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/27 00:34:07 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_ispace(char c)
{
	return ((c == 32 || c == 9));
}

int	ft_atoi(char *str)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = -1;
	while (str[++i])
		if ((str[i] < 48 || str[i] > 57)
			&& str[i] != 32 && str[i] != 9)
			return (-1);
	if (i > 10)
		return (-1);
	i = -1;
	while (ft_ispace(str[++i]))
		;
	while (str[i])
		nbr = (nbr * 10) + str[i++] - 48;
	if (nbr > 2147483647 || nbr < -2147483646)
		return (-1);
	return ((int)nbr);
}

void	action_print(t_philo *philo, int flag)
{
	int	id;
	int	time;

	id = philo->id;
	time = gettime() - philo->table->start_time;
	if (philo->eat_count >= philo->table->tme_mst_eat
		&& philo->table->tme_mst_eat > 0)
		return ;
	pthread_mutex_lock(philo->table->write);
	if (flag == 0 && !is_dead(philo))
		printf("%i %i %sis eating\n%s", time, id, YELLOW, RESET);
	if (flag == 1 && !is_dead(philo))
		printf("%i %i %shas taken a fork\n%s", time, id, GREEN, RESET);
	if (flag == 2 && !is_dead(philo))
		printf("%i %i %sis sleeping\n%s", time, id, BLUE, RESET);
	if (flag == 3 && !is_dead(philo))
		printf("%i %i %sdied\n%s", time, id, RED, RESET);
	if (flag == 4 && !is_dead(philo))
		printf("%i %i is thinking\n%s", time, id, RESET);
	pthread_mutex_unlock(philo->table->write);
}

int	is_dead(t_philo *philo)
{
	return ((philo->eat_count == philo->table->tme_mst_eat)
		|| philo->table->finish);
}

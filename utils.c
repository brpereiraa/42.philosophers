/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:51:00 by marvin            #+#    #+#             */
/*   Updated: 2024/09/29 17:51:00 by marvin           ###   ########.fr       */
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
	return ((c == 32 || c == 9 || c == 43));
}

int	ft_atoi(char *str)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = -1;
	while (str[++i])
		if ((str[i] < 48 || str[i] > 57)
			&& str[i] != 32 && str[i] != 9 && str[i] != 43)
			return (-1);
	if (i > 10)
		return (-1);
	i = -1;
	while (ft_ispace(str[++i]))
		;
	while (str[i])
	{
		if (str[i] == 43)
			return (-1);
		nbr = (nbr * 10) + str[i++] - 48;
	}
	if (nbr > 2147483647 || nbr < -2147483646)
		return (-1);
	return ((int)nbr);
}

int	get_value(pthread_mutex_t *mtx, int *value)
{
	int	r_value;

	pthread_mutex_lock(mtx);
	r_value = *value;
	pthread_mutex_unlock(mtx);
	return (r_value);
}

void	set_value(pthread_mutex_t *mtx, int *value, int f_value)
{
	pthread_mutex_lock(mtx);
	if (f_value == -1)
		*value = *value + 1;
	else
		*value = f_value;
	pthread_mutex_unlock(mtx);
}

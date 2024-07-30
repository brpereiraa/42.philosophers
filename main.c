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

int gettime()
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec);
}

int	is_dead(t_philo *philo)
{
	int time;
	int max_time;

	max_time = philo->table->tme_die;
	time = gettime();
	if(time - philo->lst_eat > max_time)
		return (1);
	return (0)
}

int ft_ispace(char c)
{
	return ((c == 32 || c == 9));	
}

int ft_atoi(char *str)
{
	long nbr;
	int	 i;
	
	nbr = 0;
	i = -1;
	while(str[++i])
		if((str[i] < 48 || str[i] > 57) && str[i] != 32 && str[i] != 9)
			return (-1);
	if(i > 10)
		return (-1);
	i = -1;
	while(ft_ispace(str[++i]))
		;
	while(str[i])
		nbr = (nbr * 10) + str[i++] - 48;
	if(nbr > 2147483647 || nbr < -2147483646)
		return (-1);
	return ((int)nbr);
}

inline static void action_print(int id, char *msg, char *color)
{
	printf("%i: %s%s\n%s", id, color, msg, RESET);
}

void *lone_philo(void *arg)
{
	t_table *table;

	table = (t_table *) arg;
	action_print(1, "has taken a fork", GREEN);
	action_print(table->tme_die, "has died", RED);

	return NULL;
}

void start_philo(t_philo *philo)
{
	t_table *table;
	int i;
	
	i = -1;
	table = philo->table;
	while(++i < 6)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		action_print(philo->id, "has taken a fork", GREEN);
		action_print(philo->id, "has taken a fork", GREEN);
		usleep(table->tme_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->lst_eat = gettime();
		action_print(philo->id, "is sleeping", BLUE);
		usleep(table->tme_sleep);
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
	struct timeval	time;
	t_table			*table;
	int				i;
	
	if (ac != 5 && ac != 6)
		return (0);
	i = -1;
	table = malloc(sizeof(t_table));
	table->n_philo = ft_atoi(av[1]);
	table->tme_die = ft_atoi(av[2]);
	table->tme_eat = ft_atoi(av[3]);
	table->tme_sleep = ft_atoi(av[4]);
	if(ac == 6)
		table->tme_mst_eat = ft_atoi(av[5]);
	else
		table->tme_mst_eat = 0;
	if(table->n_philo == -1 || table->tme_die == -1 || table->tme_eat == -1 || table->tme_sleep == -1 || table->tme_mst_eat == -1)
	{
		printf("Invalid input\n");
		free(table);
		exit(0);
	}
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if(table->n_philo == 1)
	{
		pthread_create(&table->philos[0].t_id, NULL, lone_philo, table);
		pthread_join(table->philos[0].t_id, NULL);
		free(table->philos);
		free(table);
		exit(0);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	while(++i < table->n_philo)
		pthread_mutex_init(table->forks, NULL);
	i = -1;
	table->start_time = gettime();
	while(++i < table->n_philo)
	{	
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

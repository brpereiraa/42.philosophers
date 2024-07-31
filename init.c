#include "./philo.h"

void data_init(t_table **table, char **av, int ac)
{
	*table = malloc(sizeof(t_table));
	if(!table)
		return ;
	(*table)->n_philo = ft_atoi(av[1]);
	(*table)->tme_die = ft_atoi(av[2]);
	(*table)->tme_eat = ft_atoi(av[3]);
	(*table)->tme_sleep = ft_atoi(av[4]);
	if(ac == 6)
		(*table)->tme_mst_eat = ft_atoi(av[5]);
	else
		(*table)->tme_mst_eat = 0;
}

void	threads_init(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if(!table->philos)
		return ;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if(!table->forks)
		return ;
	while(++i < table->n_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	table->write = malloc(sizeof(pthread_mutex_t));
	if(!table->write)
		return ;
	pthread_mutex_init(table->write, NULL);
}

void lone_init(t_table *table)
{
	table->philos[0].id = 0;
	table->philos[0].table = table;
	pthread_create(&table->philos[0].t_id, NULL, lone_philo, table);
	pthread_join(table->philos[0].t_id, NULL);
	free(table->philos);
	free(table);
	exit(0);
}
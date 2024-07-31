#include "./philo.h"

int valid_input(t_table *table)
{
	if(table->n_philo == -1 || table->tme_die == -1 
		|| table->tme_eat == -1 || table->tme_sleep == -1 
		|| table->tme_mst_eat == -1)
	{
		printf("Invalid input\n");
		free(table);
		return(0);
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:27:50 by marvin            #+#    #+#             */
/*   Updated: 2024/09/29 17:27:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define RESET "\033[0m"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	pthread_mutex_t			*forks;
	pthread_mutex_t			print;
	pthread_mutex_t			finish;
	t_philo					*philos;
	int						n_philo;
	int						tme_die;
	int						tme_eat;
	int						tme_sleep;
	int						max_eat;
	int						finished;
	int						start_time;
}				t_table;

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	l_eat;
	pthread_t		t_id;
	t_table			*table;
	int				lst_eat;
	int				id;
	int				eat_count;
}				t_philo;

int		gettime(void);
int		ft_atoi(char *str);
int		get_value(pthread_mutex_t *mtx, int *value);
void	set_value(pthread_mutex_t *mtx, int *value, int f_value);

void	ft_usleep(size_t milliseconds, t_table *table);
void	get_forks(pthread_mutex_t *fork, t_philo *philo, int i);
void	action_print(t_philo *philo, int flag);
void	ft_eat(t_table *table, t_philo *philo);

int		ft_init(int ac, char **av, t_table *table);
int		data_init(t_table *table);
int		threads_init(t_table *table);
int		philo_init(t_table *table, t_philo *philo, int i);
void	*init_philo(void *arg);

int		args_valid(t_table *table, int ac);
int		ft_running(t_philo *philo);
int		ft_monitoring(t_table *table);
int		check_full(t_table *table);
int		check_dead(t_table *table);

void	lone_philo(t_table *table);
void	start_philo(t_philo *philo);

void	end_simulation(t_table *table, int flag);
int		ft_thread_join(t_table *table);
void	mtx_destroy(t_table *table);
void	free_structs(t_table *table);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:16:14 by brpereir          #+#    #+#             */
/*   Updated: 2024/07/30 03:09:52 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

# define BlACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define RESET "\033[0m"

typedef struct s_philo t_philo;
typedef struct s_table t_table;

struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		t_id;
	t_table			*table;
	int				id;
	int				lst_eat;
};

struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				n_philo;
	int				tme_die;
	int				tme_eat;
	int				tme_sleep;
	int				tme_mst_eat;
	int				start_time;
	int				flag;
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:16:14 by brpereir          #+#    #+#             */
/*   Updated: 2024/07/31 17:40:36 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define RESET "\033[0m"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		t_id;
	t_table			*table;
	int				eat_count;
	int				id;
	int				lst_eat;
};

struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write;
	t_philo			*philos;
	int				n_philo;
	int				tme_die;
	int				tme_eat;
	int				tme_sleep;
	int				tme_mst_eat;
	int				start_time;
	int				flag;
};

/**
 * @brief Retrieves the current time in seconds since the Epoch.
 *
 * This function uses `gettimeofday` to obtain the current time and
 * returns the number of seconds since the Epoch.
 *
 * @return The current time in seconds since the Epoch.
 */
int		gettime(void);

/**
 * @brief Checks if a philosopher is dead based on the time since last eating.
 *
 * This function compares the current time with the time since the philosopher
 * last ate and determines if the philosopher has exceeded the maximum time
 * allowed without eating.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 1 if the philosopher is dead, 0 otherwise.
 */
int		is_dead(t_philo *philo);

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function checks if a given character is a space (' ') or tab ('\t').
 *
 * @param c The character to check.
 * @return 1 if the character is a space or tab, 0 otherwise.
 */
int		ft_ispace(char c);

/**
 * @brief Converts a string to an integer.
 *
 * This function converts a string representation of a number to an integer.
 * It handles whitespace characters and checks for non-numeric characters.
 * Returns -1 in case of an invalid input or 
 * if the number exceeds integer limits.
 *
 * @param str The string to convert to an integer.
 * @return The integer value, or -1 if the input is invalid.
 */
int		ft_atoi(char *str);

/**
 * @brief Prints an action message for a philosopher.
 *
 * This function prints a formatted message indicating a philosopher's action.
 * The message includes the elapsed time, philosopher ID, and action description.
 *
 * @param philo Pointer to the philosopher structure.
 * @param flag An integer flag indicating the action type:
 *             1 = taking a fork, 2 = sleeping, 3 = died.
 */
void	action_print(t_philo *philo, int flag);

/**
 * @brief Handles the actions of a single philosopher.
 *
 * This function simulates the actions of a lone philosopher. It prints
 * messages indicating that the philosopher has taken a fork and has died.
 *
 * @param arg Pointer to the table structure containing philosopher data.
 * @return NULL (no return value for pthread compatibility).
 */
void	lone_philo(t_table *table);

/**
 * @brief Starts the dining process for a philosopher.
 *
 * This function simulates the philosopher's dining process, including
 * taking forks, eating, and sleeping, in a loop for a fixed number of times.
 *
 * @param philo Pointer to the philosopher structure.
 */
void	start_philo(t_philo *philo);

/**
 * @brief Initializes a philosopher's thread and starts the dining process.
 *
 * This function initializes a philosopher by setting its attributes and
 * simulates a delay for even-numbered philosophers to prevent deadlock.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL (no return value for pthread compatibility).
 */
void	*init_philo(void *arg);

int		valid_input(t_table *table);

void	data_init(t_table **table, char **av, int ac);
void	threads_init(t_table *table);
int		ft_monitoring(t_table *table);
int		ft_usleep(size_t milliseconds);
void	start_simulation(t_table *table);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:37:43 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/18 00:37:43 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define MALLOC "Error\nMemory allocation failed\n"
# define MUTEX "Error\nCould not create mutex\n"
# define TIME "Error\nCould not get time\n"
# define JOIN "Error\nThread waiting not be done\n"
# define CREATE "Error\nCould not create thread\n"

# define R_CHOPSTICK "right chopstick"
# define L_CHOPSTICK "left chopstick"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD " is dead"

typedef struct s_philo
{
	int				id;
	size_t			eat_count;
	int				left_fork;
	int				right_fork;
	u_int64_t		ldinner_time;
	pthread_t		thread;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				number_of_philos;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			edge_of_eat;
	int				is_dead;
	int				all_ate;
	int				die_id;
	u_int64_t		die_time;
	u_int64_t		start_time;
	pthread_mutex_t	m_wait;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_cnt_check;
	pthread_mutex_t	write_pt;
	t_philo			*philos;
}					t_rules;

int			making_mutex(t_rules *rules);
int			start_philo(t_rules *rules);
u_int64_t	gettime(void);
void		psleep(u_int64_t time);
void		*ft_calloc(size_t count, size_t size);
int			print(char *str, t_philo *philo);
void		destroy_free(t_rules *rules);
void		mutex_unlock_flag(t_rules *rules, t_philo *philo, int flag);
int			ft_atoi(const char *str);
int			is_digit(char **av);
int			die_check(t_rules *rules, t_philo *philo, int i);
int			start_prog(t_rules *rules);
int			philo_eats(t_philo *philo);

#endif
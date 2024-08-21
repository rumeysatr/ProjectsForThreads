/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:33:42 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/21 17:40:50 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	operations(t_philo *philo)
{
	if (philo_eats(philo) == 1)
		return (1);
	psleep(philo->rules->time_to_sleep);
	if (print(SLEEP, philo) == 1)
		return (1);
	if (print(THINK, philo) == 1)
		return (1);
	return (0);
}

void	*part(void *philosopher)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		psleep(50);
	while (operations(philo) == 0)
	{
		pthread_mutex_lock(&philo->rules->eat_cnt_check);
		if (philo->eat_count == philo->rules->edge_of_eat)
		{
			rules->all_ate++;
			pthread_mutex_unlock(&philo->rules->eat_cnt_check);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->eat_cnt_check);
	}
	return (NULL);
}

int	philo_eats(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	if (print(L_CHOPSTICK, philo) == 1)
		return (mutex_unlock_flag(rules, philo, 0), 1);
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	if (print(R_CHOPSTICK, philo) == 1)
		return (mutex_unlock_flag(rules, philo, 1), 1);
	if (print(EAT, philo) == 1)
		return (mutex_unlock_flag(rules, philo, 1), 1);
	psleep(rules->time_to_eat);
	pthread_mutex_lock(&rules->write_pt);
	philo->ldinner_time = gettime();
	pthread_mutex_unlock(&rules->write_pt);
	pthread_mutex_lock(&(rules->eat_cnt_check));
	(philo->eat_count)++;
	pthread_mutex_unlock(&(rules->eat_cnt_check));
	mutex_unlock_flag(rules, philo, 1);
	return (0);
}

void	main_thread(t_rules *rules, int i)
{
	while (1)
	{
		i = -1;
		while (++i < rules->number_of_philos)
		{
			pthread_mutex_lock(&rules->m_wait);
			if (die_check(rules, &rules->philos[i], i) == 1
				|| rules->all_ate == rules->number_of_philos)
			{
				pthread_mutex_unlock(&rules->m_wait);
				break ;
			}
			pthread_mutex_unlock(&rules->m_wait);
		}
		psleep(1);
		if (i != rules->number_of_philos)
			break ;
	}
}

int	start_philo(t_rules *rules)
{
	int		i;
	t_philo	*philosopher;

	i = -1;
	philosopher = rules->philos;
	rules->all_ate = 0;
	while (++i < rules->number_of_philos)
	{
		if (pthread_create(&rules->philos[i].thread, NULL, &part,
				&rules->philos[i]) != 0)
			return (printf(CREATE), 1);
	}
	main_thread(rules, -1);
	return (0);
}

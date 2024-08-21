/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:29:04 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/06 02:29:04 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

int	making_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = (pthread_mutex_t *)ft_calloc(rules->number_of_philos,
			sizeof(pthread_mutex_t));
	if (rules->forks == NULL)
		return (printf(MALLOC), 1);
	while (i < rules->number_of_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (printf(MUTEX), 1);
		i++;
	}
	if (pthread_mutex_init(&rules->write_pt, NULL) != 0)
		return (printf(MUTEX), 1);
	if (pthread_mutex_init(&rules->eat_cnt_check, NULL) != 0)
		return (printf(MUTEX), 1);
	if (pthread_mutex_init(&rules->m_wait, NULL) != 0)
		return (printf(MUTEX), 1);
	rules->is_dead = 0;
	rules->all_ate = 0;
	return (0);
}

void	destroy_free(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->number_of_philos)
	{
		if (&rules->forks[i])
			pthread_mutex_destroy(&rules->forks[i]);
	}
	if (rules->forks)
		free(rules->forks);
	if (rules->philos)
		free(rules->philos);
	rules->philos = NULL;
	rules->forks = NULL;
	pthread_mutex_destroy(&rules->write_pt);
	pthread_mutex_destroy(&rules->eat_cnt_check);
	pthread_mutex_destroy(&rules->m_wait);
}

void	mutex_unlock_flag(t_rules *rules, t_philo *philo, int flag)
{
	if (flag == 0)
		pthread_mutex_unlock(&rules->forks[philo->left_fork]);
	else if (flag == 1)
	{
		pthread_mutex_unlock(&rules->forks[philo->left_fork]);
		pthread_mutex_unlock(&rules->forks[philo->right_fork]);
	}
}

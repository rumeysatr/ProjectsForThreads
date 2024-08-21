/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:26:04 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/21 17:41:02 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	number;
	int		i;

	i = 0;
	number = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		number = number * 10 + str[i] - '0';
		if (number > 2147483647)
			return (0);
		i++;
	}
	if (number == 0)
		return (0);
	return (number);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	i = -1;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (++i, i < count * size)
		((char *)p)[i] = 0;
	return (p);
}

int	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->write_pt);
	if (philo->rules->is_dead != 1)
	{
		printf("%llu	Philo id: %d   %s\n",
			gettime() - philo->rules->start_time,
			philo->id, str);
		pthread_mutex_unlock(&philo->rules->write_pt);
		return (0);
	}
	return (pthread_mutex_unlock(&philo->rules->write_pt), 1);
}

int	die_check(t_rules *rules, t_philo *philo, int i)
{
	pthread_mutex_lock(&rules->write_pt);
	if ((gettime() - philo->ldinner_time) >= rules->time_to_die)
	{
		rules->is_dead = 1;
		rules->die_id = i + 1;
		rules->die_time = gettime() - rules->start_time;
		pthread_mutex_unlock(&rules->write_pt);
		return (1);
	}
	pthread_mutex_unlock(&rules->write_pt);
	return (0);
}

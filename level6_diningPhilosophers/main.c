/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:11:52 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/13 17:11:52 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	values(t_rules *rules, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i])
	{
		if (av[i][j + 1] == 0 && av[i][j] == '0')
			return (1);
		i++;
	}
	rules->number_of_philos = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		rules->edge_of_eat = ft_atoi(av[5]);
	return (0);
}

int	philo_init(t_rules *rules)
{
	int	i;

	i = rules->number_of_philos;
	rules->philos = (t_philo *)ft_calloc(i, sizeof(t_philo));
	if (rules->philos == NULL)
		return (printf("%s\n", MALLOC), 1);
	rules->start_time = gettime();
	while (--i >= 0)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].left_fork = i;
		if ((i + 1) == rules->number_of_philos)
			rules->philos[i].right_fork = 0;
		else
			rules->philos[i].right_fork = i + 1;
		rules->philos[i].eat_count = 0;
		rules->philos[i].ldinner_time = rules->start_time;
		rules->philos[i].rules = rules;
	}
	return (0);
}

void	*only_one(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->rules->start_time = gettime();
	pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
	print(L_CHOPSTICK, philo);
	pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	psleep(philo->rules->time_to_die);
	print(DEAD, philo);
	return (NULL);
}

int	start_prog(t_rules *rules)
{
	int	i;

	i = -1;
	if (start_philo(rules) == 1)
		return (1);
	while (++i < rules->number_of_philos)
	{
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			return (printf(JOIN), 1);
	}
	if (rules->is_dead)
		printf("%llu	Philo id: %d  %s\n", rules->die_time, rules->die_id,
			DEAD);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ac < 5 || ac > 6)
		return (printf("Please write 5 or 6 arguments"), 1);
	if (is_digit(av))
		return (printf("Please write only numbers for arguments"), 1);
	if (values(&rules, av))
		return (printf("Argument error"), 1);
	if (philo_init(&rules))
		return (printf("Philo Init Error"), 1);
	if (making_mutex(&rules))
		return (printf("Mutex error"), 1);
	if (rules.number_of_philos == 1)
	{
		if (pthread_create(&rules.philos[0].thread, NULL, &only_one,
				&rules.philos[0]) != 0)
			return (printf(CREATE), destroy_free(&rules), 1);
		if (pthread_join(rules.philos[0].thread, NULL) != 0)
			return (printf(CREATE), destroy_free(&rules), 1);
		return (destroy_free(&rules), 1);
	}
	if (start_prog(&rules) == 1)
		return (destroy_free(&rules), 1);
	return (destroy_free(&rules), 0);
}

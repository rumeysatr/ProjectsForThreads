/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutatar <rutatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:28:43 by rutatar           #+#    #+#             */
/*   Updated: 2024/08/20 20:02:32 by rutatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

u_int64_t	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf(TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	psleep(u_int64_t time)
{
	size_t	start;

	start = gettime();
	while ((gettime() - start) < time)
		usleep(250);
}

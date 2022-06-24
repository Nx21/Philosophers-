/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:50:27 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/25 00:24:17 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' )
			return (0);
		number *= 10;
		number += str[i] - 48;
		i++;
		if (number > 2147483647)
			return (0);
	}
	return (number);
}

void	ft_delay(long long time)
{
	long long	current_time;

	current_time = get_time();
	while (get_time() - current_time < time)
		;
}

void	my_print(char *s, t_data *data, t_vars *vars, int isdead)
{
	sem_wait(data->print);
	printf("%-5lld %-2d %s\n", get_time() - data->begin_time, \
		vars->idx + 1, s);
	if (!isdead)
		sem_post(data->print);
	else
	{
		sem_post(data->stop);
		sem_wait(data->dead);
	}
}

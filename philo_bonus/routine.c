/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:18:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/22 02:36:24 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_vars *vars, t_data *data)
{
	sem_wait(data->fork);
	printf("%-5lld %-2d has taken a fork\n", get_time() - data->begin_time, \
		vars->idx + 1);
	sem_wait(data->fork);
	printf("%-5lld %-2d is eating\n", get_time() - data->begin_time, \
		vars->idx + 1);
	vars->nbr_time++;
	if (vars->nbr_time == data->nbr_time)
		sem_post(data->must_eat);
	vars->time = get_time();
	ft_delay(data->eat_time);
	sem_post(data->fork);
	sem_post(data->fork);
	return (ft_sleep(vars, data));
}

void	ft_sleep(t_vars *vars, t_data *data)
{
	printf("%-5lld %-2d is sleeping\n", get_time() - data->begin_time, \
		vars->idx + 1);
	ft_delay(data->sleep_time);
	return (ft_think(vars, data));
}

void	ft_think(t_vars *vars, t_data *data)
{
	printf("%-5lld %-2d is thinking\n", get_time() - data->begin_time, \
		vars->idx + 1);
	return (ft_eat(vars, data));
}

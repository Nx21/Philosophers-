/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:18:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/26 23:22:05 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_vars *vars, t_data *data)
{
	sem_wait(data->fork);
	my_print("has taken a fork", data, vars, 0);
	sem_wait(data->fork);
	my_print("is eating", data, vars, 0);
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
	my_print("is sleeping", data, vars, 0);
	ft_delay(data->sleep_time);
	return (ft_think(vars, data));
}

void	ft_think(t_vars *vars, t_data *data)
{
	my_print("is thinking", data, vars, 0);
	return (ft_eat(vars, data));
}

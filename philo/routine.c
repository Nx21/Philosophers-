/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:18:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/26 23:05:41 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_vars *vars, t_data *data)
{
	pthread_mutex_lock(&data->fork[(!(vars->idx % 2) + vars->idx) % data->nbr]);
	if (my_printf("has taken a fork", data, vars, 0))
		return (1);
	pthread_mutex_lock(&data->fork[((vars->idx % 2) + vars->idx) % data->nbr]);
	if (my_printf("is eating", data, vars, 0))
		return (1);
	vars->nbr_time++;
	ft_delay(data->eat_time, data);
	pthread_mutex_lock(&data->fork[data->nbr]);
	if (vars->nbr_time == data->nbr_time)
		data->comp_philo++;
	pthread_mutex_unlock(&data->fork[data->nbr]);
	vars->time = get_time();
	return (0);
}

int	ft_sleep(t_vars *vars, t_data *data)
{
	pthread_mutex_unlock(&data->fork[(!(vars->idx % 2) + vars->idx) \
	% data->nbr]);
	pthread_mutex_unlock(&data->fork[((vars->idx % 2) + vars->idx) \
	% data->nbr]);
	if (my_printf("is sleeping", data, vars, 0))
		return (1);
	ft_delay(data->sleep_time, data);
	return (0);
}

int	ft_think(t_vars *vars, t_data *data)
{
	if (my_printf("is thinking", data, vars, 0))
		return (1);
	usleep(100);
	return (0);
}

void	*routine(void *addr)
{
	t_vars	*vars;
	t_data	*data;

	vars = addr;
	data = vars->data;
	while (vars->idx % 2)
		if (ft_think(vars, data) || ft_eat(vars, data) \
		|| ft_sleep(vars, data))
			return (NULL);
	while (!(vars->idx % 2))
		if (ft_eat(vars, data) \
		|| ft_sleep(vars, data) || ft_think(vars, data))
			return (NULL);
	return (NULL);
}

void	*ft_check(void *addr)
{
	t_vars	*vars;
	t_data	*data;
	int		i;

	vars = addr;
	data = vars->data;
	i = 0;
	while (get_time() - vars[i].time <= data->die_time)
	{
		i++;
		if (i >= data->nbr)
			i = 0;
	}
	my_printf("is died", data, vars, 1);
	i = 0;
	while (i < data->nbr)
	{
		pthread_mutex_unlock(&data->fork[i]);
		i++;
	}
	return (NULL);
}

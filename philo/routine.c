/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:18:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/26 19:54:14 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_printf(char *s, t_data *data, t_vars *vars, int isdied)
{
	pthread_mutex_lock(&data->print);
	if (data->stop || data->comp_philo >= data->nbr)
	{
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	if (isdied)
		data->stop = 1;
	printf("%-5lld %-2d %s\n", get_time() - data->begin_time, \
		vars->idx + 1, s);
	pthread_mutex_unlock(&data->print);
	return (0);
}

int	ft_eat(t_vars *vars, t_data *data)
{
	ft_lock(data, ((vars->idx + 1) % 2 + vars->idx) % data->nbr);
	if (my_printf("has taken a fork", data, vars, 0))
		return (1);
	ft_lock(data, (vars->idx % 2 + vars->idx) % data->nbr);
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
	ft_unlock(data, ((vars->idx + 1) % 2 + vars->idx) % data->nbr);
	ft_unlock(data, (vars->idx % 2 + vars->idx) % data->nbr);
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
		if(ft_think(vars, data) || ft_eat(vars, data)
			|| ft_sleep(vars, data))
			return (NULL);
	while (!(vars->idx % 2))
		if(ft_eat(vars, data) \
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

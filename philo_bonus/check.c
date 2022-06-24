/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:12:32 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/22 02:33:07 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *addr)
{
	t_vars	*vars;
	t_data	*data;

	vars = addr;
	data = vars->data;
	if (vars->idx >= data->nbr / 2)
		ft_think(vars, data);
	else
		ft_eat(vars, data);
	return (NULL);
}

void	*ft_dead(void *addr)
{
	t_vars	*vars;
	t_data	*data;
	int		i;

	vars = addr;
	data = vars->data;
	i = 0;
	while (get_time() - vars->time <= data->die_time)
		;
	sem_post(data->stop);
	sem_wait(data->dead);
	printf("%-5lld %-2d is died\n", get_time() - data->begin_time, \
		vars->idx + 1);
	return (NULL);
}

void	*ft_must_eat(void *addr)
{
	t_vars	*vars;
	t_data	*data;
	int		i;

	vars = addr;
	data = vars->data;
	i = 0;
	while (i < data->nbr)
	{
		sem_wait(data->must_eat);
		i++;
	}
	sem_post(data->stop);
	exit(0);
}

void	*ft_check(void *addr)
{
	t_vars	*vars;
	t_data	*data;

	vars = addr;
	data = vars->data;
	sem_wait(data->stop);
	sem_post(data->stop);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:27:04 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/20 19:53:34 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_free_data(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/stop");
	sem_unlink("/must_eat");
	sem_unlink("/dead");
	sem_close(data->fork);
	sem_close(data->dead);
	sem_close(data->stop);
	sem_close(data->must_eat);
	printf("Error input");
	return (1);
}

int	init_data(t_data *data, char **av)
{
	data->nbr = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->nbr_time = -1;
	data->dead = 0;
	if (av[5])
		data->nbr_time = ft_atoi(av[5]);
	data->begin_time = get_time();
	if (!(data->nbr && data->die_time && data->sleep_time && \
	data->eat_time && data->nbr_time))
		return (1);
	sem_unlink("/fork");
	sem_unlink("/stop");
	sem_unlink("/must_eat");
	sem_unlink("/dead");
	data->dead = sem_open("/dead", O_CREAT, 0, 1);
	data->fork = sem_open("/fork", O_CREAT, 0, data->nbr);
	data->stop = sem_open("/stop", O_CREAT, 0, 0);
	data->must_eat = sem_open("/must_eat", O_CREAT, 0, 0);
	return (0);
}

void	init_vars(t_vars *vars, t_data *data, int i)
{
	vars->idx = i;
	vars->nbr_time = 0;
	vars->time = get_time();
	vars->data = data;
}

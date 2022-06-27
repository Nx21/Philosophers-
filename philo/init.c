/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:27:04 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/27 20:16:11 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr + 1)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	printf("Error input");
	return (1);
}

int	init_data(t_data *data, char **av)
{
	int	i;

	i = -1;
	data->nbr = ft_atoi(av[1]);
	data->fork = malloc(sizeof(pthread_mutex_t) * (data->nbr + 1));
	if(data->fork)
		return (1);
	while (++i < data->nbr + 1)
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->nbr_time = -1;
	data->comp_philo = 0;
	data->stop = 0;
	if (av[5])
		data->nbr_time = ft_atoi(av[5]);
	data->begin_time = get_time();
	if (!(data->nbr && data->die_time && data->sleep_time \
		&& data->eat_time && data->nbr_time))
		return (1);
	return (0);
}

void	init_vars(t_vars *vars, t_data *data, int i)
{
	vars->idx = i;
	vars->data = data;
	vars->nbr_time = 0;
	vars->time = get_time();
}

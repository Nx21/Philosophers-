/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:58:23 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/24 19:08:15 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_data *data, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < data->nbr + 1)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	free(vars);
}

void	ft_detach(pthread_t *thrid, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		pthread_detach(thrid[i]);
		i++;
	}
	free(thrid);
}

int	creat_tread(t_data data, t_vars *vars)
{
	int				i;
	pthread_t		*thrid;

	i = 0;
	thrid = malloc(sizeof(pthread_t) * (data.nbr + 1));
	if (!thrid)
		return (1);
	while (i < data.nbr)
	{
		init_vars(&vars[i], &data, i);
		if (pthread_create(&(thrid[i]), NULL, &routine, &(vars[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&(thrid[i]), NULL, &ft_check, vars) != 0)
		return (1);
	i = 0;
	while (i < data.nbr + 1)
	{
		if (pthread_join((thrid[i]), NULL) != 0)
			return (1);
		i++;
	}
	ft_detach(thrid, data.nbr);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_vars			*vars;

	if (argc != 6 && argc != 5)
		return (printf("Error input"));
	if (init_data(&data, argv))
		return (ft_free_data(&data));
	vars = malloc(sizeof(t_vars) * data.nbr);
	if (!vars)
		return (0);
	if (creat_tread(data, vars))
		return (ft_free_data(&data));
	ft_destroy(&data, vars);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:58:23 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/25 01:48:11 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy(pid_t *pid, t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/stop");
	sem_unlink("/must_eat");
	sem_unlink("/dead");
	sem_unlink("/print");
	sem_close(data->print);
	sem_close(data->fork);
	sem_close(data->dead);
	sem_close(data->stop);
	sem_close(data->must_eat);
	free(pid);
}

int	creat_pros(t_data *data, int idx)
{
	pthread_t	thrid[4];
	t_vars		vars;
	int			i;

	init_vars(&vars, data, idx);
	if (pthread_create(&(thrid[0]), NULL, &routine, &vars))
		return (1);
	if (pthread_create(&(thrid[1]), NULL, &ft_check, &vars))
		return (1);
	if (pthread_create(&(thrid[2]), NULL, &ft_dead, &vars))
		return (1);
	if (vars.idx == 0 && pthread_create(&(thrid[3]), NULL, &ft_must_eat, &vars))
		return (1);
	i = 0;
	while (i < 3 + !(vars.idx))
	{
		if (pthread_join((thrid[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	creat_pro(t_data data, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < data.nbr)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (creat_pros(&data, i))
				exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data.nbr)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}	
}

int	main(int argc, char *argv[])
{
	t_data	data;
	pid_t	*pid;

	if (argc != 6 && argc != 5)
		return (printf("Error input"));
	if (init_data(&data, argv))
		return (ft_free_data(&data));
	pid = malloc(sizeof(pid_t) * data.nbr);
	if(!pid)
		return 0;
	creat_pro(data, pid);
	ft_destroy(pid, &data);
	return (0);
}

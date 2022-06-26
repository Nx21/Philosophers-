/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:58:21 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/26 23:01:19 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data {
	int				nbr;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nbr_time;
	char			stop;
	int				comp_philo;
	long long		begin_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_vars {
	int			idx;
	long long	time;
	int			nbr_time;
	t_data		*data;
}				t_vars;

int			ft_free_data(t_data *data);
int			ft_atoi(char *str);
long long	get_time(void);
void		ft_error(void);
int			init_data(t_data *data, char **av);
void		init_vars(t_vars *vars, t_data *data, int i);
void		ft_delay(long long time, t_data *data);
void		*routine(void *addr);
void		*ft_check(void *addr);
int			my_printf(char *s, t_data *data, t_vars *vars, int isdied);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:58:21 by nhanafi           #+#    #+#             */
/*   Updated: 2022/06/25 00:20:27 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_data {
	int			nbr;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			nbr_time;
	long long	begin_time;
	sem_t		*dead; 
	sem_t		*fork;
	sem_t		*stop;
	sem_t		*must_eat;
	sem_t		*print;
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
void		ft_delay(long long time);
void		ft_eat(t_vars *vars, t_data *data);
void		ft_sleep(t_vars *vars, t_data *data);
void		ft_think(t_vars *vars, t_data *data);
void		*routine(void *addr);
void		*ft_check(void *addr);
void		*ft_dead(void *addr);
void		*ft_must_eat(void *addr);
void		my_print(char *s, t_data *data, t_vars *vars, int isdead);
#endif
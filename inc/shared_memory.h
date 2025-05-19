/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:34:55 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/19 20:32:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_MEMORY_H
# define SHARED_MEMORY_H

# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdlib.h>
# include <sys/sem.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"


# define SHM_KEY 1234
# define SEM_KEY 5633

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

typedef struct s_shared_data
{
	bool		gameStarted;
	int			boardSize;
	int			playerCount;
	int			connectedPlayers;
	int			speed;
	int			**board; //[][] 0 = vide, ou si != 0 id du joueur
}		t_shared_data;

typedef struct s_shared_data_manager
{
	bool			isHost;
	int				shmid;
	int				semid;
	t_shared_data	*data;
}		t_shared_data_manager;

int				sem_wait(int semid);
int				sem_signal(int semid);
int				create_or_join_semaphore(int initial_value, bool *is_creator);
t_shared_data	*create_or_get_shared_memory(int *shmid, bool create);
int				write_game_rules(t_shared_data *data, int semid, int playerCount, int boardSize, int speed, t_memlist **mem);
void			clean_shared_memory(int shmid, int semid, t_shared_data *data, bool isHost);
void			remove_semaphore(int semid, int is_host);

#endif

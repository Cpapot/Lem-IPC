/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:34:55 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 18:45:30 by cpapot           ###   ########.fr       */
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


# define SHM_KEY 1232
# define SEM_KEY 5604

union semun {
	int val;               /* Valeur pour SETVAL */
	struct semid_ds *buf;  /* Buffer pour IPC_STAT, IPC_SET */
	unsigned short *array; /* Array pour GETALL, SETALL */
	struct seminfo *__buf; /* Buffer pour IPC_INFO */
};

typedef struct s_shared_data
{
	bool		gameStarted;
	bool		isFinish;
	int			boardSize;
	int			playerCount;
	int			connectedPlayers;
	int			speed;
	int			board[1000]; //[] 0 = vide, ou si != 0 id de lekip
}		t_shared_data;

typedef struct s_player_postion {
	int x;
	int y;
} t_player_position;

typedef struct s_shared_data_manager
{
	t_memlist			*localeGameData;
	bool				isHost;
	int					hostTeamId;
	int					shmid;
	int					semid;
	t_player_position	*actualPlayerPosition;
	t_shared_data		*data;
}		t_shared_data_manager;

int				sem_wait(int semid);
int				sem_signal(int semid);
int				create_or_join_semaphore(int initial_value, bool *is_creator);
t_shared_data	*create_or_get_shared_memory(int *shmid, bool create);
int				write_game_rules(t_shared_data *data, int semid, int playerCount, int boardSize, int speed, t_memlist **mem);
void			clean_shared_memory(int shmid, t_shared_data *data, bool isHost);
void			remove_semaphore(int semid, int is_host);
int				register_new_player(t_shared_data *data, int semid);
int				check_connected_players(t_shared_data *data, int semid);


#endif

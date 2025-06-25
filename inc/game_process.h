/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:34:19 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/25 18:41:31 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_PROCESS_H
# define GAME_PROCESS_H

#include "../inc/ipc.h"
#include "../inc/shared_memory.h"

extern t_shared_data_manager	*g_shmData;


t_player_position	*set_random_player_position(int teamID, int *board, int boardSize, int semid, t_memlist **mem);
void				handle_client_close(int sig);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:16:29 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 13:37:10 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IPC_H
# define LEM_IPC_H

# include "../libft/includes/libft.h"

# define DEBUG_PRINT	"\033[7;49;96mDEBUG\033[0m :"
# define ERROR_PRINT	"\033[7;49;91mERROR\033[0m :"
# define INFO_PRINT		"\033[7;49;92mINFO\033[0m :"

typedef struct s_game_data
{
	unsigned int		playerToStart;
	unsigned int		gridSize;
}	t_game_data;

#endif

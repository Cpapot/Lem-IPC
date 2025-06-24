/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:46:31 by cpapot            #+#    #+#             */
/*   Updated: 2025/06/24 19:23:31 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPC_H
# define IPC_H

# include <sys/ipc.h>
# include <sys/msg.h>
# include <errno.h>
# include <stdio.h>

# include "../libft/includes/libft.h"
# include "lem-ipc.h"

# define MSG_KEY	0526
# define MAX_TEXT	512

typedef struct	s_message {
	long msg_type;
	char msg_text[MAX_TEXT];
}			t_message;

typedef struct	s_ipc {
	bool		isHost;
	int			msgid;
	t_message	msg;
}			t_ipc;

int			ipc_create_or_connect(t_ipc *ipc);
int			ipc_clean(t_ipc *ipc);
int			ipc_receive_message(t_ipc *ipc);
int			ipc_send_message(t_ipc *ipc, char *message);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:44:37 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/13 13:41:57 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ipc.h"

int		ipc_create_or_connect(t_ipc *ipc)
{
	int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT | IPC_EXCL);
	if (msgid != -1)
	{
		ft_printf("%s No host found, creating channel\n", INFO_PRINT);
		ipc->isHost = true;
		ipc->msgid = msgid;
		return 1;
	}
	else if (errno == EEXIST)
	{
		ft_printf("%s Host already exist, trying to connect\n", INFO_PRINT);
		ipc->isHost = false;
		ipc->msgid = msgget(MSG_KEY, 0666);
		if (ipc->msgid == -1)
		{
			perror("msgget (connexion)");
			return 0;
		}
		ft_printf("%s Connected\n", INFO_PRINT);
		return 2;
	}
	else
	{
		perror("msgget");
		return 0;
	}
}

int		ipc_clean(t_ipc *ipc)
{
	if (ipc->isHost)
	{
		if (msgctl(ipc->msgid, IPC_RMID, NULL) == -1)
		{
			perror("msgctl");
			return 1;
		}
		ft_printf("%s Channel closed\n", INFO_PRINT);
	}
	return 0;
}

int		ipc_receive_message(t_ipc *ipc)
{
	if (msgrcv(ipc->msgid, &ipc->msg, sizeof(ipc->msg.msg_text), 0, 0) == -1)
	{
		perror("msgrcv");
		return 1;
	}
	ft_printf("%s Message received : \"%s\"\n", DEBUG_PRINT, ipc->msg.msg_text);
	return 0;
}

int		ipc_send_message(t_ipc *ipc, char *message)
{
	ipc->msg.msg_type = 1;
	snprintf(ipc->msg.msg_text, MAX_TEXT, "%s", message);
	if (msgsnd(ipc->msgid, &ipc->msg, sizeof(ipc->msg.msg_text), 0) == -1) {
		perror("msgsnd");
		return 1;
	}
	ft_printf("%s Message sent : \"%s\"\n", DEBUG_PRINT, ipc->msg.msg_text);
	return 0;
}



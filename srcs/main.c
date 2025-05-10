/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:15:54 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 18:01:16 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-ipc.h"



int main(void)
{
	ft_printf("Hello, World!\n");

	// on verifie si la queue de message existe déjà

	// si oui on n'est pas l'host
	// on se connecte à la queue de message
	// on envoie un message pour dire qu'on est là
	// on recupere le terrain (memoire partagée)
	// on attend le message qui nous dit que la partie commence

	// sinon on est l'host et on crée la queue de message
	// on demande le nombre de de joueurs (depuis le argv)
	// on initalise le terrain (on cree un tableau de memoire partagé)
	// on attend le message de chaque joueur pour dire qu'il sont la
	// on envoie le message pour dire que la partie commence

	
}

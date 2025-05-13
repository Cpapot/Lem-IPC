#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
# include <sys/ipc.h>
# include <sys/msg.h>

#define MSG_KEY 0666
#define MAX_TEXT 512

struct message {
	long msg_type;
	char msg_text[MAX_TEXT];
};

int main() {
    int msgid;
    struct message msg;

    // Tenter de créer la file (IPC_CREAT | IPC_EXCL)
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT | IPC_EXCL);
    if (msgid != -1) {
        // Succès : ce processus est le RECEVEUR
        printf("🟢 Première exécution : file créée. En attente de message...\n");

        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("📩 Message reçu : %s\n", msg.msg_text);

        // Nettoyage : suppression de la file
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }

        printf("🧹 File supprimée. Fin.\n");

    } else if (errno == EEXIST) {
        // La file existe déjà : ce processus est un ENVOYEUR
        msgid = msgget(MSG_KEY, 0666);
        if (msgid == -1) {
            perror("msgget (connexion)");
            exit(1);
        }

        msg.msg_type = 1;
        snprintf(msg.msg_text, MAX_TEXT, "oui");

        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("📤 Message envoyé : %s\n", msg.msg_text);

    } else {
        perror("msgget");
        exit(1);
    }

    return 0;
}

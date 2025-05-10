#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    mqd_t mq;
    char buf[256];

    mq = mq_open("/maqueue", O_WRONLY);
    if (mq != (mqd_t)-1) {  // si déjà existante → expéditeur
        mq_send(mq, "Salut !", 8, 0);
        mq_close(mq);
    } else {  // sinon → récepteur
        struct mq_attr a = {0, 10, 256, 0};
        mq = mq_open("/maqueue", O_CREAT | O_RDONLY, 0644, &a);
        mq_receive(mq, buf, 256, NULL);
        printf("Reçu: %s\n", buf);
        mq_close(mq);
        mq_unlink("/maqueue");
    }
    return 0;
}

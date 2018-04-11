//
// Created by yanchunlan on 2018/4/11.
//

#ifndef SOCKETPROCESS_NATIVE_LIB_H
#define SOCKETPROCESS_NATIVE_LIB_H

#endif // ADV

#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/signal.h>
#define LOG_TAG "tuch"
#define LOGE(...) _android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void child_do_work();
int child_create_channel();

void child_listen_msg();

#endif //SOCKETPROCESS_NATIVE_LIB_H

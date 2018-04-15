#include <jni.h>
#include <string>


#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "native_lib.h"

//子进程有权限访问父进程的私有目录,在此建立跨进程通信的套接字文件
const char *PATH = "/data/data/com.example.yanchunlan.socketprocess/my.sock";
int m_child;
const char *userId;

/**
 *  创建服务端的socket
 */
int child_create_channel() {
    // 定义协议
    int listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (listenfd < 0) {
        LOGE("child_create_channel error");
        return listenfd;
    }

    unlink(PATH); // 情况上次的链接，防止重复

    struct sockaddr_un addr;
    // 清空结构体内存
    memset(&addr, 0, sizeof(sockaddr_un));
    addr.sun_family = AF_LOCAL;// 声明协议 服务端或本地
    strcpy(addr.sun_path, PATH); // 声明地址，端口号

    if (bind(listenfd, (const sockaddr *) &addr, sizeof(sockaddr_un)) < 0) {
        LOGE("bind error ");
        return 0;
    }

    // 最多监听5客户端
    listen(listenfd, 5);

    int connfd = 0;
    // 死循环 保证宿主进程链接成功
    while (1) {
        // 返回客户端的地址  阻塞时函数
        if ((connfd = accept(listenfd, NULL, NULL)) < 0) {

            if (errno == EINTR) {
                // 链接成功
                continue;
            } else {
                LOGE("accept error ");
                return 0;
            }

        }

        m_child = connfd;
        LOGE("accept success ");
        break;
    }
    return 1; // return 1 代表成功
};

/**
 * 服务端读取信息
 */
void child_listen_msg() {
    fd_set rfds;
    struct timeval timeout = {3, 0};
    while (1) {
        //清空集合内容  ，缓存 ，path，端口号
        FD_ZERO(&rfds);
        // 新建
        FD_SET(m_child, &rfds);
        int r = select(m_child + 1, &rfds, NULL, NULL, &timeout);// 一般设置监视文件数+1
        LOGE("read message %d", r);
        if (r > 0) {
            // 定义缓冲区
            char pkg[266] = {0};

            // 保证所读到信息 是 指定apk客户端
            if (FD_ISSET(m_child, &rfds)) {
                // 阻赛塞函数
                int result = read(m_child, pkg, sizeof(pkg));
                execlp("am", "am", "startservice", "--user", userId,
                       "com.example.yanchunlan.socketprocess/com.example.yanchunlan.socketprocess.ProcessService",
                       (char *) NULL);
                break;
            }
        }
    }
};


extern "C"
JNIEXPORT void JNICALL
Java_com_example_yanchunlan_socketprocess_Watcher_createWatcher(JNIEnv *env, jobject instance,
                                                                jstring userId_) {
    userId = env->GetStringUTFChars(userId_, 0);

    // 开双进程
    pid_t pid = fork();
    if (pid < 0) {
    } else if (pid == 0) {
        // 子进程  守护进程

        // 开启socket 服务端  开启成功之后就读
        if (child_create_channel() > 0) {
            child_listen_msg();
        }
    } else if (pid > 0) {
        // 父进程
    }

    env->ReleaseStringUTFChars(userId_, userId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_yanchunlan_socketprocess_Watcher_connectMonitor(JNIEnv *env, jobject instance) {

    //客户端  主进程
    int socked;
    while (1) {
        LOGE("client socket create");
        socked = socket(AF_LOCAL, SOCK_STREAM, 0);
        if (socked < 0) {
            LOGE("child_create_channel error");
            return;
        }
        struct sockaddr_un addr;
        // 清空结构体内存
        memset(&addr, 0, sizeof(sockaddr_un));
        addr.sun_family = AF_LOCAL;// 声明协议 服务端或本地
        strcpy(addr.sun_path, PATH); // 声明地址，端口号

        if (connect(socked, (const sockaddr *) &addr, sizeof(sockaddr_un)) < 0) {
            LOGE("connect error ");
            // 连接失败 休眠一秒连接链接
            close(socked);
            sleep(1);
            continue;
        }
        LOGE("连接成功");
        break;
    }


}
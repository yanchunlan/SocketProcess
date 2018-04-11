#include <jni.h>
#include <string>


#include <native_lib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>


void child_listen_msg();

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_yanchunlan_socketprocess_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}





/**
 * 服务端读取信息
 * 客户端
 * @return
 */
int child_create_channel(){
    // ip  端口 文件
    int listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr addr;

    // 清空内存
//    memset()


//    bind(listenfd,);




};

/**
 * 创建服务端的socket
 */
void child_listen_msg() {

};

void child_do_work(){
    // 开启socket 服务端
    if (child_create_channel()) {
        child_listen_msg();
    }

}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_yanchunlan_socketprocess_Watcher_createWatcher(JNIEnv *env, jobject instance,
                                                                jstring userId_) {
    const char *userId = env->GetStringUTFChars(userId_, 0);

    // 开双进程
    pid_t pid = fork();
    if (pid < 0) {

    } else if (pid == 0) {
        // 子进程  守护进程
        child_do_work();

    } else if (pid > 0) {
        // 父进程

    }





    env->ReleaseStringUTFChars(userId_, userId);
}

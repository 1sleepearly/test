#include<stdio.h>
#include<WinSock2.h>//网络编程头文件，引入静态库
#pragma comment(lib,"ws2_32.lib")

void sendhtml(SOCKET s, char* filename);

int merror(int redata, int error, const char* showinfo) {
    if (redata == error) {               //返回值判断是否失败，redata是否等于错误
        perror(showinfo);         //输出错误原因
        getchar();
        return -1;
    }
    return 0;
}

int main() {
    WSADATA wsadata;
    int isok = WSAStartup(MAKEWORD(2, 2), &wsadata);//确定socket协议版本
    merror(isok, WSAEINVAL, "申请socket失败");

    //第一个参数：协议族，决定socket的地址类型
    //第二个参数：传输类型，SOCk_STREAN流传输
    //第三个参数：传输协议，tcp
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//af-inet使用ipv4地址，创建socket
    merror(client, INVALID_SOCKET, "创建socket失败");

    //创建服务器协议地址族
    struct sockaddr_in seraddr;//存放
    seraddr.sin_family = AF_INET;    //获取服务器协议族
    seraddr.sin_port = htons(50000);     //端口,小端数据转换为大端存储
    //seraddr.sin_addr.s_addr = inet_addr("192.168.0.131");  
    seraddr.sin_addr.s_addr = 16777343;
    //连接服务器
    int r = connect(client, (sockaddr*) &seraddr, sizeof seraddr);

    //通信
    char buff[100];
    while (1) {
        scanf("%s",buff);//接受用户输入
        send(client, buff, strlen(buff), NULL);//发送给服务器

    }
    closesocket(client);
    WSACleanup();

    getchar();
    return 0;
}



#include<stdio.h>
#include<WinSock2.h>//������ͷ�ļ������뾲̬��
#pragma comment(lib,"ws2_32.lib")

void sendhtml(SOCKET s, char* filename);

int merror(int redata, int error, const char* showinfo) {
    if (redata == error) {               //����ֵ�ж��Ƿ�ʧ�ܣ�redata�Ƿ���ڴ���
        perror(showinfo);         //�������ԭ��
        getchar();
        return -1;
    }
    return 0;
}

int main() {
    WSADATA wsadata;
    int isok = WSAStartup(MAKEWORD(2, 2), &wsadata);//ȷ��socketЭ��汾
    merror(isok, WSAEINVAL, "����socketʧ��");

    //��һ��������Э���壬����socket�ĵ�ַ����
    //�ڶ����������������ͣ�SOCk_STREAN������
    //����������������Э�飬tcp
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//af-inetʹ��ipv4��ַ������socket
    merror(client, INVALID_SOCKET, "����socketʧ��");

    //����������Э���ַ��
    struct sockaddr_in seraddr;//���
    seraddr.sin_family = AF_INET;    //��ȡ������Э����
    seraddr.sin_port = htons(50000);     //�˿�,С������ת��Ϊ��˴洢
    //seraddr.sin_addr.s_addr = inet_addr("192.168.0.131");  
    seraddr.sin_addr.s_addr = 16777343;
    //���ӷ�����
    int r = connect(client, (sockaddr*) &seraddr, sizeof seraddr);

    //ͨ��
    char buff[100];
    while (1) {
        scanf("%s",buff);//�����û�����
        send(client, buff, strlen(buff), NULL);//���͸�������

    }
    closesocket(client);
    WSACleanup();

    getchar();
    return 0;
}



#include<stdio.h>
#include<WinSock2.h>//������ͷ�ļ������뾲̬��
#pragma comment(lib,"ws2_32.lib")


void CyberPrisoner(int a, int b);  //����
int merror(int redata, int error, const char* showinfo);  //����Ƿ����
void func(int index);//ͨ��
void finalAnswer();
void roundAnswer(int a,int b);
void roundfuc();


int sumA, sumB;//��¼AB��ҵ��������
int answer[2];
int round;//��¼��Ϸ����
char revdate[1024] = "";
SOCKET server;

struct sockaddr_in claddr; //���ܿͻ��˵���Ϣ
int cllen = sizeof(claddr);
SOCKET clientSocket[2000];//���������Խ��ܶ���ͻ���

int main() {
    printf("��ӭ����Cyber-Prisoner�����,�����ӿͻ���\n");
    
    WSADATA wsadata;
    int isok = WSAStartup(MAKEWORD(2, 2), &wsadata);//ȷ��socketЭ��汾
    merror(isok, WSAEINVAL, "����socketʧ��");

    //��һ��������Э���壬����socket�ĵ�ַ����
    //�ڶ����������������ͣ�SOCk_STREAN������
    //����������������Э�飬tcp
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//af-inetʹ��ipv4��ַ������socket
    merror(server, INVALID_SOCKET, "����socketʧ��");

    //����������Э���ַ��
    struct sockaddr_in seraddr;//���
    seraddr.sin_family = AF_INET;    //Э����
    seraddr.sin_port = htons(50000);     //�˿�,С������ת��Ϊ��˴洢
    seraddr.sin_addr.s_addr = INADDR_ANY;  //���������ַ

    isok = bind(server, &seraddr, sizeof(seraddr));   //��socket��Э����
    merror(isok, SOCKET_ERROR, "��ʧ��\n");

    isok = listen(server, 100);    //�ͻ�������
    merror(isok, SOCKET_ERROR, "����ʧ��\n");
    
    


    roundfuc();
    int userdecide=0;
    printf("���ٽ��������ͻ���\n");

    for (int i = 1; i <= 1023; i++) {
       
       
        
        clientSocket[i] = accept(server, &claddr, &cllen);  //˭��������
        merror(clientSocket[i], INVALID_SOCKET, "��������ʧ��\n");
        

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func, (LPVOID)(i), NULL, NULL);
  
    }

   

    closesocket(server);
    WSACleanup();

    getchar();    //ͣ�ڽ���
    return 0;
}

void roundfuc() {
    clientSocket[0] = accept(server, &claddr, &cllen);  //˭��������
    merror(clientSocket[0], INVALID_SOCKET, "round����ʧ��\n");

    printf("��������Ҫ���еĲ�������(0<n<10)\n");
    for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
    recv(clientSocket[0], revdate, 1, 0);   //����
    round= revdate[0] - '0';
    

    printf("���Ľ�����%d��\n", round);

    printf("\n*******************************************\n");
    printf("��Ϸ������%d��\n", round);
    printf("���򣺵����ͬʱ̹�׸���8�꣬����̹�׸���1�꣬����̹��һ���ͷţ���̹��һ����10��\n");
    printf("��ע�⣬���˫���������С�ڵ���%d�꣬�����ʤ�����ڵ���%d��ʱ���ʧ��\n", 3 * round, 7 * round);
    printf("*******************************************\n");
}


void func(int index) {
    int users = 0;


    for (int i = 1; i <= round; i++) {

        
        boolean legalA = 0;    //�ж������Ƿ�Ϸ�
        do {
            printf("�����A����ѡ��0��ʾ̹�ף�1��ʾ��̹�ף�\n");
            legalA = 0;
            for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
            recv(clientSocket[index-1], revdate, 1, 0);   //����ѡ��
            answer[0] = revdate[0] - '0';
            if (answer[0] != 0 && answer[0] != 1) {      //�ж������Ƿ�Ϸ�
                legalA = 1;
                printf("�������벻�Ϸ�������������\n");
            }
        } while (legalA == 1);

        
        boolean legalB = 0;    //�ж������Ƿ�Ϸ�
        do {
            printf("�����B����ѡ��0��ʾ̹�ף�1��ʾ��̹�ף�\n");
            legalB = 0;
            for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
            recv(clientSocket[index], revdate, 1, 0);   //����ѡ��
            answer[1] = revdate[0] - '0';
            if (answer[1] != 0 && answer[1] != 1) {      //�ж������Ƿ�Ϸ�
                legalB = 1;
                printf("�������벻�Ϸ�������������\n");
            }
        } while (legalB == 1);
        
          CyberPrisoner(answer[0], answer[1]);
          roundAnswer(answer[0], answer[1]);
        
    finalAnswer();
}


int merror(int redata, int error, const char* showinfo){
    if (redata == error) {               //����ֵ�ж��Ƿ�ʧ�ܣ�redata�Ƿ���ڴ���
        perror(showinfo);         //�������ԭ��
        getchar();
        return -1;
    }
    return 0;

}

void CyberPrisoner(int a, int b) {
    if (a == 0) {
        if (b == 0) {
            sumA += 8;
            sumB += 8;
        }
        else {
            sumB += 10;
        }
    }
    else {
        if (b == 1) {
            sumA += 1;
            sumB += 1;
        }
        else {
            sumA += 10;
        }
    }
}



void finalAnswer() {
    printf("\n*******************************************\n");
    printf("��ϲ������в��ģ��������\n");
    printf("�û�A���е������Ϊ%d\n", sumA);
    printf("�û�B���е������Ϊ%d\n", sumB);
    if (sumA <= 3 * round && sumB <= 3 * round) printf("��ϲ��λ��Ҷ���ʤ\n");
    else  if (sumA >= 7 * round && sumB >= 7 * round) printf("���ź���λ��Ҷ�ʧ����\n");
    else {
        if (sumA > sumB)  printf("��ϲ���B��ʤ\n");
        if (sumA > sumB)  printf("��ϲ���A��ʤ\n");
    }
    printf("*******************************************\n");


}

void roundAnswer(int a, int b) {
    printf("��ϲ��ɱ��β��ģ��������\n");
    printf("�û�A���ֵ�ѡ����%d��Ŀǰ���е������Ϊ%d\n", a, sumA);
    printf("�û�B���ֵ�ѡ����%d��Ŀǰ���е������Ϊ%d\n", b, sumB);
    printf("*******************************************\n");

}

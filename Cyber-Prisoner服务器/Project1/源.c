#include<stdio.h>
#include<WinSock2.h>//网络编程头文件，引入静态库
#pragma comment(lib,"ws2_32.lib")


void CyberPrisoner(int a, int b);  //判刑
int merror(int redata, int error, const char* showinfo);  //检查是否出错
void func(int index);//通信
void finalAnswer();
void roundAnswer(int a,int b);
void roundfuc();


int sumA, sumB;//记录AB玩家的囚禁年份
int answer[2];
int round;//记录游戏轮数
char revdate[1024] = "";
SOCKET server;

struct sockaddr_in claddr; //接受客户端的信息
int cllen = sizeof(claddr);
SOCKET clientSocket[2000];//定义数组以接受多个客户端

int main() {
    printf("欢迎来到Cyber-Prisoner服务端,请链接客户端\n");
    
    WSADATA wsadata;
    int isok = WSAStartup(MAKEWORD(2, 2), &wsadata);//确定socket协议版本
    merror(isok, WSAEINVAL, "申请socket失败");

    //第一个参数：协议族，决定socket的地址类型
    //第二个参数：传输类型，SOCk_STREAN流传输
    //第三个参数：传输协议，tcp
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//af-inet使用ipv4地址，创建socket
    merror(server, INVALID_SOCKET, "创建socket失败");

    //创建服务器协议地址族
    struct sockaddr_in seraddr;//存放
    seraddr.sin_family = AF_INET;    //协议族
    seraddr.sin_port = htons(50000);     //端口,小端数据转换为大端存储
    seraddr.sin_addr.s_addr = INADDR_ANY;  //监听任意地址

    isok = bind(server, &seraddr, sizeof(seraddr));   //绑定socket和协议族
    merror(isok, SOCKET_ERROR, "绑定失败\n");

    isok = listen(server, 100);    //客户端数量
    merror(isok, SOCKET_ERROR, "监听失败\n");
    
    


    roundfuc();
    int userdecide=0;
    printf("请再接入两个客户端\n");

    for (int i = 1; i <= 1023; i++) {
       
       
        
        clientSocket[i] = accept(server, &claddr, &cllen);  //谁连进来了
        merror(clientSocket[i], INVALID_SOCKET, "博弈连接失败\n");
        

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func, (LPVOID)(i), NULL, NULL);
  
    }

   

    closesocket(server);
    WSACleanup();

    getchar();    //停在界面
    return 0;
}

void roundfuc() {
    clientSocket[0] = accept(server, &claddr, &cllen);  //谁连进来了
    merror(clientSocket[0], INVALID_SOCKET, "round连接失败\n");

    printf("请输入需要进行的博弈轮数(0<n<10)\n");
    for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
    recv(clientSocket[0], revdate, 1, 0);   //接收
    round= revdate[0] - '0';
    

    printf("博弈将进行%d轮\n", round);

    printf("\n*******************************************\n");
    printf("游戏将进行%d轮\n", round);
    printf("规则：当玩家同时坦白各判8年，都不坦白各判1年，否则，坦白一方释放，不坦白一方判10年\n");
    printf("请注意，如果双方被判年份小于等于%d年，则均获胜，大于等于%d年时则均失败\n", 3 * round, 7 * round);
    printf("*******************************************\n");
}


void func(int index) {
    int users = 0;


    for (int i = 1; i <= round; i++) {

        
        boolean legalA = 0;    //判断输入是否合法
        do {
            printf("请玩家A做出选择（0表示坦白，1表示不坦白）\n");
            legalA = 0;
            for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
            recv(clientSocket[index-1], revdate, 1, 0);   //接收选择
            answer[0] = revdate[0] - '0';
            if (answer[0] != 0 && answer[0] != 1) {      //判断输入是否合法
                legalA = 1;
                printf("您的输入不合法，请重新输入\n");
            }
        } while (legalA == 1);

        
        boolean legalB = 0;    //判断输入是否合法
        do {
            printf("请玩家B做出选择（0表示坦白，1表示不坦白）\n");
            legalB = 0;
            for (int i = 0; i <= 1023; i++)  revdate[i] = 0xff;
            recv(clientSocket[index], revdate, 1, 0);   //接收选择
            answer[1] = revdate[0] - '0';
            if (answer[1] != 0 && answer[1] != 1) {      //判断输入是否合法
                legalB = 1;
                printf("您的输入不合法，请重新输入\n");
            }
        } while (legalB == 1);
        
          CyberPrisoner(answer[0], answer[1]);
          roundAnswer(answer[0], answer[1]);
        
    finalAnswer();
}


int merror(int redata, int error, const char* showinfo){
    if (redata == error) {               //返回值判断是否失败，redata是否等于错误
        perror(showinfo);         //输出错误原因
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
    printf("恭喜完成所有博弈，结果如下\n");
    printf("用户A被判的总年份为%d\n", sumA);
    printf("用户B被判的总年份为%d\n", sumB);
    if (sumA <= 3 * round && sumB <= 3 * round) printf("恭喜两位玩家都获胜\n");
    else  if (sumA >= 7 * round && sumB >= 7 * round) printf("很遗憾两位玩家都失败了\n");
    else {
        if (sumA > sumB)  printf("恭喜玩家B获胜\n");
        if (sumA > sumB)  printf("恭喜玩家A获胜\n");
    }
    printf("*******************************************\n");


}

void roundAnswer(int a, int b) {
    printf("恭喜完成本次博弈，结果如下\n");
    printf("用户A本轮的选择是%d，目前被判的总年份为%d\n", a, sumA);
    printf("用户B本轮的选择是%d，目前被判的总年份为%d\n", b, sumB);
    printf("*******************************************\n");

}

#include<iostream>
#include<fstream>
#include<WinSock2.h> 
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
 
// dhttp://www.4stud.info/web-programming/ - я буду копировать вот эту страницу

    WSADATA wsaData; 
    WSAStartup(MAKEWORD(2, 2), &wsaData); 

    

    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  

     addrinfo* result = nullptr;
     addrinfo hi; 

    ZeroMemory(&hi, sizeof(hi)); 
    hi.ai_family = AF_UNSPEC; 
    hi.ai_socktype = SOCK_STREAM; 
    hi.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("www.4stud.info", "80", &hi, &result) != 0)
    {   

        cout << "Не могу подключиться к хосту"<< endl; 
        closesocket(ConnectSocket); 
        WSACleanup();
        return 1;
    }

    sockaddr_in* addr = (sockaddr_in*)result->ai_addr;

    connect(ConnectSocket, (sockaddr*)addr, sizeof(*addr));

    const char* request = "GET /web-programming/ HTTP/1.1\r\nHost: www.4stud.info\r\nConnection: close\r\n\r\n";
    send(ConnectSocket, request, strlen(request), 0);

    std::ofstream outputFile("output.txt");
    char buffer[4096] = { 0 };
    int bytesReceived;

    do
    {
        bytesReceived = recv(ConnectSocket, buffer, 4096, 0);
        if (bytesReceived > 0)
        {
            outputFile.write(buffer, bytesReceived);
        }
    } while (bytesReceived > 0);

    outputFile.close();

    closesocket(ConnectSocket);
    WSACleanup();


    cout << "Все символы со страницы http://www.4stud.info/web-programming/  скопированы" << endl;
    cout << "В файл output.txt, который только что создался" << endl;
    cout << "HTML коды тоже присутствуют. Пока не нашёл способа от них избавиться." << endl;
    cout << "С уважением Куликов Д.С." << endl;

    return 0;
}
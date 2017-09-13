/*
* chat_server_win.c
* VidualStudio에서 console프로그램으로 작성시 multithread-DLL로 설정하고
*  소켓라이브러리(ws2_32.lib)를 추가할 것.
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>

#define BUFSIZE 100

DWORD WINAPI ClientConn(void *arg);
void SendMSG(char* message, int len);
void ErrorHandling(char *message);

int clntNumber = 0;
char *whisper;  // 귓속말
char *finalui;
char uiorigin[100];
SOCKET clntSocks[10]; // 10명의 클라이언트까지 받아들이겠다.
int SocketNumber[10]; // 소켓 번호를 저장할 배열
char UserName[10][30]; // 사용자 이름을 저장할 배열
int cnt = 0; // 카운트변수
HANDLE hMutex;

int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET servSock;
	SOCKET clntSock;

	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int clntAddrSize;

	HANDLE hThread;
	DWORD dwThreadID;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == NULL) {
		ErrorHandling("CreateMutex() error");
	}

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1])); /* 9000을 넣는곳. atoi : 9000문자열을 9000이라는 숫자값으로 변환,
											  htons = host to network in short host는 cpu 하나는 intel 다른하나는 motorola */


	if (bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(servSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (1) { // 채팅문자열이 날아올때마다 broadcast
		clntAddrSize = sizeof(clntAddr);
		clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &clntAddrSize); // 새로운 손님이올 때 (그손님만을 위한 소켓을 만들어서 1:1로 매칭) 
		if (clntSock == INVALID_SOCKET)
			ErrorHandling("accept() error");

		WaitForSingleObject(hMutex, INFINITE);  // 크리티컬 섹션
		clntSocks[clntNumber++] = clntSock; // 크리티컬 섹션
		ReleaseMutex(hMutex); // 크리티컬 섹션
		printf("새로운 연결, 클라이언트 IP : %s , 소켓 : %d \n", inet_ntoa(clntAddr.sin_addr), clntSock);

		hThread = (HANDLE)_beginthreadex(NULL, 0, ClientConn, (void*)clntSock, 0, (unsigned *)&dwThreadID);
		if (hThread == 0) {
			ErrorHandling("쓰레드 생성 오류");
		}
	}

	WSACleanup();
	return 0;
}

DWORD WINAPI ClientConn(void *arg)
{
	SOCKET clntSock = (SOCKET)arg;
	int strLen = 0;
	char message[BUFSIZE];
	int i;
	int j = 0;
	while ((strLen = recv(clntSock, message, BUFSIZE, 0)) != 0) { // 접속이 끊김 (빠져나옴)
		strcpy(uiorigin, message);
		finalui = strtok(uiorigin, " \n");
		char *SendUser = finalui;
		finalui = strtok(NULL, " \n");
		if (strcmp(uiorigin, "@@join") == 0) {
			strcpy(UserName[cnt], finalui);
			printf(UserName[cnt]);
			SocketNumber[cnt] = clntSock;
			printf(" 님이 <가입>접속하셨습니다.\n");
			SendMSG(UserName[cnt], sizeof(UserName[cnt]) + 30);
			SendMSG(" 님이 <가입>접속하셨습니다.\n", 30);
			cnt++;
		}
		else { // 일반 메세지
			strcpy(uiorigin, message);
			finalui = strtok(uiorigin, " \n");
			finalui = strtok(NULL, " \n");
			if (!strcmp(finalui, ("&quit")) || !strcmp(finalui, ("@@out"))) { // 탈퇴기능
				int j;
				for (j = 0; j < cnt; j++) {
					if (SocketNumber[j] == clntSock) {
						printf(UserName[j]);
						printf(" 님이 <탈퇴>퇴장하셨습니다.\n");
						SendMSG(UserName[j], sizeof(UserName[j]));
						int k;
						if (j == cnt - 1) // 마지막 사람이 빠지면
							cnt--;
						else { // 마지막 사람이 아닌 경우
							for (k = j; k < cnt; k++) {
								strcpy(UserName[k], UserName[k + 1]);
								SocketNumber[k] = SocketNumber[k + 1];
							}
							cnt--;
						}
					}
				}
				SendMSG(" 님이 <탈퇴>퇴장하셨습니다.\n", 30);
				break;
			}
			else if (!strcmp(finalui, ("@@member")) || !strcmp(finalui, ("&list"))) { // 사용자명단 검색기능
				WaitForSingleObject(hMutex, INFINITE);
				printf("client가 사용자 list를 요청하였습니다.\n");
				strcpy(finalui, "현재 사용자 명단 : ");
				int j;
				for (j = 0; j<cnt; j++) {
					strcat(finalui, UserName[j]); // printf 사용시 ㅁ로 뜨는 등 이상한 오류가 생겨 이어붙이는걸 이용하였다.
					strcat(finalui, "\n		   ");
				}
				strcat(finalui, "\n");
				send(clntSock, finalui, strlen(finalui), 0);
				ReleaseMutex(hMutex);
			}
			else if (!strcmp(finalui, ("@@talk")) || !strcmp(finalui, ("&p2p"))) { // 귓속말기능
				printf("사용자가 귓속말 기능을 사용하였습니다.\n");
				WaitForSingleObject(hMutex, INFINITE);
				finalui = strtok(NULL, " \n"); // 한번더 잘라서 귓속말할 상대방 ID를 추출
				whisper = strtok(NULL, "\n"); // 귓속말 할 내용을 추출
				int j;
				for (j = 0; j < cnt; j++) { // 사용자 리스트에 있는 사람들을 찾는다.
					if (!strncmp(finalui, UserName[j], sizeof(finalui))) { // 귓속말 상대와 등록된 사용자 이름이 일치하면
						send(SocketNumber[j], "비밀글 : <", 30, 0);
						send(SocketNumber[j], SendUser, strlen(SendUser), 0);
						send(SocketNumber[j], "> ", 2, 0);
						send(SocketNumber[j], ": <", 3, 0);
						send(SocketNumber[j], whisper, strlen(whisper), 0);
						send(SocketNumber[j], "> ", 2, 0);
						send(SocketNumber[j], "\n", 1, 0);
					}
					ReleaseMutex(hMutex);
				}

			}
			else
				SendMSG(message, strLen);
		}
	}

	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i<clntNumber; i++) {   // 클라이언트 연결 종료시
		if (clntSock == clntSocks[i]) {
			for (; i<clntNumber - 1; i++)
				clntSocks[i] = clntSocks[i + 1];
			break;
		}
	}
	clntNumber--;
	ReleaseMutex(hMutex);

	closesocket(clntSock);
	return 0;
}

void SendMSG(char* message, int len)
{
	int i;
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i<clntNumber; i++)
		send(clntSocks[i], message, len, 0);
	ReleaseMutex(hMutex);
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

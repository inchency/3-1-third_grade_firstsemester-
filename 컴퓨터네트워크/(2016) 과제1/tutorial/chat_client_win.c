/*
* chat_client_win.c
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
#define NAMESIZE 20

DWORD WINAPI SendMSG(void *arg);
DWORD WINAPI RecvMSG(void *arg);
void ErrorHandling(char *message);

char name[NAMESIZE] = "[Default]";
char message[BUFSIZE];
char userid[100];
char uiorigin[100];
char *finalui;
int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN servAddr;

	HANDLE hThread1, hThread2;
	DWORD dwThreadID1, dwThreadID2;

	if (argc != 3) {
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}
	printf("사용할 ID를 입력하시오\n 형식 : @@join 사용할ID\n"); //처음에 무조건 사용할 ID를 입력하여야만 채팅 가능
	fgets(userid, 100, stdin);
	strcpy(uiorigin, userid);
	finalui = strtok(userid, " \n");
	while (1) {
		if (strcmp(userid, "@@join") == 0) {
			finalui = strtok(NULL, " \n");
			printf("ID 등록 성공 채팅을 시작합니다.\n");
			sprintf(name, "[%s]", finalui);
			break;
		}
		else {
			printf("사용할 ID를 형식에 맞게 다시 입력하세요.\n 형식 : @@join 사용할ID\n");
			fgets(userid, 100, stdin);
			finalui = strtok(userid, " \n");
		}
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
		ErrorHandling("WSAStartup() error!");


	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, SendMSG, (void*)sock, 0, (unsigned *)&dwThreadID1); // 보내는
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, RecvMSG, (void*)sock, 0, (unsigned *)&dwThreadID2); // 받는
	if (hThread1 == 0 || hThread2 == 0) {
		ErrorHandling("쓰레드 생성 오류");
	}

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	closesocket(sock);
	return 0;
}

DWORD WINAPI SendMSG(void *arg) // 메시지 전송 쓰레드 실행 함수
{
	SOCKET sock = (SOCKET)arg;
	char nameMessage[NAMESIZE + BUFSIZE];
	send(sock, uiorigin, sizeof(uiorigin), 0);
	while (1) {
		fgets(message, BUFSIZE, stdin);
		sprintf(nameMessage, "%s %s", name, message);

		send(sock, nameMessage, strlen(nameMessage), 0);
		if (!strcmp(message, ("&quit\n")) || !strcmp(message, ("@@out\n"))) {  // '&quit' or '@@out' 입력시 종료
			printf("로그아웃되었습니다.");
			closesocket(sock);
			exit(1);
		}
	}
}

DWORD WINAPI RecvMSG(void *arg) /* 메시지 수신 쓰레드 실행 함수 */
{
	SOCKET sock = (SOCKET)arg;
	char nameMessage[NAMESIZE + BUFSIZE];
	int strLen;
	while (1) {
		strLen = recv(sock, nameMessage, NAMESIZE + BUFSIZE - 1, 0);
		if (strLen == -1) return 1;

		nameMessage[strLen] = 0;
		fputs(nameMessage, stdout);
	}
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

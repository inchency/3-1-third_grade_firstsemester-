/*
* chat_server_win.c
* VidualStudio���� console���α׷����� �ۼ��� multithread-DLL�� �����ϰ�
*  ���϶��̺귯��(ws2_32.lib)�� �߰��� ��.
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
char *whisper;  // �ӼӸ�
char *finalui;
char uiorigin[100];
SOCKET clntSocks[10]; // 10���� Ŭ���̾�Ʈ���� �޾Ƶ��̰ڴ�.
int SocketNumber[10]; // ���� ��ȣ�� ������ �迭
char UserName[10][30]; // ����� �̸��� ������ �迭
int cnt = 0; // ī��Ʈ����
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
	servAddr.sin_port = htons(atoi(argv[1])); /* 9000�� �ִ°�. atoi : 9000���ڿ��� 9000�̶�� ���ڰ����� ��ȯ,
											  htons = host to network in short host�� cpu �ϳ��� intel �ٸ��ϳ��� motorola */


	if (bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(servSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (1) { // ä�ù��ڿ��� ���ƿö����� broadcast
		clntAddrSize = sizeof(clntAddr);
		clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &clntAddrSize); // ���ο� �մ��̿� �� (�׼մԸ��� ���� ������ ���� 1:1�� ��Ī) 
		if (clntSock == INVALID_SOCKET)
			ErrorHandling("accept() error");

		WaitForSingleObject(hMutex, INFINITE);  // ũ��Ƽ�� ����
		clntSocks[clntNumber++] = clntSock; // ũ��Ƽ�� ����
		ReleaseMutex(hMutex); // ũ��Ƽ�� ����
		printf("���ο� ����, Ŭ���̾�Ʈ IP : %s , ���� : %d \n", inet_ntoa(clntAddr.sin_addr), clntSock);

		hThread = (HANDLE)_beginthreadex(NULL, 0, ClientConn, (void*)clntSock, 0, (unsigned *)&dwThreadID);
		if (hThread == 0) {
			ErrorHandling("������ ���� ����");
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
	while ((strLen = recv(clntSock, message, BUFSIZE, 0)) != 0) { // ������ ���� (��������)
		strcpy(uiorigin, message);
		finalui = strtok(uiorigin, " \n");
		char *SendUser = finalui;
		finalui = strtok(NULL, " \n");
		if (strcmp(uiorigin, "@@join") == 0) {
			strcpy(UserName[cnt], finalui);
			printf(UserName[cnt]);
			SocketNumber[cnt] = clntSock;
			printf(" ���� <����>�����ϼ̽��ϴ�.\n");
			SendMSG(UserName[cnt], sizeof(UserName[cnt]) + 30);
			SendMSG(" ���� <����>�����ϼ̽��ϴ�.\n", 30);
			cnt++;
		}
		else { // �Ϲ� �޼���
			strcpy(uiorigin, message);
			finalui = strtok(uiorigin, " \n");
			finalui = strtok(NULL, " \n");
			if (!strcmp(finalui, ("&quit")) || !strcmp(finalui, ("@@out"))) { // Ż����
				int j;
				for (j = 0; j < cnt; j++) {
					if (SocketNumber[j] == clntSock) {
						printf(UserName[j]);
						printf(" ���� <Ż��>�����ϼ̽��ϴ�.\n");
						SendMSG(UserName[j], sizeof(UserName[j]));
						int k;
						if (j == cnt - 1) // ������ ����� ������
							cnt--;
						else { // ������ ����� �ƴ� ���
							for (k = j; k < cnt; k++) {
								strcpy(UserName[k], UserName[k + 1]);
								SocketNumber[k] = SocketNumber[k + 1];
							}
							cnt--;
						}
					}
				}
				SendMSG(" ���� <Ż��>�����ϼ̽��ϴ�.\n", 30);
				break;
			}
			else if (!strcmp(finalui, ("@@member")) || !strcmp(finalui, ("&list"))) { // ����ڸ�� �˻����
				WaitForSingleObject(hMutex, INFINITE);
				printf("client�� ����� list�� ��û�Ͽ����ϴ�.\n");
				strcpy(finalui, "���� ����� ��� : ");
				int j;
				for (j = 0; j<cnt; j++) {
					strcat(finalui, UserName[j]); // printf ���� ���� �ߴ� �� �̻��� ������ ���� �̾���̴°� �̿��Ͽ���.
					strcat(finalui, "\n		   ");
				}
				strcat(finalui, "\n");
				send(clntSock, finalui, strlen(finalui), 0);
				ReleaseMutex(hMutex);
			}
			else if (!strcmp(finalui, ("@@talk")) || !strcmp(finalui, ("&p2p"))) { // �ӼӸ����
				printf("����ڰ� �ӼӸ� ����� ����Ͽ����ϴ�.\n");
				WaitForSingleObject(hMutex, INFINITE);
				finalui = strtok(NULL, " \n"); // �ѹ��� �߶� �ӼӸ��� ���� ID�� ����
				whisper = strtok(NULL, "\n"); // �ӼӸ� �� ������ ����
				int j;
				for (j = 0; j < cnt; j++) { // ����� ����Ʈ�� �ִ� ������� ã�´�.
					if (!strncmp(finalui, UserName[j], sizeof(finalui))) { // �ӼӸ� ���� ��ϵ� ����� �̸��� ��ġ�ϸ�
						send(SocketNumber[j], "��б� : <", 30, 0);
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
	for (i = 0; i<clntNumber; i++) {   // Ŭ���̾�Ʈ ���� �����
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

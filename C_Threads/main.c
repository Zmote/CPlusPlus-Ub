#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadFunc(LPVOID n){
	printf("Thread entered; initial thread paramter is: %d\n", *(int *)n);
	return *(int *)n;
}

int main(){
	HANDLE hThread;
	DWORD threadId;
	int a = 5;
	DWORD result;
	hThread = CreateThread(NULL, 0, ThreadFunc, &a, 0, &threadId);
	if(hThread) printf("Thread launched %d\n", threadId);
	Sleep(2000);
	GetExitCodeThread(hThread,&result);
	printf("Result is %d\n", result);
	return EXIT_SUCCESS;
}

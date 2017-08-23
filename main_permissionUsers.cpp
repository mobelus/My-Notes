#include <cstring>
#include <iostream>

/*

class Object
{
public:
	char  mas[32];
	char* arr;

	Object()
	{}

	~Object()
	{if(arr) delete arr;}

	void operator=(const Object& _obj)
	{
		//memcpy(this, _obj, sizeof(_obj));

		//this->mas = _obj.mas; // must be a modified lvalue
		memcpy(this->mas, _obj.mas, sizeof(_obj.mas)); // must be a modified lvalue
		if (_obj.arr)
		{ this->arr = _obj.arr;} // ƒва объекта будут указывать на одну и ту же пам€ть
		//когда вызоветс€  delete()  то 
	}

};

*/

#include <windows.h>
#include <stdio.h>

#define THRD_GIVERS_NUM 1 
#define THRD_TAKERS_NUM 4 

HANDLE ghWriteEvent;
HANDLE ghThreadsGivers[THRD_GIVERS_NUM];
HANDLE ghThreadsTakers[THRD_TAKERS_NUM];

DWORD WINAPI funTakePermission(LPVOID);
DWORD WINAPI funGivePermission(LPVOID);

void CreatePermissionEvent()
{
	// Create a manual-reset event object. The write thread sets this
	// object to the signaled state when it finishes writing to a 
	ghWriteEvent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("EventGivePermission")  // object name
	);

	if (ghWriteEvent == NULL)
	{
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}
}

void CreateGiversThreads(void)
{
	// Create multiple threads to read from the buffer.
	DWORD dwThreadID;
	for (int i = 0; i < THRD_GIVERS_NUM; i++)
	{
		ghThreadsGivers[i] = CreateThread(
			NULL,              // default security
			0,                 // default stack size
			funGivePermission,        // name of the thread function
			NULL,              // no thread parameters
			0,                 // default startup flags
			&dwThreadID);

		if (ghThreadsGivers[i] == NULL)
		{
			printf("CreateThread failed (%d)\n", GetLastError());
			return;
		}
	}
}

void CreateTakersThreads(void)
{
	// Create multiple threads to read from the buffer.
	DWORD dwThreadID;
	for (int i = 0; i < THRD_TAKERS_NUM; i++)
	{
		ghThreadsTakers[i] = CreateThread(
			NULL,              // default security
			0,                 // default stack size
			funTakePermission,        // name of the thread function
			NULL,              // no thread parameters
			0,                 // default startup flags
			&dwThreadID);

		if (ghThreadsTakers[i] == NULL)
		{
			printf("CreateThread failed (%d)\n", GetLastError());
			return;
		}
	}
}


void usePermiussion()
{
	printf("Permission was used !!! \n");
	
	for (int i = 0; i < 3; i++)
	{
		Sleep(1000); // 2 seconds we emulate that the fuction does something;
		printf("%d second: Thread %d function is doing stuff...\n",i ,GetCurrentThreadId());
	}
}

DWORD WINAPI funTakePermission(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	while (true)
	{
		DWORD dwWaitResult = WaitForSingleObject(
			ghWriteEvent, // event handle
			INFINITE);    // indefinite wait

		switch (dwWaitResult)
		{
			// Event object was signaled
		case WAIT_OBJECT_0:
			usePermiussion();
			printf("Thread %d reading from buffer\n", GetCurrentThreadId());
			break;

			// An error occurred
		default:
			printf("Wait error (%d)\n", GetLastError());
			return 0;
		}
	}

	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}

DWORD WINAPI funGivePermission(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	while (true)
	{
		// Set ghWriteEvent to signaled
		if (!SetEvent(ghWriteEvent))
		{
			printf("SetEvent failed (%d)\n", GetLastError());
			return 0;
		}

		Sleep(10000); // 10 seconds we set the event and it means we GIVE the permission

	    // ReSet ghWriteEvent to unsignaled
		if (!ResetEvent(ghWriteEvent))
		{
			printf("ResetEvent failed (%d)\n", GetLastError());
			return 0;
		}

		Sleep(5000); // 10 seconds we reset the event and it means  NO  permission
	}

	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}


void CloseEvents()
{
	CloseHandle(ghWriteEvent);
}

int main(void)
{
	DWORD dwWaitResult;

	// TODO: Create the shared buffer
	void CreatePermissionEvent();
	void CreateGiversThreads();
	void CreateTakersThreads();

	// At this point, the reader threads have started and are most
	// likely waiting for the global event to be signaled. However, 
	// it is safe to write to the buffer because the event is a 
	// manual-reset event.

	printf("Main thread waiting for threads to exit...\n");

	// The handle for each thread is signaled when the thread is terminated.
	dwWaitResult = WaitForMultipleObjects(
		THRD_GIVERS_NUM,   // number of handles in array
		ghThreadsGivers,     // array of thread handles
		TRUE,          // wait until all are signaled
		INFINITE);

	switch (dwWaitResult)
	{
		// All thread objects were signaled
	case WAIT_OBJECT_0:
		printf("All threads ended\n");
		break;

		// An error occurred
	default:
		printf("WaitForMultipleObjects failed (%d)\n", GetLastError());
		return 1;
	}

	CloseEvents();

	return 0;
}









































/*
	ћои фейлы:
	1) 
	arr[100];
	ar[100];
	ar = arr; // “ј  Ќ≈Ћ№«я !!
	memcpy(ar, arr);

	2) есть 
	char* a;

	a = b; // Ќ≈Ћ№«я
	и a и b будут казывать на одну и ту же пам€ть.
	и после если будет
	delete a;
	то и b будет невалидным указателем, как и а !!!

*/



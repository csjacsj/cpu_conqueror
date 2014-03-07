#include "stdafx.h"
#include <iostream>
#include "windows.h"

const double SLEEP_INTERVAL = 17*10;
static double Ratio = 0.8;
const int NUM_CPUS = 1;

typedef double Func(double);
typedef void Solve(Func *calc);

inline DWORD get_time()   
{   
	return GetTickCount();
}

void solve_linear(Func*)
{
	const unsigned BUSY = static_cast<const unsigned>(Ratio * SLEEP_INTERVAL);
	const unsigned IDLE = static_cast<const unsigned>((1 - Ratio) * SLEEP_INTERVAL);
	while(true)
	{
		unsigned ta = get_time();
		while(get_time() - ta < BUSY)
		{
		}
		Sleep(IDLE);
	}
}

void run()
{
	HANDLE handle[NUM_CPUS];    
	DWORD thread_id[NUM_CPUS];

	for (int i = 0; i < NUM_CPUS; ++i)
	{
		Func *calc = NULL;
		Solve *solve = solve_linear;
		if ((handle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve, (VOID*)calc, 0, &thread_id[i])) != NULL)
		{
			SetThreadAffinityMask(handle[i], i+1);
		}
	}
	WaitForSingleObject(handle[0],INFINITE);
}



int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	cout<<"input ratio:"<<endl;
	cin>>Ratio;
	run();
	return 0;
}

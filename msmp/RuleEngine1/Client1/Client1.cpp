// Client1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	CoInitialize(0);

	HRESULT hr;
	IMyREClient2Ptr pTest;

	hr = pTest.CreateInstance(__uuidof(MyREClient2));

	if(FAILED(hr))
	{
		::MessageBox(NULL, "Create Instance failed", "Error", MB_OK);
	}
	pTest->Process();

	pTest = NULL;

	CoUninitialize();
	getchar();
	return 0;
}

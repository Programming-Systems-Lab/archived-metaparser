#include "stdio.h"

#define _WIN32_DCOM

#import "Q:\Project\Visual Studio\ComMetaParserTest1\Debug\ComMetaParserTest1.exe"
using namespace COMMETAPARSERTEST1Lib;

int main()
{
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	IMyMetaParserTest1Ptr pTest;
	HRESULT hr;
	hr = pTest.CreateInstance(__uuidof(MyMetaParserTest1));
	if(FAILED(hr))
	{
		printf("CreateInstance failed\n");
	}
	else
	{
		pTest->Init();
		VARIANT_BOOL res = VARIANT_FALSE;
		res = pTest->Parse("Q:\\Project\\xml\\Library.xml");
		pTest->Process();
		if(res == VARIANT_TRUE)
		{
			printf("Parse succeeded!\n");
		}
		else
		{
			printf("Parse failed!\n");
		}
	}
	getchar();
	return 0;
}
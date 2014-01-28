#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <boost/thread.hpp>

int i = 0, j=0 ;
bool experiment_end = 0;

void savingThread()
{
printf("Saving thread started\n");
	/* get handle to dll */ 
   HINSTANCE hGetProcIDDLL = LoadLibraryA("xsens_dll.dll"); 

   /* get pointer to the function in the dll*/ 
   FARPROC lpfnGetProcessID1 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_create"); 
   FARPROC lpfnGetProcessID2 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_doTheMeasurements"); 
   FARPROC lpfnGetProcessID3 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_getData"); 

   /* 
      Define the Function in the DLL for reuse. This is just prototyping the dll's function. 
      A mock of it. Use "stdcall" for maximum compatibility. 
   */ 
   typedef void* (__cdecl * pICFUNC1)(int);
   typedef void (__cdecl * pICFUNC2)(void*);
   typedef void (__cdecl * pICFUNC3)(void*, double* , double* , double* , double* , double*);

   pICFUNC1 connectAtComport; 
   pICFUNC2 doTheMeasurement;
   pICFUNC3 getTheMeasurement;
   connectAtComport = pICFUNC1(lpfnGetProcessID1); 
   doTheMeasurement = pICFUNC2(lpfnGetProcessID2);
   getTheMeasurement = pICFUNC3(lpfnGetProcessID3);

   /* The actual call to the function contained in the dll */ 
   void * xsens = connectAtComport(16);

   double temp;
   double acc[4];
   double quat[4];
   double gyr[4];
   double mag[4];
   
   std::ofstream zap;
   zap.open("Xsense.data");

   printf("Ready to start the experiment\n");
	while(true)
	{
		if ( j >= i )
		{
			if ( experiment_end == 1)
				break;
		}
		else
		{
			getTheMeasurement(xsens,&temp,acc,quat,gyr,mag);
			zap << (j)/ 15<< " | " <<temp << " | " << acc[0] << " " << acc[1] << " " << acc[2] << " | ";
			zap << quat[0] << " "<< quat[1]<< " "<< quat[2] << " "<< quat[3] << " | ";
			zap << gyr[0] << " "<<gyr[1]<< " "<<gyr[2]<< " | ";
			zap << mag[0] << " "<<mag[1]<< " "<<mag[2]<< std::endl;

			j++;
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			printf("Saved %d : %d!\n", (j-1)/ 15, (j-1) % 15);
		}
		doTheMeasurement(xsens);
		//printf("i, j : %d , %d\n", i, j);
	}

	/* Release the Dll */ 
    FreeLibrary(hGetProcIDDLL); 
	zap.close();
}

int main(void)
{
	boost::thread t(savingThread);
	while(1)
	{
		int a;
		std::cin>>a;
		for (int k =0;k<15;k++) i++;
		if (a == 0)
			break;
	}
	experiment_end = true;
	t.join();

	//int a; std::cin>>a;

	return 1;
}

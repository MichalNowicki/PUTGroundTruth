#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ws2tcpip.h>
#include <Windows.h>
#include <boost/thread.hpp>



using namespace cv;
using namespace std;
//using namespace boost;

#define DEFAULT_BUFLEN 512
#define CYCLIC_BUFFER_SIZE 5000

//Mat **dMap;
//Mat **rgbImg;
//Mat **wiezaImg;
int i = 0, j=0 ;
bool experiment_end = 0;
//
//void Dsave(int k)
//{
//	char zapis[40];
//	sprintf(zapis,"depth_%d.bmp", k);
//	imwrite( zapis, *dMap[k%CYCLIC_BUFFER_SIZE]);
//	delete dMap[k%CYCLIC_BUFFER_SIZE];
//}
//
//void RGBsave(int k)
//{
//	char zapis[40];
//	sprintf(zapis,"rgb_%d.bmp", k);
//	imwrite( zapis, *rgbImg[k%CYCLIC_BUFFER_SIZE]);
//	delete rgbImg[k%CYCLIC_BUFFER_SIZE];
//}
//
//void TOWERsave(int k)
//{
//	char zapis[40];
//	sprintf(zapis,"wieza_%d.bmp", k);
//	imwrite( zapis, *wiezaImg[k%CYCLIC_BUFFER_SIZE]);
//	delete wiezaImg[k%CYCLIC_BUFFER_SIZE];
//}

void savingThread()
{
	while(true)
	{
		if ( j >= i )
		{
			if ( experiment_end == 1)
				break;
			Sleep(20);
		}
		else
		{
///			Dsave(j);
//			RGBsave(j);
//			TOWERsave(j);
			j++;
		}
		//printf("i, j : %d , %d\n", i, j);
	}
}

//void TCPconnect(SOCKET &ConnectSocket, WSADATA &wsaData, String &address)
//{
//	// holds address info for socket to connect to
//    struct addrinfo *result = NULL, *ptr = NULL, hints;
//
//    // Initialize Winsock
//    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//
//    if (iResult != 0) {
//        printf("WSAStartup failed with error: %d\n", iResult);
//        exit(-1);
//    }
//
//    // set address info
//    ZeroMemory( &hints, sizeof(hints) );
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!
//
//	// Setting connecting address information
//	iResult = getaddrinfo(address.c_str(), "3000", &hints, &result);
//
//    if( iResult != 0 ) 
//    {
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        exit(-1);
//    }
//
//	// Create a SOCKET for connecting to server
//	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//
//	if (ConnectSocket == INVALID_SOCKET) {
//		printf("socket failed with error: %ld\n", WSAGetLastError());
//		WSACleanup();
//		exit(1);
//	}
//
//	// Connect to server.
//	iResult = connect( ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
//
//	if (iResult == SOCKET_ERROR)
//	{
//		closesocket(ConnectSocket);
//		ConnectSocket = INVALID_SOCKET;
//		printf ("The server is down... did not connect");
//		exit(1);
//	}
//	else
//	{
//		printf("Connected to the server");
//	}
//}

//void kinectInit(VideoCapture &capture)
//{
//	cout << "Device opening ..." << endl;
//    capture.open( CV_CAP_OPENNI );
//
//    if( !capture.isOpened() )
//    {
//        cout << "Can not open a capture object." << endl;
//		exit(-1);
//    }
//	else
//		cout<< "Device opened" <<endl;
//
//  
//    bool modeRes=false;
//	modeRes = capture.set( CV_CAP_OPENNI_IMAGE_GENERATOR_OUTPUT_MODE, CV_CAP_OPENNI_VGA_30HZ );
//  
//    if (!modeRes)
//        cout << "\nThis image mode is not supported by the device, the default value (CV_CAP_OPENNI_SXGA_15HZ) will be used.\n" << endl;
//    
//
//    // Print some available device settings.
//    cout << "\nDepth generator output mode:" << endl <<
//            "FRAME_WIDTH      " << capture.get( CV_CAP_PROP_FRAME_WIDTH ) << endl <<
//            "FRAME_HEIGHT     " << capture.get( CV_CAP_PROP_FRAME_HEIGHT ) << endl <<
//            "FRAME_MAX_DEPTH  " << capture.get( CV_CAP_PROP_OPENNI_FRAME_MAX_DEPTH ) << " mm" << endl <<
//            "FPS              " << capture.get( CV_CAP_PROP_FPS ) << endl <<
//            "REGISTRATION     " << capture.get( CV_CAP_PROP_OPENNI_REGISTRATION ) << endl;
//    if( capture.get( CV_CAP_OPENNI_IMAGE_GENERATOR_PRESENT ) )
//    {
//        cout <<
//            "\nImage generator output mode:" << endl <<
//            "FRAME_WIDTH   " << capture.get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FRAME_WIDTH ) << endl <<
//            "FRAME_HEIGHT  " << capture.get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FRAME_HEIGHT ) << endl <<
//            "FPS           " << capture.get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FPS ) << endl;
//    }
//    else
//    {
//        cout << "\nDevice doesn't contain image generator." << endl;
//    }
//}
//

int main( int argc, char* argv[] )
{
	 /* get handle to dll */ 
   HINSTANCE hGetProcIDDLL = LoadLibrary("D:\\xsens_dll.dll"); 

   /* get pointer to the function in the dll*/ 
   FARPROC lpfnGetProcessID1 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_create"); 
   FARPROC lpfnGetProcessID2 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_doTheMeasurements"); 
   FARPROC lpfnGetProcessID3 = GetProcAddress(HMODULE (hGetProcIDDLL),"XSENS_getAcc"); 

   /* 
      Define the Function in the DLL for reuse. This is just prototyping the dll's function. 
      A mock of it. Use "stdcall" for maximum compatibility. 
   */ 
   typedef void* (__cdecl * pICFUNC1)(int);
   typedef void (__cdecl * pICFUNC2)(void*);
   typedef void (__cdecl * pICFUNC3)(void*, double*);

   pICFUNC1 MyFunction1; 
   pICFUNC2 MyFunction2;
   pICFUNC3 MyFunction3;
   MyFunction1 = pICFUNC1(lpfnGetProcessID1); 
   MyFunction2 = pICFUNC2(lpfnGetProcessID2);
   MyFunction3 = pICFUNC3(lpfnGetProcessID3);

   /* The actual call to the function contained in the dll */ 
   void * xsens = MyFunction1(6);
   while(1)
	{
		COORD coord;
		coord.X = 0;
		coord.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		MyFunction2(xsens);
		double acc[4];
		MyFunction3(xsens, acc);

		cout << acc[0] << endl << acc[1] << endl << acc[2] << endl;
	}

   /* Release the Dll */ 
   FreeLibrary(hGetProcIDDLL); 

   /* The return val from the dll */ 
    return 1;//intMyReturnVal; 
	

	/*

	rgbImg = new Mat *[CYCLIC_BUFFER_SIZE];
	dMap = new Mat *[CYCLIC_BUFFER_SIZE];
	wiezaImg = new Mat *[CYCLIC_BUFFER_SIZE];

	/// Starting TCP connection
	SOCKET ConnectSocket = INVALID_SOCKET;
    WSADATA wsaData;
	String address = "150.254.47.246";

	TCPconnect(ConnectSocket,wsaData,address);


	/// Starting kinect connection
	VideoCapture capture;

	kinectInit(capture);

	VideoCapture wieza(0);
	wieza.set(CV_CAP_PROP_FRAME_WIDTH, 800);
	wieza.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
	if( !wieza.isOpened() )
    {
        cout << "Can not open wieza." << endl;
		exit(-1);
    }
	cout<<"Opened both devices"<<endl;
	
	/// Starting saving thread
//	thread t(savingThread);
    
	// Receiving buffer for TCP/IP communication
	char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

	printf("Ready for action!\n");
	string recvStr = "";
	int iResult = 0;
	
    while(true)
    {
		// Sending READY for transmission
		sprintf(recvbuf,"READY");
		send(ConnectSocket,recvbuf,5,0);

		// Receiving permission to capture data
		// "START %d_" %d=='X' for stop
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		
		recvStr = recvbuf;
		int strPos = recvStr.find('_');
		recvStr = recvStr.substr(6,strPos-6);
		if ( iResult > 0 )
			printf("Received number: %s, expected %d\n",recvStr,i);

		if ( recvStr == "X" )
			break;

		// Creating new MATs
		dMap[i%CYCLIC_BUFFER_SIZE] = new Mat();
		rgbImg[i%CYCLIC_BUFFER_SIZE] = new Mat();
		wiezaImg[i%CYCLIC_BUFFER_SIZE] = new Mat();

        if( !capture.grab() )
        {
            cout << "Can not grab images." << endl;
            return -1;
        }
		
		// Retrieving data for saving
		capture.retrieve( *dMap[i%CYCLIC_BUFFER_SIZE], CV_CAP_OPENNI_DEPTH_MAP );
		capture.retrieve( *rgbImg[i%CYCLIC_BUFFER_SIZE] , CV_CAP_OPENNI_BGR_IMAGE );
		wieza >> *wiezaImg[i%CYCLIC_BUFFER_SIZE] ;

		// Increment buffer position
		i++;
	}

	// Release camera and w8 for save
	experiment_end = true;
	WSACleanup();
	capture.release();
	
//	t.join();
	wieza.release();

    return 0;*/
}


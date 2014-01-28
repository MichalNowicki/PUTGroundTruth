#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <boost/thread.hpp>
#include <fstream>

using namespace cv;
using namespace std;
using namespace boost;

#define DEFAULT_BUFLEN 512
#define CYCLIC_BUFFER_SIZE 5000

Mat **dMap;
Mat **rgbImg;
Mat **cameraImg;
int i = 0, j=0 ;
bool experiment_end = 0;

#define ADDITIONAL_CAMERA

// Saving depth data
//		k -> number of frame
void Dsave(int k)
{
	char zapis[40];
	sprintf(zapis,"depth_%d.png", k);

	imwrite( zapis, *dMap[k%CYCLIC_BUFFER_SIZE]);
	delete dMap[k%CYCLIC_BUFFER_SIZE];
}

// Saving rgb data
//		k -> number of frame
void RGBsave(int k)
{
	char zapis[40];
	sprintf(zapis,"rgb_%d.bmp", k);
	imwrite( zapis, *rgbImg[k%CYCLIC_BUFFER_SIZE]);
	delete rgbImg[k%CYCLIC_BUFFER_SIZE];
}

// Saving data from the CAMERA
//		k -> number of frame
void CAMERAsave(int k)
{
	char zapis[40];
	sprintf(zapis,"camera_%d.bmp", k);
	imwrite( zapis, *cameraImg[k%CYCLIC_BUFFER_SIZE]);
	delete cameraImg[k%CYCLIC_BUFFER_SIZE];
}

// Thread responsible for saving data to files
void savingThread(bool additional_camera)
{
	while(true)
	{
		if ( j >= i )
		{
			if ( experiment_end == 1)
				break;
			Sleep(5);
		}
		else
		{
			Dsave(j);
			RGBsave(j);
			
			if ( additional_camera )
			{
				CAMERAsave(j);
			}
			j++;
		}
		//printf("i, j : %d , %d\n", i, j);
	}
}

// TCP connection init
void TCPconnect(SOCKET &ConnectSocket, WSADATA &wsaData, String &address, String &port)
{
	// holds address info for socket to connect to
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(-1);
    }

    // set address info
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!

	// Setting connecting address information
	iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);

    if( iResult != 0 ) 
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(-1);
    }

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		exit(1);
	}

	// Connect to server.
	iResult = connect( ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		printf ("The server is down... did not connect");
		exit(1);
	}
	else
	{
		printf("Connected to the server");
	}
}

// Initializes Kinect
void kinectInit(VideoCapture &capture)
{
	cout << "Device opening ..." << endl;
    capture.open( CV_CAP_OPENNI );

    if( !capture.isOpened() )
    {
        cout << "Can not open a capture object." << endl;
		exit(-1);
    }
	else
		cout<< "Device opened" <<endl;

  
    bool modeRes=false;
	modeRes = capture.set( CV_CAP_OPENNI_IMAGE_GENERATOR_OUTPUT_MODE, CV_CAP_OPENNI_VGA_30HZ );
  
    if (!modeRes)
        cout << "\nThis image mode is not supported by the device, the default value (CV_CAP_OPENNI_SXGA_15HZ) will be used.\n" << endl;
    

   
    if( !capture.get( CV_CAP_OPENNI_IMAGE_GENERATOR_PRESENT ) )
    {
        cout << "\nDevice doesn't contain image generator." << endl;
    }  
}


void cameraInit(VideoCapture &camera, int number, int width = 640, int height = 480)
{
	camera.open(number);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, height);
	if( !camera.isOpened() )
    {
        cout << "Can not open camera with number : " <<number << endl;
		exit(-1);
    }
	cout<<"Opened camera " << number <<endl;
}


int main( int argc, char* argv[] )
{
	// Creating cyclic buffers
	rgbImg = new Mat *[CYCLIC_BUFFER_SIZE];
	dMap = new Mat *[CYCLIC_BUFFER_SIZE];
	cameraImg = new Mat *[CYCLIC_BUFFER_SIZE];

	// Configuration file
	ifstream odczyt;
	odczyt.open("config.txt");

	String dummy, address;
	// comment + address
	getline(odczyt,dummy); getline(odczyt,address);

	int camera_number;
	// comment + number camery
	getline(odczyt,dummy); odczyt >> camera_number;getline(odczyt,dummy);

	int width, height;
	// comment + camera width + comment + camera height
	getline(odczyt,dummy); odczyt >> width; getline(odczyt,dummy);
	getline(odczyt,dummy); odczyt >> height; getline(odczyt,dummy);

	// Read if we use xSense 
	int xSense;
	getline(odczyt,dummy); odczyt >> xSense; getline(odczyt,dummy);
	odczyt.close();	

	cout<<"Parameters: "<< address<< " "<< camera_number << " "<<width << " "<<height <<" "<<xSense<< endl;

	// TCP connection to program responsible for syncronizing with xSense
	SOCKET ConnectSocket2 = INVALID_SOCKET;
	WSADATA wsaData2;
	String address2 = "127.0.0.1";
	String port2 = "27015";

	if (xSense == 1)
	{
		TCPconnect(ConnectSocket2,wsaData2,address2,port2);
		printf("Connected with xSense\n");
	}
	// TCP connection with computer responsible from data from 
	SOCKET ConnectSocket = INVALID_SOCKET;
	WSADATA wsaData;


	printf("Starting connection to server! \n");
	String port = "3000";
	TCPconnect(ConnectSocket,wsaData,address,port);
	printf("connected!\n");

	// Starting kinect connection
	VideoCapture capture;
	kinectInit(capture);

	VideoCapture camera;
	if (camera_number >= 0)
	{
		cameraInit(camera, camera_number, width, height);
	}
	// Starting saving thread
	thread t(savingThread, camera_number>=0 ? true : false);
    
	// Receiving buffer for TCP/IP communication
	char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

	printf("Ready for action!\n");
	string recvStr = "";
	int iResult = 0;
	
	long long start = GetTickCount();
    while(true)
    {
		// Sending "READY" to server
		sprintf(recvbuf,"READY");
		send(ConnectSocket,recvbuf,5,0);


		// Receiving permission to capture data
		//		"START %d_"  || %d=='X' means stop
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		printf("Received : %sf\n",recvbuf);
			
		// Sending ready to the xSense
		if (xSense == 1)
		{
			send(ConnectSocket2,recvbuf,1,0);
		}

		// Checking if we didn't miss any synchronization packets
		recvStr = recvbuf;
		int strPos = recvStr.find('_');
		recvStr = recvStr.substr(6,strPos-6);
		if ( iResult > 0 )
			printf("Received number: %s, expected %d\n",recvStr,i);

		// We got the stop critiria
		if ( recvStr == "X" )
			break;

		// Creating new MATs
		dMap[i%CYCLIC_BUFFER_SIZE] = new Mat();
		rgbImg[i%CYCLIC_BUFFER_SIZE] = new Mat();
		
		if (camera_number >=0 )
		{
			cameraImg[i%CYCLIC_BUFFER_SIZE] = new Mat();
		}

        if( !capture.grab() )
        {
            cout << "Can not grab images." << endl;
            return -1;
        }
		
		// Retrieving data for saving
		capture.retrieve( *dMap[i%CYCLIC_BUFFER_SIZE], CV_CAP_OPENNI_DEPTH_MAP );
		capture.retrieve( *rgbImg[i%CYCLIC_BUFFER_SIZE] , CV_CAP_OPENNI_BGR_IMAGE );
		
		if (camera_number >= 0)
		{
			camera >> *cameraImg[i%CYCLIC_BUFFER_SIZE] ;
		}

		// Increment buffer position
		i++;

	}

	// Release camera and w8 for save
	experiment_end = true;
	
	closesocket(ConnectSocket);
	//closesocket(ConnectSocket2);
	WSACleanup();
	
	
	// Waiting for thread end
	t.join();

	// Closing
	capture.release();

	if (camera_number >= 0)
	{
		camera.release();
	}
    return 0;
}


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
//#include <boost/thread.hpp>
#include <iostream>

using namespace cv;
using namespace std;
//using namespace boost;

#define DEFAULT_BUFLEN 512

double PCFreq = 0.0;
__int64 CounterStart = 0;

#define KIN
//#define CAM

//void histogram(cv::Mat xxx)
//{
//	int histogram[70000];
//	int roznych = 0;
//
//	memset(histogram,0,70000 * sizeof(int));
//	for (int u=0;u<640;u++)
//	{
//		for (int j=0;j<480;j++)
//		{
//			histogram[ xxx.at<uint16_t>(j,u) ] ++;
//		}
//	}
//
//	for (int u=0;u<70000;u++)
//	{
//		if ( histogram[u] != 0.0 )
//		{
//			roznych++;
//		}
//	}
//	cout<< "Roznych wartosci : " << roznych << endl;
//}


int main()
{

#ifdef KIN
	Mat imgKin, dKin = cv::Mat(480, 640, CV_16SC1);
	//dKin = imread("depth_003.png", -1);
	



	VideoCapture captureKinect;
	captureKinect.open( CV_CAP_OPENNI );
	if (captureKinect.isOpened())
		cout<<"Kinect opened !"<<endl;
	else
		exit(0);

	//VideoCapture camerka(0);
	//camerka.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	//camerka.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	//if( !camerka.isOpened() )
    //{
	//	cout << "Can not open camerka." << endl;
	//	exit(-1);
   // }
	cout<<"Opened both devices"<<endl;

	char a;
	int i = 0;
	char nazwa[30];
	long long tick = GetTickCount();

	while(1)
	{
		
		Mat depthShow;
		Mat camerkaimg;
		Mat tmp;
		while(1)
		{
			if( !captureKinect.grab() ) ;
				captureKinect.retrieve( imgKin, CV_CAP_OPENNI_BGR_IMAGE);
				captureKinect.retrieve( dKin, CV_CAP_OPENNI_DEPTH_MAP );

			//camerka >> camerkaimg;
			const float scaleFactor = 0.05f;
			dKin.convertTo( depthShow, CV_8UC1, scaleFactor );
			imshow("test",depthShow);
			//resize(camerkaimg, tmp, Size(), 0.5, 0.5, 1);
			
			//tmp = dKin *5000;
			//imshow("test",tmp);
			//imshow("test2", tmp);
			char c = waitKey(1);
			if ( c == 'c') break;
		}
		

		// RGB
		//sprintf(nazwa,"img_100_%03d.bmp",i);
		sprintf(nazwa,"rgb_%03d.png",i);
		imwrite(nazwa,imgKin);

		//sprintf(nazwa,"Camerka%d.bmp",i);
		//imwrite(nazwa,camerkaimg);

		// 8 bit
	    sprintf(nazwa,"depth8_%d.png",i);	
		imwrite(nazwa,depthShow);

		// 16 bit tiff
		sprintf(nazwa,"depth16_%d.tiff",i);//, compression_params);
		imwrite(nazwa,dKin);

		// 16 bit png
		sprintf(nazwa,"depth_%03d.png", i);//, compression_params);
		imwrite(nazwa,dKin);

		//sprintf(nazwa,"depth16_%d.tiff",i);//, compression_params);
		//imwrite(nazwa,dKin);

		//Mat xxx = imread(nazwa, -1);

		//histogram(xxx);

		printf("Saved %i!\n",i);
		i++;
	}



	//imwrite("Kinect0.bmp",imgKin);

	//captureKinect.release();
#endif

#ifdef CAM
	Mat img;

	VideoCapture captureCamera;
	captureCamera.open(0);
	if (captureCamera.isOpened())
		cout<<"Camera opened !"<<endl;


	captureCamera.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	captureCamera.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	captureCamera >> img;

	imwrite("Camera0.bmp",img);

	//char a;
	int i = 1;
	char nazwa[30];

	while(1)
	{
		sprintf(nazwa,"Camera%d.bmp",i);

		while(1)
		{
			captureCamera >> img;
			imshow("test",img);
			char c = waitKey(1);
			if ( c == 'c') break;
		}
		imwrite(nazwa,img);
		cout<<"Done"<<endl;
		i++;
	}
#endif
}

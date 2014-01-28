#include <stddef.h>
#include "XsensCMTstatic.h"

using namespace::xsens;

__declspec(dllexport) class CXsens
{
	private:
		Cmt3 cmt3;
		CmtDeviceId deviceIds[1];

		CmtOutputMode mode;
		CmtOutputSettings settings;

		unsigned short sampleFreq;

		Packet* packet;

	public:
		// vars for sample counter & temp.
		unsigned short sdata;
		double tdata;
		//structs to hold data.
		CmtCalData caldata;
		CmtQuat quat_data;
		//CmtEuler euler_data;
		//CmtMatrix matrix_data;
		CmtVector positionLLA;

	public:
		CXsens()
		{
		}
		~CXsens()
		{
		}

		void Init(uint32_t comportNumber)
		{
			// baud rate = 115200
			cmt3.openPort(comportNumber);

			uint16_t mtCount;
			//get the Mt sensor count.
			mtCount = cmt3.getMtCount();
			
			cmt3.getDeviceId(1, deviceIds[0]);

			// set sensor to config sate
			cmt3.gotoConfig();

			mode = CMT_OUTPUTMODE_TEMP | CMT_OUTPUTMODE_CALIB | CMT_OUTPUTMODE_ORIENT;// | CMT_OUTPUTMODE_POSITION;
			settings = CMT_OUTPUTSETTINGS_ORIENTMODE_QUATERNION;
			settings |= CMT_OUTPUTSETTINGS_TIMESTAMP_SAMPLECNT;
			
			sampleFreq = cmt3.getSampleFrequency();

			CmtDeviceMode deviceMode(mode, settings, sampleFreq);
			cmt3.setDeviceMode(deviceMode, true, deviceIds[0]);
			for(unsigned int i = 0; i < mtCount; i++)
			{
				CmtDeviceMode deviceMode(mode, settings, sampleFreq);
				
			}
	
			// start receiving data
			cmt3.gotoMeasurement();

			// Initialize packet for data
			packet = new Packet((unsigned short)mtCount,cmt3.isXm());
		}

		void Deinit()
		{
			delete packet;
			cmt3.closePort();
		}

		void DoTheMeasurements()
		{
			cmt3.waitForDataMessage(packet);

			int mtNumber = 0;

			//get sample count, goto position & display.
			sdata = packet->getSampleCounter();

			// Output Temperature
			if ((mode & CMT_OUTPUTMODE_TEMP) != 0) {						
				tdata = packet->getTemp(mtNumber);
			}

			if ((mode & CMT_OUTPUTMODE_CALIB) != 0) {					
				caldata = packet->getCalData(mtNumber);
			}

			// Output: Quaternions
			if ((mode & CMT_OUTPUTMODE_ORIENT) != 0) {
				quat_data = packet->getOriQuat(mtNumber);	
			}

			// Output: Position
			if ((mode & CMT_OUTPUTMODE_POSITION) != 0) {
				positionLLA = packet->getPositionLLA();
			}
		}
};

extern "C" __declspec(dllexport) CXsens* XSENS_create(int portNumber)
{
	CXsens* pXsens = new CXsens();
	pXsens->Init((uint32_t)portNumber);
	return pXsens;
}

extern "C" __declspec(dllexport) void XSENS_doTheMeasurements(CXsens* pObject)
{
	pObject->DoTheMeasurements();
}

extern "C" __declspec(dllexport) void XSENS_getQuat(CXsens* pObject, double* quat)
{
	for(int i=0; i<4; ++i)
	{
		quat[i] = pObject->quat_data.m_data[i];
	}
}

extern "C" __declspec(dllexport) void XSENS_getAcc(CXsens* pObject, double* acc)
{
	for(int i=0; i<3; ++i)
	{
		acc[i] = pObject->caldata.m_acc.m_data[i];
	}
}

extern "C" __declspec(dllexport) void XSENS_getData(CXsens* pObject, double* temp, double* acc, double* quat, double *gyr, double *mag)
{
	temp[0] = pObject->tdata;
	for(int i=0; i<3; ++i)
	{
		acc[i] = pObject->caldata.m_acc.m_data[i];
	}
	for(int i=0; i<4; ++i)
	{
		quat[i] = pObject->quat_data.m_data[i];
	}
	for(int i=0; i<3; ++i)
	{
		gyr[i] = pObject->caldata.m_gyr.m_data[i];
	}
	for(int i=0; i<3; ++i)
	{
		mag[i] = pObject->caldata.m_mag.m_data[i];
	}
}

extern "C" __declspec(dllexport) void XSENS_dispose(CXsens* pObject)
{
	pObject->Deinit();
	if(pObject != NULL)
    {
        delete pObject;
        pObject = NULL;
    }
}
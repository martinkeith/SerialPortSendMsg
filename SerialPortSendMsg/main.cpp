////include <windows.h>
////include <iostream>
////#include <string>
////HANDLE hSerial = nullptr;
////HANDLE OpenSerialPort(std::string &strPort, ULONG ulBaudrate)
////{
////
////	LPCWSTR lptmp = stringToLPCWSTR(strPort);
////	HANDLE hSerial;
////	hSerial = CreateFile(lptmp,
////		GENERIC_READ | GENERIC_WRITE,
////		NULL,
////		NULL,
////		OPEN_EXISTING,
////		NULL,
////		NULL);
////
////	if (hSerial == INVALID_HANDLE_VALUE)//Open serial port failed.
////	{
////		return hSerial;
////	}
////
////	//Config serial port
////	DCB PortDCB;
////	PortDCB.DCBlength = sizeof(DCB);
////
////	// Get the default serial parameter.
////	GetCommState(hSerial, &PortDCB);
////	PortDCB.BaudRate = ulBaudrate;      // baudrate
////	PortDCB.ByteSize = 8;               // Number of bits/byte, 4-8 
////	PortDCB.Parity = NOPARITY;
////	PortDCB.StopBits = ONESTOPBIT;
////
////	if (!SetCommState(hSerial, &PortDCB))
////	{
////		//config the serial port failed.
////		CloseHandle(hSerial);
////		return (INVALID_HANDLE_VALUE);
////	}
////
////	//Config the serial port timeout property.
////	COMMTIMEOUTS CommTimeouts;
////	GetCommTimeouts(hSerial, &CommTimeouts);        //Get the serial port default timeout.
////	CommTimeouts.ReadIntervalTimeout = MAXDWORD;
////	CommTimeouts.ReadTotalTimeoutMultiplier = 10;
////	CommTimeouts.ReadTotalTimeoutConstant = 10;
////	CommTimeouts.WriteTotalTimeoutMultiplier = 50;
////	CommTimeouts.WriteTotalTimeoutConstant = 100;
////
////	if (!SetCommTimeouts(hSerial, &CommTimeouts))
////	{
////		//config the serial port timeout failed;
////		CloseHandle(hSerial);
////		return (INVALID_HANDLE_VALUE);
////	}
////	return (hSerial);
////};
////
////void CloseSerialPort(HANDLE hSerial)
////{
////	CloseHandle(hSerial);
////};
////
////bool WriteSerial(char* btData, ULONG ulSize, HANDLE hSerial)
////{
////	DWORD dwNumBytes, dwRet;
////	dwRet = WriteFile(hSerial, //Handle
////		btData, //Data buffer
////		ulSize, //Buffer size
////		&dwNumBytes, //written bytes
////		NULL); //don't support
////
////	return (dwRet != 0);
////};
////
////bool ReadSerial(BYTE *btData, ULONG *ulSize, HANDLE hSerial)
////{
////	//SetCommMask (hSerial, EV_RXCHAR);
////	ULONG ulRdSize = 0;
////	BYTE Byte;
////	DWORD dwBytes;
////	bool blRd = false;
////	DWORD dwMask = EV_RXCHAR;
////	//WaitCommEvent(hSerial,&dwMask,NULL);
////	SetCommMask(hSerial, EV_RXCHAR);
////	while (ReadFile(hSerial, &Byte, 1, &dwBytes, 0) != 0)
////	{
////		if (dwBytes > 0)
////		{
////			btData[ulRdSize++] = Byte;
////
////			if (ulRdSize == *ulSize)
////			{
////				blRd = true;
////				break;
////			}
////		}
////
////		else
////		{
////			blRd = true;
////			break;
////		}
////	}
////
////	*ulSize = ulRdSize;
////	return (blRd);
////};
/////////////////////IR CUT///////////////////////////////
////
////int main()
////{
////	// TODO: 在此添加控件通知处理程序代码
////
////
////	
////	
////
////
////	std::string portname = "3";
////	char data[5] = { 0xaa,0xaa,0x00,0x01,0x55 };
////
////
////
////	hSerialPort = OpenSerialPort(portname, 76800);//Open serial port com1
////
////	if (hSerialPort != INVALID_HANDLE_VALUE)
////	{
////		if (!WriteSerial(data, 5, hSerialPort))//Send data hello to com1
////		{
////			MessageBox(_T("WriteSerial Error!"));
////		}
////		CloseSerialPort(hSerialPort);//串口发送完后要关闭
////	}
////
////}
//
//
#include<iostream>
//#include<windows.h>
#include <afx.h>
HANDLE hEvent;

using namespace std;
LPCWSTR stringToLPCWSTR(std::string orig)
{
	wchar_t *wcstring = 0;
	try
	{
		size_t origsize = orig.length() + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		if (orig == "")
		{
			wcstring = (wchar_t *)malloc(0);
			mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
		}
		else
		{
			wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
			mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
		}
	}
	catch (std::exception e)
	{

	}return wcstring;
}
HANDLE OpenSerialPort(std::string &strPort, ULONG ulBaudrate)
{

	LPCSTR lptmp = strPort.c_str();
	HANDLE hSerial;



	hSerial = CreateFileA(lptmp,
		GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);

	if (hSerial == INVALID_HANDLE_VALUE)//Open serial port failed.
	{
		return hSerial;
	}

	//Config serial port
	DCB PortDCB;
	PortDCB.DCBlength = sizeof(DCB);

	// Get the default serial parameter.
	GetCommState(hSerial, &PortDCB);
	PortDCB.BaudRate = ulBaudrate;      // baudrate
	PortDCB.ByteSize = 8;               // Number of bits/byte, 4-8 
	PortDCB.Parity = NOPARITY;
	PortDCB.StopBits = 1;

	if (!SetCommState(hSerial, &PortDCB))
	{
		//config the serial port failed.
		//CloseHandle(hSerial);
		//return (INVALID_HANDLE_VALUE);
	}

	//Config the serial port timeout property.
	COMMTIMEOUTS CommTimeouts;
	GetCommTimeouts(hSerial, &CommTimeouts);        //Get the serial port default timeout.
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;
	CommTimeouts.ReadTotalTimeoutMultiplier = 10;
	CommTimeouts.ReadTotalTimeoutConstant = 10;
	CommTimeouts.WriteTotalTimeoutMultiplier = 50;
	CommTimeouts.WriteTotalTimeoutConstant = 100;

	if (!SetCommTimeouts(hSerial, &CommTimeouts))
	{
		//config the serial port timeout failed;
		CloseHandle(hSerial);
		return (INVALID_HANDLE_VALUE);
	}
	return (hSerial);
}
bool WriteSerial(char* btData, ULONG ulSize, HANDLE hSerial)
{
	WaitForSingleObject(hEvent, INFINITE);
	DWORD dwNumBytes, dwRet;
	dwRet = WriteFile(hSerial, //Handle
		btData, //Data buffer
		ulSize, //Buffer size
		&dwNumBytes, //written bytes
		NULL); //don't support
	SetEvent(hEvent);
	Sleep(10);
	return (dwRet != 0);
}
bool ReadSerial(BYTE *btData, ULONG *ulSize, HANDLE hSerial)
{
	//SetCommMask (hSerial, EV_RXCHAR);
	ULONG ulRdSize = 0;
	BYTE Byte;
	DWORD dwBytes;
	bool blRd = false;
	DWORD dwMask = EV_RXCHAR;
	//WaitCommEvent(hSerial,&dwMask,NULL);
	WaitForSingleObject(hEvent, INFINITE);
	SetCommMask(hSerial, EV_RXCHAR);
	while (ReadFile(hSerial, &Byte, 1, &dwBytes, 0) != 0)
	{
		if (dwBytes > 0)
		{
			btData[ulRdSize++] = Byte;

			//if (ulRdSize == *ulSize)
			//{
			//	blRd = true;
			//	break;
			//}
		}

		else
		{
			blRd = true;
			break;
		}
	}
	SetEvent(hEvent);
	Sleep(10);
	*ulSize = ulRdSize;
	return (blRd);
}
void CloseSerialPort(HANDLE hSerial)
{
	CloseHandle(hSerial);
};

//DWORD WINAPI ThreadWriteSerial(LPVOID lpParam)
//{
//	DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);
//	DWORD dwNumBytes, dwRet;
//	dwRet = WriteFile(hSerial, //Handle
//		btData, //Data buffer
//		ulSize, //Buffer size
//		&dwNumBytes, //written bytes
//		NULL); //don't support
//	SetEvent(hEvent);
//	Sleep(10);
//	return (dwRet != 0);
//}
//DWORD WINAPI ThreadReadSerial(LPVOID lpParam)
//{
//	ULONG ulRdSize = 0;
//	BYTE Byte;
//	DWORD dwBytes;
//	bool blRd = false;
//	DWORD dwMask = EV_RXCHAR;
//	//WaitCommEvent(hSerial,&dwMask,NULL);
//	DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);
//	SetCommMask(hSerial, EV_RXCHAR);
//	while (ReadFile(hSerial, &Byte, 1, &dwBytes, 0) != 0)
//	{
//		if (dwBytes > 0)
//		{
//			btData[ulRdSize++] = Byte;
//
//			if (ulRdSize == *ulSize)
//			{
//				blRd = true;
//				break;
//			}
//		}
//
//		else
//		{
//			blRd = true;
//			break;
//		}
//	}
//	SetEvent(hEvent);
//	Sleep(10);
//	*ulSize = ulRdSize;
//	return (blRd);
//}
int main()
{

	CString	m_strSMSTel = "18745783176";
	CString	m_strSMSCon = "火警测试改";
	CString strtmp = "//上海迅赛信息技术有限公司,网址www.xunsai.com//";
	HINSTANCE hinstDLL = nullptr;
	typedef int(_stdcall *Sms_Connection)(CString CopyRight, int Com_Port, int Com_BaudRate, CString *Mobile_Type);
	Sms_Connection Proc;
	Proc = (Sms_Connection)GetProcAddress(hinstDLL, "Sms_Connection");
	CString tmp[256];
	int iValue = Proc(strtmp, 3, 115200, tmp);
	if (iValue == 1)
	{
		printf("短信猫连接成功!(短信猫型号为:%s)\n", *tmp);
		//AfxMessageBox(strText);
	}
	else if (iValue == 0) {
		printf("failed\n");
		//AfxMessageBox("短信猫连接失败!(请重新连接短信猫)");
	}
	typedef int(_stdcall *Sms_Send)(CString Sms_TelNum, CString Sms_Text);
	Sms_Send Proc2;
	Proc2 = (Sms_Send)GetProcAddress(hinstDLL, "Sms_Send");
	int iValue2 = Proc2(m_strSMSTel, m_strSMSCon);
	if (iValue2 == 1)
	{
		printf("send success\n");
		
	}
	else {
		printf("send faild\n");
	}


		//HANDLE hSerialPort = nullptr;

		//hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		//std::string portname = "COM3";
		////char data[5] = { 0x41,0x54,0x0D };
		//char data[] = { 0x41,0x54,0x2B,0x43,0x4D,0x47,0x46,0x3D,0x31,"\n" };//10
		//char data2[] = { 0x41,0x54,0x2B,0x43,0x53,0x4D,0x50,0x3D,0x31,0x37,0x2C,0x31,0x36,0x37,0x2C,0x32,0x2C,0x32,0x35,"\n" };//20
		//char data3[] = { 0x41,0x54,0x2B,0x43,0x53,0x43,0x53,0x3D,0x22,0x55,0x43,0x53,0x32,0x22,"\n" };//15
		//char data4[] = { 0x41,0x54,0x2B,0x43,0x4D,0x47,0x53,0x3D,0x22,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x34,0x30,0x30,0x33,0x35,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x33,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x36,0x22,"\n" };
		////55
		//char data42[] = {0x41,0x54,0x2B,0x43,0x4D,0x47,0x53,0x3D,0x22,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x34,0x30,0x30,0x33,0x35,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x33,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x36,0x22,"\n" };
		//char data5[] = { 0x37,0x30,0x36,0x42,0x36,0x30,0x43,0x35,0x38,0x42,0x36,0x36,0x35,0x34,0x34,0x41 };//16
		//
		//char data6[] = { 0x1A };//1
		//BYTE btData[100];
		//memset(btData,0,sizeof(btData));
		//ULONG uLongSize;
		//hSerialPort = OpenSerialPort(portname, 115200);//Open serial port com1

		////if (hSerialPort == INVALID_HANDLE_VALUE)
		////{
		////	return -1;
		////}
		////else
		////{
		////	HANDLE hThread1 = CreateThread(NULL, 0, ThreadWriteSerial, NULL, 0, NULL);
		////	HANDLE hTreahd2 = CreateThread(NULL, 0, ThreadReadSerial, NULL, 0, NULL);
		////}
		//if (hSerialPort != INVALID_HANDLE_VALUE)
		//{
		//	SetEvent(hEvent);
		//	if (!WriteSerial(data, 10, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	if (!WriteSerial(data2, 20, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	if (!WriteSerial(data3, 15, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	if (!WriteSerial(data4, 55, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	if (!WriteSerial(data5, 16, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	
		//	if (!WriteSerial(data6, 1, hSerialPort))//Send data hello to com1
		//	{
		//		printf("WriteSerial Error!");
		//	}
		//	else
		//	{
		//		memset(btData, 0, sizeof(btData));
		//		ReadSerial(btData, &uLongSize, hSerialPort);
		//	}
		//	Sleep(5000);
		//	CloseSerialPort(hSerialPort);//串口发送完后要关闭
		//}


		//CloseSerialPort(hSerialPort);


	//HANDLE hcom;
	//hcom = CreateFile("COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
	//	, FILE_ATTRIBUTE_NORMAL, NULL);
	//if (hcom == INVALID_HANDLE_VALUE)
	//{

	//	fprintf(stderr, "打开串口失败！\n");
	//	exit(0);
	//}
	//SetupComm(hcom, 1024, 1024);
	//DCB dcb;
	//GetCommState(hcom, &dcb);
	//dcb.BaudRate = 9600;
	//dcb.ByteSize = 8;
	//dcb.Parity = 0;
	//dcb.StopBits = 1;
	//SetCommState(hcom, &dcb);
	//DWORD dwWrittenLen = 0;
	//char data[] = { 0x41,0x54,0x2B,0x43,0x4D,0x47,0x46,0x3D,0x31,0x0D};
	//


	//if (!WriteFile(hcom, data,10, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}

	//Sleep(100);


	//char data2[] = {0x41,0x54,0x2B,0x43,0x53,0x4D,0x50,0x3D,0x31,0x37,0x2C,0x31,0x36,0x37,0x2C,0x32,0x2C,0x32,0x35,0x0D};



	//if (!WriteFile(hcom, data2,20, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}
	//Sleep(100);

	//char data3[] = { 0x41,0x54,0x2B,0x43,0x53,0x43,0x53,0x3D,0x22,0x55,0x43,0x53,0x32,0x22,0x0D };



	//if (!WriteFile(hcom, data3,15, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}
	//Sleep(100);

	//char data4[] = {0x41,0x54,0x2B,0x43,0x4D,0x47,0x53,0x3D,0x22,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x34,0x30,0x30,0x33,0x35,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x33,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x36,0x0D};



	//if (!WriteFile(hcom, data4,54, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}
	//Sleep(100);

	//char data5[] = {0x37,0x30,0x36,0x42,0x36,0x30,0x43,0x35,0x38,0x42,0x36,0x36,0x35,0x34,0x34,0x41};



	//if (!WriteFile(hcom, data5, 16, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}
	//Sleep(100);
	//char data6[] = {0x1A};



	//if (!WriteFile(hcom, data6, 1, &dwWrittenLen, NULL))
	//{
	//	fprintf(stderr, "发送数据失败！\n");
	//}
	//Sleep(100);
	//CloseSerialPort(hcom);





	return 0;
}





//#include "SerialPort.h"  
//using namespace std;
//int main()
//{
//	CSerialPort mySerialPort;//首先将之前定义的类实例化
//	int length = 8;//定义传输的长度
//
//
//	unsigned char *temp = new unsigned char[3];//动态创建一个数组
//
//
//
//
//	if (!mySerialPort.InitPort(7, CBR_19200, 'N', 8, 1, EV_RXCHAR))//是否打开串口，3就是你外设连接电脑的com口，可以在设备管理器查看，然后更改这个参数
//	{
//		std::cout << "initPort fail !" << std::endl;
//	}
//	else
//	{
//		std::cout << "initPort success !" << std::endl;
//	}
//	if (!mySerialPort.OpenListenThread())//是否打开监听线程，开启线程用来传输返回值
//	{
//		std::cout << "OpenListenThread fail !" << std::endl;
//	}
//	else
//	{
//		std::cout << "OpenListenThread success !" << std::endl;
//	}
//
//
//	temp[0] = 0x41;
//	temp[1] = 0x54;
//	temp[2] = 0x0D;
//	unsigned char data[] = { 0x41,0x54,0x2B,0x43,0x4D,0x47,0x46,0x3D,0x31,0x0D };
//	unsigned char data2[] = { 0x41,0x54,0x2B,0x43,0x53,0x4D,0x50,0x3D,0x31,0x37,0x2C,0x31,0x36,0x37,0x2C,0x32,0x2C,0x32,0x35,0x0D };
//	unsigned char data3[] = { 0x41,0x54,0x2B,0x43,0x53,0x43,0x53,0x3D,0x22,0x55,0x43,0x53,0x32,0x22,0x0D };
//	unsigned char data4[] = { 0x41,0x54,0x2B,0x43,0x4D,0x47,0x53,0x3D,0x22,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x34,0x30,0x30,0x33,0x35,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x38,0x30,0x30,0x33,0x33,0x30,0x30,0x33,0x31,0x30,0x30,0x33,0x37,0x30,0x30,0x33,0x36,0x0D };
//	
//	unsigned char data5[] = { 0x37,0x30,0x36,0x42,0x36,0x30,0x43,0x35,0x38,0x42,0x36,0x36,0x35,0x34,0x34,0x41 };
//
//	unsigned char data6[] = { 0x1A };
//	cout << "Data send:"<<mySerialPort.WriteData(data, 10) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:"<<mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//
//	cout << "Data2 send:" << mySerialPort.WriteData(data2, 20) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:" << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//
//	cout << "Data3 send:" << mySerialPort.WriteData(data3, 15) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:" << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//
//	cout << "Data4 send:" << mySerialPort.WriteData(data4, 54) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:" << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//
//	cout << "Data5 send:" << mySerialPort.WriteData(data5, 16) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:" << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//
//
//	cout << "Data6 send:" << mySerialPort.WriteData(data6, 1) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
//	cout << "Data receive:" << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
//	delete []temp;
//
//	return 0;
//}
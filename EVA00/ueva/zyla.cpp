/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEVA

uEVA is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

uEVA is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with uEva. If not, see <http://www.gnu.org/licenses/>
*/

#include "zyla.h"

ZylaSettings::ZylaSettings()
{
	boolMap[L"Overlap"] = false; // link framerate to exposure
	boolMap[L"StaticBlemishCorrection"] = true; // FPGA noisy pixels
	boolMap[L"FastAOIFrameRateEnable"] = true; // increase fps for small AOI
	boolMap[L"FullAOIControl"] = true; // arbitrary selection
	//boolMap[L"AlternatingReadoutDirection"] = true; // sensor direction
	//boolMap[L"RollingShutterGlobalClear"] = false; // faster clear
	//boolMap[L"ScanSpeedControlEnable"] = false; // allow change line row scan
	boolMap[L"SensorCooling"] = true;
	boolMap[L"MetadataEnable"] = false;
	boolMap[L"MetadataTimestamp"] = false;
	boolMap[L"MetadataFrameinfo"] = false;

	intMap[L"FrameCount"] = 1; // number of images to acquire in each sequence
	intMap[L"Accumulatecount"] = 1; // number of images to sum as one
	//intMap[L"AOILeft"] = 1; // units in sensor pixel
	//intMap[L"AOITop"] = 1; // units in sensor pixel
	//intMap[L"AOIWidth"] = 1; // units in super pixel
	//intMap[L"AOIHeight"] = 1; // units in super pixels
	//intMap[L"AOIStride"] = 1; // row size in bytes
	//intMap[L"AOIHBin"] = 4; // horizontal binning
	//intMap[L"AOIVBin"] = 4; // vertical binning
	intMap[L"ImageSizeBytes"] = 0;
	intMap[L"TimeStampClock"] = 0;
	intMap[L"TimeStampClockFrequency"] = 0;

	floatMap[L"ExposureTime"] = 0.004; // seconds
	floatMap[L"FrameRate"] = 40; // Hz
	floatMap[L"ReadoutTime"] = 0;
	floatMap[L"RowReadTime"] = 0;
	floatMap[L"LineScanSpeed"] = 0;
	floatMap[L"TargetSensorTemperature"] = 0;
	floatMap[L"SensorTemperature"] = 0;

	enumMap[L"TriggerMode"] = L"Internal"; // trigger shutter
	enumMap[L"CycleMode"] = L"Continuous"; // fix or continuous sequence
	enumMap[L"ElectronicShutteringMode"] = L"Rolling"; // rolling or global
	enumMap[L"PixelReadoutRate"] = L"280 MHz"; // 100MHz
	enumMap[L"TemperatureStatus"] = L"Stabilized";
	enumMap[L"AOIBinning"] = L"2x2"; // binning, intensity vs resolution
	//enumMap[L"AOILayout"] = L"Image"; // Kinetics, TDI, Multitrack
	//enumMap[L"SensorReadoutMode"] = L"Bottom Up Sequential";
	enumMap[L"SimplePreAmpGainControl"] = L"16-bit (low noise & high well capacity)";
	enumMap[L"PixelEncoding"] = L"Mono16"; // Mono12 Mono16 Mono32
	enumMap[L"BitDepth"] = L"16 Bit";

	collapse();
}

ZylaSettings::~ZylaSettings()
{

}

void ZylaSettings::print()
{
	for (boolMapIterator = boolMap.begin();
		boolMapIterator != boolMap.end();
		boolMapIterator++)
	{
		std::wcout << boolMapIterator->first << " = " <<
			boolMapIterator->second << std::endl;
	}
	std::cout << std::endl;
	for (intMapIterator = intMap.begin();
		intMapIterator != intMap.end();
		intMapIterator++)
	{
		std::wcout << intMapIterator->first << " = " <<
			intMapIterator->second << std::endl;
	}
	std::cout << std::endl;
	for (floatMapIterator = floatMap.begin();
		floatMapIterator != floatMap.end();
		floatMapIterator++)
	{
		std::wcout << floatMapIterator->first << " = " <<
			floatMapIterator->second << std::endl;
	}
	std::cout << std::endl;
	for (enumMapIterator = enumMap.begin();
		enumMapIterator != enumMap.end();
		enumMapIterator++)
	{
		std::wcout << enumMapIterator->first << " = " <<
			enumMapIterator->second << std::endl;
	}
	std::cout << std::endl;
}

void ZylaSettings::collapse()
{
	allMap.clear();

	for (boolMapIterator = boolMap.begin();
		boolMapIterator != boolMap.end();
		boolMapIterator++)
	{
		allMap[QString::fromWCharArray(boolMapIterator->first)] =
			QString::number(boolMapIterator->second);
	}

	for (intMapIterator = intMap.begin();
		intMapIterator != intMap.end();
		intMapIterator++)
	{
		allMap[QString::fromWCharArray(intMapIterator->first)] =
			QString::number(intMapIterator->second);
	}

	for (floatMapIterator = floatMap.begin();
		floatMapIterator != floatMap.end();
		floatMapIterator++)
	{
		allMap[QString::fromWCharArray(floatMapIterator->first)] =
			QString::number(floatMapIterator->second);
	}

	for (enumMapIterator = enumMap.begin();
		enumMapIterator != enumMap.end();
		enumMapIterator++)
	{
		allMap[QString::fromWCharArray(enumMapIterator->first)] =
			QString::fromWCharArray(enumMapIterator->second);
	}
}

void ZylaSettings::expand()
{
	QMapIterator<QString, QString> m(allMap);

	for (boolMapIterator = boolMap.begin();
		boolMapIterator != boolMap.end();
		boolMapIterator++)
	{
		m.toFront();
		while (m.hasNext())
		{
			m.next();
			if (m.key() == QString::fromWCharArray(boolMapIterator->first))
			{
				boolMapIterator->second = m.value().toInt();
			}
		}
	}

	for (intMapIterator = intMap.begin();
		intMapIterator != intMap.end();
		intMapIterator++)
	{
		m.toFront();
		while (m.hasNext())
		{
			m.next();
			if (m.key() == QString::fromWCharArray(intMapIterator->first))
			{
				intMapIterator->second = m.value().toInt();
			}
		}
	}

	for (floatMapIterator = floatMap.begin();
		floatMapIterator != floatMap.end();
		floatMapIterator++)
	{
		m.toFront();
		while (m.hasNext())
		{
			m.next();
			if (m.key() == QString::fromWCharArray(floatMapIterator->first))
			{
				floatMapIterator->second = m.value().toDouble();
			}
		}
	}

	for (enumMapIterator = enumMap.begin();
		enumMapIterator != enumMap.end();
		enumMapIterator++)
	{
		m.toFront();
		while (m.hasNext())
		{
			m.next();
			if (m.key() == QString::fromWCharArray(enumMapIterator->first))
			{
				//delete enumMapIterator->second; // small leak
				AT_WC *str = new AT_WC[256];
				int strLength = m.value().toWCharArray(str);
				str[strLength] = '\0';
				enumMapIterator->second = str;
			}
		}
	}
}






Zyla::Zyla(int i) : cameraIndex(i)
{
	//// libraries
	returnCode = AT_InitialiseLibrary();
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not initialise library, return " <<
			returnCode << std::endl;
		return;
	}
	else
	{
		std::cout << "zyla initialized library" << std::endl;
	}
	returnCode = AT_InitialiseUtilityLibrary();
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not initialise utility library, return " <<
			returnCode << std::endl;
		return;
	}
	else
	{
		std::cout << "zyla initialized utility library" << std::endl;
	}
	//// handle
	returnCode = AT_Open(cameraIndex, &handle);
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not open, return " <<
			returnCode << std::endl;
		return;
	}
	else
	{
		std::cout << "zyla opened with handle " << handle << std::endl;
	}
	std::cout << std::endl;
}

Zyla::~Zyla()
{
	//// handle
	returnCode = AT_Close(handle);
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not close, return " <<
			returnCode << std::endl;
	}
	else
	{
		std::cout << "zyla closed" << std::endl;
	}
	//// library
	returnCode = AT_FinaliseLibrary();
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not finalise library, return " <<
			returnCode << std::endl;
	}
	else
	{
		std::cout << "zyla finalized library" << std::endl;
	}
	std::cout << std::endl;
	//// utility library
	returnCode = AT_FinaliseUtilityLibrary();
	if (returnCode != AT_SUCCESS)
	{
		std::cout << "FAIL: zyla can not finalise utility library, return " <<
			returnCode << std::endl;
	}
	else
	{
		std::cout << "zyla finalized utility library" << std::endl;
	}
	std::cout << std::endl;
}

void Zyla::get(ZylaSettings &s)
{
	//// bool
	for (s.boolMapIterator = s.boolMap.begin();
		s.boolMapIterator != s.boolMap.end();
		s.boolMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.boolMapIterator->first, 
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.boolMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.boolMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.boolMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not get " << s.boolMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.boolMapIterator->first;
			if (readable)
			{
				AT_BOOL value;
				returnCode = AT_GetBool(handle, s.boolMapIterator->first,
					&value);
				s.boolMapIterator->second = value;
				std::wcout << " = " << value;
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// int
	for (s.intMapIterator = s.intMap.begin();
		s.intMapIterator != s.intMap.end();
		s.intMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.intMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.intMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.intMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.intMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not get " << s.intMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.intMapIterator->first;
			if (readable)
			{
				AT_64 value;
				returnCode = AT_GetInt(handle, s.intMapIterator->first,
					&value);
				s.intMapIterator->second = value;
				std::wcout << " = " << value;
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// float
	for (s.floatMapIterator = s.floatMap.begin();
		s.floatMapIterator != s.floatMap.end();
		s.floatMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.floatMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.floatMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.floatMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.floatMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not get " << s.floatMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.floatMapIterator->first;
			if (readable)
			{
				double value;
				returnCode = AT_GetFloat(handle, s.floatMapIterator->first,
					&value);
				s.floatMapIterator->second = value;
				std::wcout << " = " << value;
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// enum
	for (s.enumMapIterator = s.enumMap.begin();
		s.enumMapIterator != s.enumMap.end();
		s.enumMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.enumMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.enumMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.enumMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.enumMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not get " << s.enumMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.enumMapIterator->first;
			if (readable)
			{
				int index = 0;
				AT_WC *str = new AT_WC[256];
				returnCode = AT_GetEnumIndex(handle,
					s.enumMapIterator->first,
					&index);
				returnCode = AT_GetEnumStringByIndex(handle,
					s.enumMapIterator->first,
					index, str, 256);
				//delete[] s.enumMapIterator->second; // small leak
				s.enumMapIterator->second = str;
				std::wcout << " = " << str;
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
}

void Zyla::set(ZylaSettings &s)
{
	//// bool
	for (s.boolMapIterator = s.boolMap.begin();
		s.boolMapIterator != s.boolMap.end();
		s.boolMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.boolMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.boolMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.boolMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.boolMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not set " << s.boolMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.boolMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetBool(handle,
					s.boolMapIterator->first,
					s.boolMapIterator->second);
				if (returnCode != AT_SUCCESS)
					std::wcout << " can NOT set";
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// int
	for (s.intMapIterator = s.intMap.begin();
		s.intMapIterator != s.intMap.end();
		s.intMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.intMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.intMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.intMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.intMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not set " << s.intMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.intMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetInt(handle, 
					s.intMapIterator->first,
					s.intMapIterator->second);
				if (returnCode != AT_SUCCESS)
					std::wcout << " can NOT set";
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// float
	for (s.floatMapIterator = s.floatMap.begin();
		s.floatMapIterator != s.floatMap.end();
		s.floatMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.floatMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.floatMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.floatMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.floatMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not set " << s.floatMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.floatMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetFloat(handle, 
					s.floatMapIterator->first,
					s.floatMapIterator->second);
				if (returnCode != AT_SUCCESS)
					std::wcout << " can NOT set";
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
	//// enum
	for (s.enumMapIterator = s.enumMap.begin();
		s.enumMapIterator != s.enumMap.end();
		s.enumMapIterator++)
	{
		AT_BOOL implemented;
		returnCode = AT_IsImplemented(handle, s.enumMapIterator->first,
			&implemented);
		AT_BOOL readOnly;
		returnCode = AT_IsReadOnly(handle, s.enumMapIterator->first,
			&readOnly);
		AT_BOOL readable;
		returnCode = AT_IsReadable(handle, s.enumMapIterator->first,
			&readable);
		AT_BOOL writable;
		returnCode = AT_IsWritable(handle, s.enumMapIterator->first,
			&writable);
		if (returnCode != AT_SUCCESS)
		{
			std::wcout << "FAIL: can not set " << s.enumMapIterator->first << std::endl;
		}
		else
		{
			std::wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.enumMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetEnumString(handle,
					s.enumMapIterator->first,
					s.enumMapIterator->second);
				if (returnCode != AT_SUCCESS)
					std::wcout << " can NOT set";
			}
			std::wcout << std::endl;
		}
	}
	std::cout << std::endl;
}

void Zyla::start(const int &Ts)
{
	//// flush queue and wait buffers;
	returnCode = AT_Flush(handle);

	//// get info
	samplePeriod = Ts;
	returnCode = AT_GetInt(handle, L"ImageSizeBytes", &imageSizeBytes);
	bufferSize = (int)(imageSizeBytes);
	returnCode = AT_GetFloat(handle, L"FrameRate", &frameRate);
	queueLength = (int)(frameRate * samplePeriod + 1); // min length = 1;
	returnCode = AT_GetInt(handle, L"AOIStride", &imageStride);
	returnCode = AT_GetInt(handle, L"AOIWidth", &imageWidth);
	returnCode = AT_GetInt(handle, L"AOIHeight", &imageHeight);
	int index = 0;
	AT_WC *str = new AT_WC[256];	
	returnCode = AT_GetEnumIndex(handle, L"Pixel Encoding", &index);
	returnCode = AT_GetEnumStringByIndex(handle, L"Pixel Encoding", index, str, 256);
	imageEncode = str;

	//// allocate buffer
	buffers = new unsigned char*[queueLength];
	alignedBuffers = new unsigned char*[queueLength];
	for (int i = 0; i < queueLength; i++)
	{
		buffers[i] = new unsigned char[bufferSize + 7];
		alignedBuffers[i] = reinterpret_cast<unsigned char*>
			((reinterpret_cast<unsigned	long>(buffers[i% queueLength]) + 7) & ~7);
	}
	//// pass buffers to queue
	for (int i = 0; i < queueLength; i++)
	{
		returnCode = AT_QueueBuffer(handle, alignedBuffers[i], bufferSize);
	}
	//// start acquisition
	returnCode = AT_Command(handle, L"AcquisitionStart");
	accumNumFrames = 0;
}

void Zyla::stop()
{
	//// stop acquisition
	returnCode = AT_Command(handle, L"AcquisitionStop");
	returnCode = AT_Flush(handle);
	//// free buffer
	for (int i = 0; i < queueLength; i++)
	{
		delete[] buffers[i];
	}
	delete[] buffers;
	delete[] alignedBuffers;
}

void Zyla::process(cv::Mat &image)
{
	//// grab buffer
	unsigned char* pointer;
	int size;
	returnCode = AT_WaitBuffer(handle, &pointer, &size, 0); // timeout = 0, only get existing frames
	//cerr << "zyla process wait buffer returns " << returnCode << endl;
	if (returnCode == 0)
	{
		//// re-queue buffer
		returnCode = AT_QueueBuffer(handle, alignedBuffers[accumNumFrames % queueLength], bufferSize);
		//cerr << "re-queue returns " << returnCode << endl;
		accumNumFrames++;
		//// clean up buffer
		image = cv::Mat(imageHeight, imageWidth, CV_16UC1);
		returnCode = AT_ConvertBuffer(pointer, reinterpret_cast<unsigned char*>(image.data),
			imageWidth, imageHeight, imageStride, imageEncode, L"Mono16");
		//cerr << "convert returns " << returnCode << endl;
	}
	else
	{
		return;
	}
}











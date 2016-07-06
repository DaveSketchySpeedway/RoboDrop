/*
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEva

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

	floatMap[L"ExposureTime"] = 0.001; // seconds
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
	enumMap[L"AOIBinning"] = L"4x4"; // binning, intensity vs resolution
	//enumMap[L"AOILayout"] = L"Image"; // Kinetics, TDI, Multitrack
	//enumMap[L"SensorReadoutMode"] = L"Bottom Up Sequential";
	enumMap[L"SimplePreAmpGainControl"] = L"12-bit (high well capacity)";
	enumMap[L"PixelEncoding"] = L"Mono12Packed"; // Mono12 Mono16 Mono32
	enumMap[L"BitDepth"] = L"12Bit";

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
		wcout << boolMapIterator->first << " = " <<
			boolMapIterator->second << endl;
	}
	cout << endl;
	for (intMapIterator = intMap.begin();
		intMapIterator != intMap.end();
		intMapIterator++)
	{
		wcout << intMapIterator->first << " = " <<
			intMapIterator->second << endl;
	}
	cout << endl;
	for (floatMapIterator = floatMap.begin();
		floatMapIterator != floatMap.end();
		floatMapIterator++)
	{
		wcout << floatMapIterator->first << " = " <<
			floatMapIterator->second << endl;
	}
	cout << endl;
	for (enumMapIterator = enumMap.begin();
		enumMapIterator != enumMap.end();
		enumMapIterator++)
	{
		wcout << enumMapIterator->first << " = " <<
			enumMapIterator->second << endl;
	}
	cout << endl;
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
		cout << "FAIL: zyla can not initialise library, return " << 
			returnCode << endl;
		return;
	}
	else
	{
		cout << "zyla initialized library" << endl;
	}
	//// handle
	returnCode = AT_Open(cameraIndex, &handle);
	if (returnCode != AT_SUCCESS)
	{
		cout << "FAIL: zyla can not open, return " <<
			returnCode << endl;
		return;
	}
	else
	{
		cout << "zyla opened with handle " << handle << endl;
	}
	cout << endl;
}

Zyla::~Zyla()
{
	//// handle
	returnCode = AT_Close(handle);
	if (returnCode != AT_SUCCESS)
	{
		cout << "FAIL: zyla can not close, return " <<
			returnCode << endl;
	}
	else
	{
		cout << "zyla closed" << endl;
	}
	//// library
	returnCode = AT_FinaliseLibrary();
	if (returnCode != AT_SUCCESS)
	{
		cout << "FAIL: zyla can not finalise library, return " <<
			returnCode << endl;
	}
	else
	{
		cout << "zyla finalized library" << endl;
	}
	cout << endl;
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
			wcout << "FAIL: can not get " << s.boolMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.boolMapIterator->first;
			if (readable)
			{
				AT_BOOL value;
				returnCode = AT_GetBool(handle, s.boolMapIterator->first,
					&value);
				s.boolMapIterator->second = value;
				wcout << " = " << value;
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not get " << s.intMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.intMapIterator->first;
			if (readable)
			{
				AT_64 value;
				returnCode = AT_GetInt(handle, s.intMapIterator->first,
					&value);
				s.intMapIterator->second = value;
				wcout << " = " << value;
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not get " << s.floatMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.floatMapIterator->first;
			if (readable)
			{
				double value;
				returnCode = AT_GetFloat(handle, s.floatMapIterator->first,
					&value);
				s.floatMapIterator->second = value;
				wcout << " = " << value;
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not get " << s.enumMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
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
				wcout << " = " << str;
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not set " << s.boolMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.boolMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetBool(handle,
					s.boolMapIterator->first,
					s.boolMapIterator->second);
				if (returnCode != AT_SUCCESS)
					wcout << " can NOT set";
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not set " << s.intMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.intMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetInt(handle, 
					s.intMapIterator->first,
					s.intMapIterator->second);
				if (returnCode != AT_SUCCESS)
					wcout << " can NOT set";
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not set " << s.floatMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.floatMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetFloat(handle, 
					s.floatMapIterator->first,
					s.floatMapIterator->second);
				if (returnCode != AT_SUCCESS)
					wcout << " can NOT set";
			}
			wcout << endl;
		}
	}
	cout << endl;
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
			wcout << "FAIL: can not set " << s.enumMapIterator->first << endl;
		}
		else
		{
			wcout << "i" << implemented << "o" << readOnly <<
				"r" << readable << "w" << writable << "\t" <<
				s.enumMapIterator->first;
			if (writable)
			{
				returnCode = AT_SetEnumString(handle,
					s.enumMapIterator->first,
					s.enumMapIterator->second);
				if (returnCode != AT_SUCCESS)
					wcout << " can NOT set";
			}
			wcout << endl;
		}
	}
	cout << endl;
}

void Zyla::start()
{

}

void Zyla::end()
{

}









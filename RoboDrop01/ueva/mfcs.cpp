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

#include "mfcs.h"

Mfcs::Mfcs(unsigned short sn, int ez)
{
	// load library
	library_handle = LoadLibrary(TEXT("mfcs_c_64.dll"));
	if (!library_handle)
	{
		std::cerr << "FAIL: can not load mfcs_c_64.dll" << std::endl;
	}
	else
	{
		// link functions
		init_ptr = (init_ptr_type)GetProcAddress(library_handle, "mfcs_initialisation");
		init_ez_ptr = (init_ez_ptr_type)GetProcAddress(library_handle, "mfcsez_initialisation");
		serial_ptr = (serial_ptr_type)GetProcAddress(library_handle, "mfcs_get_serial");
		purge_on_ptr = (purge_ptr_type)GetProcAddress(library_handle, "mfcs_set_purge_on");
		purge_off_ptr = (purge_ptr_type)GetProcAddress(library_handle, "mfcs_set_purge_off");
		close_ptr = (close_ptr_type)GetProcAddress(library_handle, "mfcs_close");
		status_ptr = (status_ptr_type)GetProcAddress(library_handle, "mfcs_get_status");
		read_ptr = (status_ptr_type)GetProcAddress(library_handle, "mfcs_read"); // not sure what it does
		write_ptr = (status_ptr_type)GetProcAddress(library_handle, "mfcs_write"); // not sure what it does
		read_chan_ptr = (read_chan_ptr_type)GetProcAddress(library_handle, "mfcs_read_chan");
		set_auto_ptr = (set_auto_ptr_type)GetProcAddress(library_handle, "mfcs_set_auto");
		set_alpha_ptr = (set_alpha_ptr_type)GetProcAddress(library_handle, "mfcs_set_alpha");

		// initialize pump
		switch (ez)
		{
		case 0:
		{
			if (init_ptr)
			{
				mfcs_handle = init_ptr(sn);
				Sleep(500);
				std::cerr << "mfcs initialized, handle " << mfcs_handle << std::endl;
			}
			else
			{
				std::cerr << "FAIL: mfcs can not initialize" << std::endl;
			}
			break;
		}
		case 1:
		{
			if (init_ptr)
			{
				mfcs_handle = init_ez_ptr(sn);
				Sleep(500);
				std::cerr << "mfcs ez initialized, handle " << mfcs_handle << std::endl;
			}
			else
			{
				std::cerr << "FAIL: mfcs ez can not initialize" << std::endl;
			}
			break;
		}
		}


		// get serial
		if (serial_ptr)
		{
			unsigned short sn;
			unsigned char c = serial_ptr(mfcs_handle, &sn);
			std::cerr << "mfcs sn " << sn << ", return " << (int)c << std::endl;
		}
		else
		{
			std::cerr << "FAIL: mfcs can not get sn" << std::endl;
		}

		// get status
		if (status_ptr)
		{
			unsigned char s;
			unsigned char c = status_ptr(mfcs_handle, &s);
			switch (int(s))
			{
			case 0:
				std::cerr << "mfcs status reset" << std::endl;  break;
			case 1:
				std::cerr << "mfcs status normal" << std::endl; break;
			case 2:
				std::cerr << "mfcs status overpressure" << std::endl; break;
			case 3:
				std::cerr << "mfcs status need remarm" << std::endl; break;
			default:
				std::cerr << "mfcs no physical pump" << std::endl;
			}
		}
		else
		{
			std::cerr << "FAIL: mfcs can not get status" << std::endl;
		}
		
		// set gains
		if (set_alpha_ptr)
		{
			for (int i = 1; i <= 10; i++)
			{
				unsigned char c = set_alpha_ptr(
					mfcs_handle, (unsigned char)i, (unsigned char)5);
				std::cerr << "mfcs set gain return " << (int)c << std::endl;
			}
		}
		else
		{
			std::cerr << "FAIL: mfcs can not set gain" << std::endl;
		}

		std::cerr << std::endl;
	}
}




Mfcs::~Mfcs()
{
	// set zero
	if (set_auto_ptr)
	{
		for (int i = 1; i <= 10; i++)
		{
			unsigned char c = set_auto_ptr(mfcs_handle, (unsigned char)i, (float)0);
			std::cerr << "mfcs command zero, return " << (int)c << std::endl;
		}
	}
	else
	{
		std::cerr << "FAIL: mfcs can not zero" << std::endl;
	}

	// close pump
	if (close_ptr)
	{
		bool b = close_ptr(mfcs_handle);
		std::cerr << "mfcs closed " << std::endl;
	}
	else
	{
		std::cerr << "FAIL: mfcs can not close" << std::endl;
	}

	// free library
	FreeLibrary(library_handle);
	std::cerr << "mfcs_c_64.dll is freed" << std::endl;
	std::cerr << std::endl;
}




void Mfcs::purge_on()
{
	purge_on_ptr(mfcs_handle);
}

void Mfcs::purge_off()
{
	purge_off_ptr(mfcs_handle);
}




void Mfcs::read(unsigned char* s)
{
	read_ptr(mfcs_handle, s);
}

void Mfcs::write(unsigned char* s)
{
	write_ptr(mfcs_handle, s);
}



void Mfcs::measure(int channel, float* pressure, float* pump_time)
{
	float mbar;
	unsigned short t25ms;
	read_chan_ptr(mfcs_handle, (unsigned char)channel, &mbar, &t25ms);
	*pressure = mbar;
	*pump_time = (float)t25ms * (float)0.025;
}

void Mfcs::command(int channel, float pressure)
{
	set_auto_ptr(mfcs_handle, (unsigned char)channel, pressure);
}





void Mfcs::gain(int channel, int gain)
{
	if (set_alpha_ptr)
	{
		unsigned char c = set_alpha_ptr(mfcs_handle, (unsigned char)channel, (unsigned char)gain);
		std::cerr << "mfcs new gain, return " << (int)c << std::endl;
	}
	else
	{
		std::cerr << "FAIL: mfcs can not new gain " << std::endl;
	}
	std::cerr << std::endl;
}

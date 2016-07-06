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

#ifndef MFCS_H
#define MFCS_H

#include <Windows.h>
#include <iostream>


class Mfcs
{
public:
	Mfcs(unsigned short sn = 0, int ez = 0);
	~Mfcs();
	void purge_on();
	void purge_off();

	void write(unsigned char* s); // not used in operation
	void read(unsigned char* s); // not used in operation

	void measure(int channel, float* pressure, float* pump_time);
	void command(int channel, float pressure);
	void gain(int channel, int gain);
	



private:
	
	typedef unsigned long(__stdcall* init_ptr_type)(unsigned short);
	typedef unsigned long(__stdcall* init_ez_ptr_type)(unsigned short);
	typedef bool(__stdcall* close_ptr_type)(unsigned long);
	typedef unsigned char(__stdcall* serial_ptr_type)(unsigned long, unsigned short*);
	typedef unsigned char(__stdcall* purge_ptr_type)(unsigned long);
	typedef unsigned char(__stdcall* status_ptr_type)(unsigned long, unsigned char*);
	typedef unsigned char(__stdcall* read_chan_ptr_type)(
		unsigned long, unsigned char, float*, unsigned short*);
	typedef unsigned char(__stdcall* set_auto_ptr_type)(
		unsigned long, unsigned char, float);
	typedef unsigned char(__stdcall* set_alpha_ptr_type)(
		unsigned long, unsigned char, unsigned char);

	init_ptr_type init_ptr;
	init_ez_ptr_type init_ez_ptr;
	serial_ptr_type serial_ptr;
	purge_ptr_type purge_on_ptr, purge_off_ptr;
	close_ptr_type close_ptr;
	status_ptr_type status_ptr, read_ptr, write_ptr;
	read_chan_ptr_type read_chan_ptr;
	set_auto_ptr_type set_auto_ptr;
	set_alpha_ptr_type set_alpha_ptr;

	HINSTANCE library_handle;
	unsigned long mfcs_handle;


};








#endif

# RoboDrop
a program for controlling microfludics droplets

Copyright 2016 David Wong

[Demo](https://www.youtube.com/watch?v=VtfMz4Gftpk)

[Documentation](https://uwspace.uwaterloo.ca/handle/10012/11124)

[Contact](yh3wong@uwaterloo.ca)






## Content

RoboDrop01 -- prototype with old algorithms

RoboDrop02 -- better tracking methods

model_ctrl -- matlab script for modelling and designing controllers

pump_sysid -- system identification with linear regression






## Operating System

Windows 7 Professional

executable is tested on a i7-4790 machine

## Pump

RoboDrop works with Fluigent MFCS or MFCS-ez pump.

To use other pumps, write your own pump class to replace mfcs.h and mfcs.cpp

## Camera

RoboDrop works with Andor Zyla camera. AndorSDK3.0 must be purchased separately

To use other cameras, write your own camera class to replace zyla.h and zyla.cpp

## Controller

Design controller that fits your network using Matlab script provided (step1 - step4)

export into .yaml (step3)

import in RoboDrop Setup window

## Third Party

Following libraries are required to run the executable:
```
	atblkbx.dll
	atd_bitflow.dll
	atcore.dll
	atdevapogee.dll
	atdevregcam.dll
	atmcd64d.dll
	atspooler.dll
	atusb_libusb.dll
	atusb_libusb10.dll
	atutility.dll
	mfcs_c_64.dll
	opencv_world310.dll
	Qt5Core.dll
	Qt5Gui.dll
	Qt5Widgets.dll
	\platforms\qwindows.dll
```


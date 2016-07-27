microfluidics Enhanced Vision-based Automation
Copyright 2016 David Wong
https://github.com/DaveSketchySpeedway/uEva



Platform:
	Source code is platform independent, EXCEPT for:
		camera class (zyla.h, zyla.cpp)
		pump class (mfcs.h, mfcs.cpp)
	because of third party dll
	executable is tested on a i7-4790 Windows 7 Professional machine

Pump:
	uEVA works with Fluigent MFCS or MFCS-ez pump.
	To use other pumps, write your own pump class to replace mfcs.h and mfcs.cpp

Camera:
	uEVA works with Andor Zyla camera. AndorSDK3.0 must be purchased separately
	To use other cameras, write your own camera class to replace zyla.h and zyla.cpp

Controller:
	Design controller that fits your network using Matlab script provided (step0 - step4)
	export into .yaml (step5)
	import using uEVA setup window

Deployment:
	Following libraries are required to run the executable:
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

		


Contact author for more info
email: yh3wong@uwaterloo.ca
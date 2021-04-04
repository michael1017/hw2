# HW2
## Intro
NTHUEE240500 homework 2.
## Installation
* prerequirement
	* python: version >= 3.6
	* git: version >= 2.17
	* 107060005.csv
	* latest pip
	    * matplotlib
```
git clone https://github.com/michael1017/hw2.git
```

## Execution
Excute the command below, the compiled binary will be sent to your STM32 device.
```
sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f
``` 
After that follow the wire connection discribe in main.cpp
![](https://i.imgur.com/y8khUTG.png)
![](https://i.imgur.com/Lo8KuDG.jpg)

FTT.py is a python script to analysis the output signal with using matplotlib

## Example Output
the low pass filter I used is composed by 38k ohm resister and 0.22uF capacitance. The corner frequency is 19.038 Hz.
The 5Hz WaveOut signal before passing low pass filter
![](https://i.imgur.com/JGTB8cF.png)

The WaveOut signal before passing low pass filter
From left to right is 5Hz, 10Hz and 50Hz.
![](https://i.imgur.com/DLeSEaJ.png)

The WaveOut signal after passing low pass filter
From left to right is 5Hz, 10Hz and 50Hz.
![](https://i.imgur.com/IWCXRvO.png)

The 5Hz WaveOut signal after passing low pass.
The WaveOut signal is measured from WaveIn(D7) and analyzed using FFT.py
![](https://i.imgur.com/sc3eiKX.png)

The 10Hz WaveOut signal after passing low pass.
The WaveOut signal is measured from WaveIn(D7) and analyzed using FFT.py
![](https://i.imgur.com/Whwtecl.png)

The 50Hz WaveOut signal after passing low pass.
The WaveOut signal is measured from WaveIn(D7) and analyzed using FFT.py
![](https://i.imgur.com/uv0bipp.png)

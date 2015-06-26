# BINX
> _Universal format of firmware files_ 

Firmware **BINX** format may be of interest to developers of devices on microcontrollers, if they plan to implement in their devices the firmware upgrade function (**Update Firmware**), i.e. self programming MCU, under conditions:
* insufficiency intermediate memory which used for receiving the new firmware
* slow or unstable communication channel for programming of device
* developer not wish give task for MCU for parsing of HEX format

In fact, **BINX** is a binary representation of a conventional firmware HEX file standard of '**Intel HEX**', 
it transmitted to the MCU "**as is**".

![hex2binx_screenshot](https://raw.githubusercontent.com/JohnMcLaren/HEX2BINX/master/img/hex2binx_screenshot.png)

Read more about BINX there http://johnmclaren.github.io/HEX2BINX/

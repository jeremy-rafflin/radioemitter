##radioemitter

Radio emitter is used to controll radio plugs.

This module is for [gladys v3](https://github.com/GladysProject/Gladys)

It use the module [gladys-serial](https://github.com/GladysProject/gladys-serial) to send a radio code to the arduino that's connected to the Raspberry Pi.

**How to use** 

The module only implement the exec function. It's automaticaly call by gladys when you put on/off the device.

The identifier is the off code for disable the plug. For exemple : 16129807 

The on code is calculated, it's the off code +1 (the state value when you put on the device). 


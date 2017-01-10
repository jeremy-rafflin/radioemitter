##radioemitter

Radio emitter is used to controll radio plugs.

This module is for [gladys v3](https://github.com/GladysProject/Gladys)

It use the module [gladys-serial](https://github.com/GladysProject/gladys-serial) to send a radio code to the arduino that's connected to the Raspberry Pi.

**How to use** 

You can find the code for the arduino in the file arduino_code.ino.

The module only implement the exec function. It's automaticaly call by gladys when you put on/off the device.

The identifier is the off code for disable the plug. For exemple : 16129807 

The on code is calculated, it's the off code +1 (the state value when you put on the device).

**How to add a device on gladys and use it** 

Actualy, to create a device, you must create it in the database.

Create a device in the 'device' table with 'radioemitter' for service culumn value. 
For exemple  :

| name 				| protocol 	| service 		| identifier 	| room 	| id 	| createdAt | updatedAt |
| ---| ---| ---| ---| ---| ---| ---| ---|
| Petite lumière salon 	| radio 	| radioemitter 	| 16129806 		| 2 	| 5 	|  			| 	 |

Create the devicetype correspondance with 'binary' (for binary device, min is 0 and max is 1) for the 'type' and the code af your radio device for the 'identifier'.

For exemple : 

| type | tag | sensor | unit | min | max | display | device | id | createdAt | updatedAt | name | identifier |
| ---| ---| ---| ---| ---| ---| ---| ---| ---| ---| ---| ---| ---|
| binary | lumiere_salon | 0 | 0 | 1 | 1 | 5 | 4 | lumiere_salon | 16129806 |

After that, go on Dladys, to the devices page and you can controle your device.

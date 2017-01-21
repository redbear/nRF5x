# Getting Started Guide

## Out-of-Box Test

To test the board for the first time, follow these steps:

* The preloaded firmware is a BLE Heart Rate peripheral simulator.
* To test the BLE Nano 2 or Blend 2 boards
	* BLE Nano 2
		* DAPLink
			* Stack the BLE Nano 2 on the DAPLink USB dongle and connect to PC USB port.
			* ![image](./images/Nano2/Nano2_01.jpg)
		* ProtoBoard
			* If you want to try with coin cell battery (CR2032) with the Proto Board, stack the BLE Nano 2 correctly to the ProtoBoard.
			* ![image](./images/Nano2/ProtoBoard_01.jpg)
	* Blend 2	
		* Connect it to your 5V USB adaptor or PC USB port using an USB **DATA** cable.
		* Note: Some USB cables are for charging only, no data lines inside.
* You will see the onboard LED is flashing.
* Use Nordic's iOS or Android Apps called nRFToolBox and use the HRM icon to connect to the board, the Heart Rate counter will be increasing every 1 second.
* ![image](./images/App_01.png)
* Congrats, your board works as expected.

## Arduino

* Follow the [Arduino Installation Guide](./Arduino_Board_Package_Installation_Guide.md).

## Nordic SDK

* Follow the [Nordic nRF52 SDK User Guide](./Nordic_SDK_User_Guide.md).

## mbed

- To be written -






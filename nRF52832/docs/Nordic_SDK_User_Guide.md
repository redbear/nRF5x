# Nordic SDK User Guide

This document introduces how to use the Nordic SDK12 with board nRF52832. Nordic SDK supports Keil 5.x, GCC and Eclipse development. Here, we will only instroduce the development using Keil 5.x IDE.

## Development of KEIL 5.xx IDE

### 1. Download Keil5.xx and install

 * Download [MDK-ARM](https://www.keil.com/download/product/ "MDK-ARM").

### 2. Download SDK

 * Download SDK from Nordic Official site:

    [http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832](http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832 "Download Nordic SDK")

 * Find ***SOFTWARE DEVELOPMENT KIT***, select ***nRF5-SDK-zip*** and download.

    ![nordic_sdk_1](images/nordic_sdk/nordic_sdk_1.png)

### 3. Installing pack of NordicSemiconductor

 * Open ***Keil uVision 5***, click ***pack install***:

    ![nordic_sdk_2](images/nordic_sdk/nordic_sdk_2.png)

 * Under the list of ***Devices***, select ***Nordic Semiconductor/nRF52 Serials/nRF52832-xxAA***, then installing ***NordicSemiconductor:nRF_DeviceFamillyPack***.

    ![nordic_sdk_3](images/nordic_sdk/nordic_sdk_3.png)

 * After installing the pack successfully, click ***Project->Open Project...*** to open a exist project. For example, here will open example ***"ble-app-hrs"***(nRF5-SDK-12.0.0\examples\ble_peripheral\ble-app-hrs\pca10040\s132\arm5-no-packs). Then you can compile this example.

    ![nordic_sdk_4](images/nordic_sdk/nordic_sdk_4.png)

    ![nordic_sdk_5](images/nordic_sdk/nordic_sdk_5.png)

### 4. Configuration for Compiling and uploading

 * If use softdevice-s132-3.0, IROM should start at 0x1F000,IRAM is defined according to the actual used:

    ![nordic_sdk_6](images/nordic_sdk/nordic_sdk_6.png)

    If not use softdevice, config IROM and IRAM as:

    ![nordic_sdk_7](images/nordic_sdk/nordic_sdk_7.png)

 * Click ***Debug***, select ***J-LINK/J-TRACE Cortex***(It is assumed that use nRF52DK board, the interface is JLink):
    
    ![nordic_sdk_8](images/nordic_sdk/nordic_sdk_8.png)

 * Then click ***settings***, configurate the ***Programming Algorithm***:

    ![nordic_sdk_9](images/nordic_sdk/nordic_sdk_9.png)

    ![nordic_sdk_10](images/nordic_sdk/nordic_sdk_10.png)

 * After these steps, now you can compile and upload the project!

### 5. DAPLink Configuration
 
 * Please refer to the [DAPLink User Guide](DAPLink_User_Guide.md).


## Development with eclipse IDE and GCC

 * Please refer to [https://devzone.nordicsemi.com/tutorials/7/](https://devzone.nordicsemi.com/tutorials/7/ "Development with GCC and Eclipse")
 
 
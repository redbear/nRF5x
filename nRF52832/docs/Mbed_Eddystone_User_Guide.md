
# MBED Eddystone User Guide

This document introduces the development of RedBear Blend 2.0 and BLE Nano 2.0 using the **mbed Online IDE**.

We are submitting the information of Blend 2.0 and Nano 2.0 to mbed platform for approval, here we will use the nRF52DK to instead of Blend 2.0 and it has the similar pinout as nRF52DK.

### 1. Select target platform

 * Sign into mbed website, go to **Workspace Management** page. Click on the red area to select new platform.
    
    ![mbed_ide_1](images/mbed_ide/mbed_ide_1.png)

 * In the select platform window, click **Add Platform**.

    ![mbed_ide_2](images/mbed_ide/mbed_ide_2.png)

 * Select nRF52DK board:

    ![mbed_ide_3](images/mbed_ide/mbed_ide_3.png)

 * Click **Add to your mbed Compiler**:

    ![mbed_ide_4](images/mbed_ide/mbed_ide_4.png)

 * Then nRF52DK will exist in your board list, Click **Select Platform**, now you will compile the source code with nRF52DK board. 

    ![mbed_ide_5](images/mbed_ide/mbed_ide_5.png)

    ![mbed_ide_6](images/mbed_ide/mbed_ide_6.png)

### 2. Inport Eddystone programs

 * Click **Import** then Click **click here**:

    ![Eddystone_1](images/Eddystone/Eddystone_1.png)

 * Add Source URL: https://developer.mbed.org/teams/Bluetooth-Low-Energy/code/BLE_EddystoneBeacon_Service/, then Click Import:

    ![Eddystone_2](images/Eddystone/Eddystone_2.png)

    ![Eddystone_3](images/Eddystone/Eddystone_3.png)

### 3. Compilling programs

 * Select example **BLE_EddystoneBeacon_Service**, click **Compile**:

    ![Eddystone_4](images/Eddystone/Eddystone_4.png)

 * When the compilation is complete, the **BLE_EddystoneBeacon_Service_NRF52_DK.hex** will generate.

### 4. Uploading firmware

 * Connecting BLE Nano2 to PC, then a driver **DAPLink** will appear. Drag hex file **BLE_EddystoneBeacon_Service_NRF52_DK.hex** to this driver.Then Eddystone will running.

    ![Eddystone_5](images/Eddystone/Eddystone_5.png)


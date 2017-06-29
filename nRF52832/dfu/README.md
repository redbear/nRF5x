# nRF52832-DFU

This DFU project is compiled on Nordic SDK11. It uses single bank.

## Compiling DFU project

 * Copy project **rbl-nrf52832-bootloader** to path **"Nordic SDK11\examples\dfu\"**.

 * Open the project **rbl-nrf52832-bootloader\pca10040\dual-bank-ble-s132\arm5-no-packs\dfu-dual-bank-ble-s132-pca10040.uvprojx** and compile.

## Change

 * Change the **BOOTLOADER_BUTTON** to P04.

    ```
         #define BOOTLOADER_BUTTON  4
    ```

 * Add a marked LED (100ms blinky)
    
    ```
       #define DFU_BLINKY_BLEND2_LED   25 //For Blend2.0
    ```

    ```
       #define DFU_BLINKY_NANO2_LED    11 //For Nano2.0
    ```

## More information

 * [nRF52832 docs](https://github.com/redbear/nRF52-Beta/tree/master/docs "Docs")


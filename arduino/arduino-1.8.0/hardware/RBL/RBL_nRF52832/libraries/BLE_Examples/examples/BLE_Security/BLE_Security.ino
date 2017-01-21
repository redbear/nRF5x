/*
 * Copyright (c) 2016 RedBear
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <nRF5x_BLE_API.h>

#define DEVICE_NAME                       "BLE Security"
#define TXRX_BUF_LEN                      20

BLE                                       ble;
Timeout                                   timeout;

static uint8_t passkey[] = "123456";

static uint8_t rx_buf[TXRX_BUF_LEN];
static uint8_t rx_buf_num;
static uint8_t rx_state=0;

// The uuid of service and characteristics
static const uint8_t service1_uuid[]        = {0x71, 0x3D, 0, 0, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};
static const uint8_t service1_tx_uuid[]     = {0x71, 0x3D, 0, 3, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};
static const uint8_t service1_rx_uuid[]     = {0x71, 0x3D, 0, 2, 0x50, 0x3E, 0x4C, 0x75, 0xBA, 0x94, 0x31, 0x48, 0xF1, 0x8D, 0x94, 0x1E};
static const uint8_t uart_base_uuid_rev[]   = {0x1E, 0x94, 0x8D, 0xF1, 0x48, 0x31, 0x94, 0xBA, 0x75, 0x4C, 0x3E, 0x50, 0, 0, 0x3D, 0x71};

uint8_t tx_value[TXRX_BUF_LEN] = {0,};
uint8_t rx_value[TXRX_BUF_LEN] = {0,};

// Create characteristic and service
GattCharacteristic  characteristic1(service1_tx_uuid, tx_value, 1, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE );
GattCharacteristic  characteristic2(service1_rx_uuid, rx_value, 1, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ);
GattCharacteristic *uartChars[] = {&characteristic1, &characteristic2};
GattService         uartService(service1_uuid, uartChars, sizeof(uartChars) / sizeof(GattCharacteristic *));


void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *params) {
  ble.startAdvertising();
}

void gattServerWriteCallBack(const GattWriteCallbackParams *Handler) {
  uint16_t index;
  Serial.print("gattServerWriteCallBack : ");
  if (Handler->handle == characteristic1.getValueAttribute().getHandle()) {
    for(index=0; index<Handler->len; index++) {
      Serial.write(Handler->data[index]);
    }
  }
  Serial.println("");
}

void m_uart_rx_handle() {
  //update characteristic data
  ble.updateCharacteristicValue(characteristic2.getValueAttribute().getHandle(), rx_buf, rx_buf_num, true);
  memset(rx_buf, 0x00,20);
  rx_state = 0;
}

void uart_handle(uint32_t id, SerialIrq event) {
  // Serial rx IRQ
  if(event == RxIrq) {
    if (rx_state == 0) {
      rx_state = 1;
      timeout.attach_us(m_uart_rx_handle, 100000);
      rx_buf_num=0;
    }
    while(Serial.available()) {
      if(rx_buf_num < 20) {
        rx_buf[rx_buf_num] = Serial.read();
        rx_buf_num++;
      }
      else
        Serial.read();
    }
  }
}

/**
 * @brief To indicate that a security procedure for the link has started.
 * 
 * @param[in]  handle
 * @param[in]  allowBonding
 * @param[in]  requireMITM
 * @param[in]  iocaps          IO_CAPS_DISPLAY_ONLY     = 0x00,   Display only. 
 *                             IO_CAPS_DISPLAY_YESNO    = 0x01,   Display and yes/no entry. 
 *                             IO_CAPS_KEYBOARD_ONLY    = 0x02,   Keyboard only. 
 *                             IO_CAPS_NONE             = 0x03,   No I/O capabilities.
 *                             IO_CAPS_KEYBOARD_DISPLAY = 0x04,   Keyboard and display.
 */
void SecurityInitiatedCB(Gap::Handle_t handle, bool allowBonding, bool requireMITM, SecurityManager::SecurityIOCapabilities_t iocaps)
{
  Serial.println("Security:Initiate CB");
}

/**
 * @brief To indicate that the security procedure for the link has completed.
 * 
 * @param[in]  handle
 * @param[in]  status        SEC_STATUS_SUCCESS              = 0x00,  Procedure completed with success.
 *                           SEC_STATUS_TIMEOUT              = 0x01,  Procedure timed out.
 *                           SEC_STATUS_PDU_INVALID          = 0x02,  Invalid PDU received.
 *                           SEC_STATUS_PASSKEY_ENTRY_FAILED = 0x81,  Passkey entry failed (user canceled or other).
 *                           SEC_STATUS_OOB_NOT_AVAILABLE    = 0x82,  Out of Band Key not available.
 *                           SEC_STATUS_AUTH_REQ             = 0x83,  Authentication requirements not met.
 *                           SEC_STATUS_CONFIRM_VALUE        = 0x84,  Confirm value failed.
 *                           SEC_STATUS_PAIRING_NOT_SUPP     = 0x85,  Pairing not supported. 
 *                           SEC_STATUS_ENC_KEY_SIZE         = 0x86,  Encryption key size.
 *                           SEC_STATUS_SMP_CMD_UNSUPPORTED  = 0x87,  Unsupported SMP command.
 *                           SEC_STATUS_UNSPECIFIED          = 0x88,  Unspecified reason.
 *                           SEC_STATUS_REPEATED_ATTEMPTS    = 0x89,  Too little time elapsed since last attempt.
 *                           SEC_STATUS_INVALID_PARAMS       = 0x8A,  Invalid parameters.
 * 
 */
void SecurityCompletedCB(Gap::Handle_t handle, SecurityManager::SecurityCompletionStatus_t status)
{
  Serial.println("Security:Completed CB");
  switch(status) {
    case SecurityManager::SEC_STATUS_SUCCESS:
    {
      Serial.println("Status:SEC_STATUS_SUCCESS");
    }break;

    case SecurityManager::SEC_STATUS_TIMEOUT:
    {
      Serial.println("Status:SEC_STATUS_TIMEOUT");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    }break;

    case SecurityManager::SEC_STATUS_PDU_INVALID:
    {
      Serial.println("Status:SEC_STATUS_PDU_INVALID");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    }break;
    
    case SecurityManager::SEC_STATUS_PASSKEY_ENTRY_FAILED:
    {
      Serial.println("Status:SEC_STATUS_PASSKEY_ENTRY_FAILED");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    }break;

    case SecurityManager::SEC_STATUS_CONFIRM_VALUE:
    {
      Serial.println("Status:SEC_STATUS_CONFIRM_VALUE");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    }break;
        
    case SecurityManager::SEC_STATUS_PAIRING_NOT_SUPP:
    {
      Serial.println("Status:SEC_STATUS_PAIRING_NOT_SUPP");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    }break;
      
    default:
      Serial.println("Status:Other");
      ble.disconnect(Gap::REMOTE_USER_TERMINATED_CONNECTION);
    break;
  }
}
/**
 * @brief  To indicate that the link with the peer is secured. 
 *         For bonded devices,subsequent reconnections with a bonded peer will result only in this callback
 *         when the link is secured; setup procedures will not occur (unless the bonding information is either lost or deleted on either or both sides).
 *         
 * @param[in]  handle
 * @param[in]  securityMode      SECURITY_MODE_NO_ACCESS,
 *                               SECURITY_MODE_ENCRYPTION_OPEN_LINK, Require no protection, open link.
 *                               SECURITY_MODE_ENCRYPTION_NO_MITM,   Require encryption, but no MITM protection.
 *                               SECURITY_MODE_ENCRYPTION_WITH_MITM, Require encryption and MITM protection.
 *                               SECURITY_MODE_SIGNED_NO_MITM,       Require signing or encryption, but no MITM protection.
 *                               SECURITY_MODE_SIGNED_WITH_MITM,     Require signing or encryption, and MITM protection.
 */
void SecurityLinkSecuredCB(Gap::Handle_t handle, SecurityManager::SecurityMode_t securityMode)
{
  Serial.println("Security: LinkSecured");
  Serial.print("Handle : ");
  Serial.println(handle, HEX);
  Serial.print("SecurityMode : ");
  Serial.println(securityMode, DEC);
}

/**
 * @brief  To indicate that device context is stored persistently.
 * 
 * @param[in]  handle
 */
void SecurityContextStoredCB(Gap::Handle_t handle)
{
  Serial.println("Security: ContextStored");
  Serial.print("Handle : ");
  Serial.println(handle, HEX);
}

/**
 * @brief  To set the callback for when the passkey needs to be displayed on a peripheral with DISPLAY capability.
 * 
 * @param[in]  handle
 * @param[in]  passkey
 */
void SecurityPasskeyDisplayCB(Gap::Handle_t handle, const SecurityManager::Passkey_t passkey)
{
  Serial.println("Security: Display Passkey");
  Serial.print("The Passkey : ");
  Serial.println((const char *)passkey);
}

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  Serial.attach(uart_handle);
  Serial.println("Start");
  
  ble.init();
  ble.onDisconnection(disconnectionCallBack);
  ble.onDataWritten(gattServerWriteCallBack);
  /**
   * @brief Initialize security
   * 
   * @param[in]  enableBonding   Allow for bonding
   * @param[in]  requireMITM     Require protection for man-in-the-middle attacks.
   * @param[in]  iocaps          IO_CAPS_DISPLAY_ONLY     = 0x00,   Display only. 
   *                             IO_CAPS_DISPLAY_YESNO    = 0x01,   Display and yes/no entry. 
   *                             IO_CAPS_KEYBOARD_ONLY    = 0x02,   Keyboard only. 
   *                             IO_CAPS_NONE             = 0x03,   No I/O capabilities.
   *                             IO_CAPS_KEYBOARD_DISPLAY = 0x04,   Keyboard and display.
   * @param[in]  passkey         To specify a static passkey. Default NULL.
   */
  ble.initializeSecurity(1, 1, SecurityManager::IO_CAPS_DISPLAY_ONLY, passkey);
  ble.onSecuritySetupInitiated(SecurityInitiatedCB);
  ble.onSecuritySetupCompleted(SecurityCompletedCB);
  ble.onLinkSecured(SecurityLinkSecuredCB);
  ble.onSecurityContextStored(SecurityContextStoredCB);  
  ble.onPasskeyDisplay(SecurityPasskeyDisplayCB);
  /**
   * @brief Initialize security
   * 
   * @param[in]  securityMode      SECURITY_MODE_NO_ACCESS,
   *                               SECURITY_MODE_ENCRYPTION_OPEN_LINK, Require no protection, open link.
   *                               SECURITY_MODE_ENCRYPTION_NO_MITM,   Require encryption, but no MITM protection.
   *                               SECURITY_MODE_ENCRYPTION_WITH_MITM, Require encryption and MITM protection.
   *                               SECURITY_MODE_SIGNED_NO_MITM,       Require signing or encryption, but no MITM protection.
   *                               SECURITY_MODE_SIGNED_WITH_MITM,     Require signing or encryption, and MITM protection.
   */
  characteristic1.requireSecurity(SecurityManager::SECURITY_MODE_ENCRYPTION_WITH_MITM);
  characteristic2.requireSecurity(SecurityManager::SECURITY_MODE_ENCRYPTION_WITH_MITM);
  
  // setup adv_data and srp_data
  ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,
                                   (const uint8_t *)"TXRX", sizeof("TXRX") - 1);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,
                                   (const uint8_t *)uart_base_uuid_rev, sizeof(uart_base_uuid_rev));
  // set adv_type
  ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
  // add service
  ble.addService(uartService);
  // set device name
  ble.setDeviceName((const uint8_t *)DEVICE_NAME);
  // set tx power,valid values are -40, -20, -16, -12, -8, -4, 0, 4
  ble.setTxPower(4);
  // set adv_interval, 100ms in multiples of 0.625ms.
  ble.setAdvertisingInterval(160);
  // set adv_timeout, in seconds
  ble.setAdvertisingTimeout(0);
  // start advertising
  ble.startAdvertising();

  Serial.println("start advertising");
}

void loop() {
  // put your main code here, to run repeatedly:
  ble.waitForEvent();
}


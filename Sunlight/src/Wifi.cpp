#include <Debug.h>
#include <Globals.h>
#include <Config.h>
#ifdef ESP8266
#include <ESP8266httpUpdate.h>
#else
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#endif
#include <Ticker.h>
#include <Wifi.h>

#ifdef ESP8266
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
void onWifiConnect(const WiFiEventStationModeGotIP &event);
void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);
#elif defined(ESP32)
wifi_event_id_t wifiConnectHandler;
wifi_event_id_t wifiDisconnectHandler;
void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info);
void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info);
#endif

ESP8266WiFiClass WiFi;
Ticker wifiReconnectTimer;
int32_t wifi_raw_strength;
int32_t wifi_strength;
int32_t wifi_percent;
char wifi_bssid_str[18];

void initWifi(){
    #ifdef ESP8266
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  #elif defined(ESP32)
    wifiConnectHandler = WiFi.onEvent(onWifiConnect, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
    wifiDisconnectHandler = WiFi.onEvent(onWifiConnect, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
  #endif
}
void connectToWifi()
{
  Debug("Connecting to WiFi...");
  WiFi.begin(HardcodedWifi_SSID, HardcodedWifi_Password);
}

#ifdef ESP8266
void onWifiConnect(const WiFiEventStationModeGotIP &event)
#elif defined(ESP32)
void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info)
#endif
{
  Debug("Connected to WiFi.");
  isWifiConnected = true;
  ip = WiFi.localIP();
  updateWifiStrength();
}

#ifdef ESP8266
void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
#elif defined(ESP32)
void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info)
#endif
{
  Debug("Disconnected from Wi-Fi.");
  isWifiConnected = false;
  wasWifiConnected = false;
  wifiReconnectTimer.once(2, connectToWifi);
}

void updateWifiStrength()
{
  wifi_raw_strength = WiFi.RSSI();
  wifi_strength = constrain(wifi_raw_strength, -100, -50);
  if (wifi_raw_strength > -40)
  {
    wifi_percent = 100;
  }
  else
  {
    // https://stackoverflow.com/a/25079742/73135
    wifi_percent = map(wifi_strength, -100, -50, 30, 90);
  }

  //get the ap bssid
  //uint8_t* wifi_bssid_ptr = WiFi.BSSID();
  // static struct station_config conf;
  // wifi_station_get_config(&conf);

  WiFi.BSSIDstr().toCharArray(wifi_bssid_str, sizeof wifi_bssid_str, 0);
}

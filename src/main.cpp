#include "header.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  wifi.attach(1, wifi_init);
  WiFi.onEvent(WiFiEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();
}

void wifi_init(){
  if(!wifiInitiated){
    WiFi.mode(WIFI_STA);
    auto result = WiFi.begin(ssid, pass);
    wifiInitiated = true;
    timer_wifi_init = millis();
  }
  else if(!wifiConnected && millis() - timer_wifi_init > 2000){  // Ini boros loop
    wifiInitiated = false;
  }
}

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        case ARDUINO_EVENT_WIFI_STA_START:
            if(!led.active()) led.detach();
            ledfadecount = 0;
            led.attach(1, ledBlink);
            WiFi.setHostname("AP_SSID");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            if(!led.active()) led.detach();
            ledfadecount = 0;
            led.attach(1, ledBlinkTwice);
            wifiConnected = true;
            if(wifi.active()) wifi.detach();
            OTASetup();
            WiFi.enableIpV6();
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            if(!led.active()) led.detach();
            ledfadecount = 0;
            led.attach(1, ledBlinkThrice);
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            break;
        default:
            break;
    }
}

void OTASetup(){
  ArduinoOTA.onStart(onStartFn)
      .onProgress(onProgressFn)
      .onEnd(onEndFn)
      .onError(onErrorFn);
  ArduinoOTA.setPort(3141);
  ArduinoOTA.begin();
}

void onStartFn(){
  if(!led.active()) led.detach();
  led.attach_ms(200, ledBlinkTwice);
  Serial.println("OTA Started");
}

void onErrorFn(ota_error_t res){
  ESP.restart();
  Serial.printf("Error occured: %d", res);
}

void onProgressFn(unsigned int progress, unsigned int total){

}

void onEndFn(){
  Serial.println("OTA Ended");
}

void ledBlink(){ // WIP: Gak ngeblink kalau udah jadi analogWrite
  switch (ledfadecount)
  {
  case 0:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 1:
    digitalWrite(2, LOW);
    ledfadecount = 0;
    break;

  default:
    ledfadecount = 0;
    break;
  }
}

void ledBlinkTwice(){ // WIP: Gak ngeblink kalau udah jadi analogWrite
  switch (ledfadecount)
  {
  case 0:
    digitalWrite(2, HIGH);
    if(led.active())led.detach();
    led.attach_ms(200, ledBlinkTwice);
    ledfadecount ++;
    break;
  case 1:
    digitalWrite(2, LOW);
    ledfadecount ++;
    break;
  case 2:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 3:
    digitalWrite(2, LOW);
    ledfadecount ++;
    break;
  case 4:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 5:
    digitalWrite(2, LOW);
    if(led.active())led.detach();
    led.attach(2, ledBlinkTwice);
    ledfadecount = 0;
    break;

  default:
    ledfadecount = 0;
    break;
  }
}

void ledBlinkThrice(){ // WIP: Gak ngeblink kalau udah jadi analogWrite
  switch (ledfadecount)
  {
  case 0:
    digitalWrite(2, HIGH);
    if(led.active())led.detach();
    led.attach_ms(200, ledBlinkThrice);
    ledfadecount = 1;
    break;
  case 1:
    digitalWrite(2, LOW);
    ledfadecount ++;
    break;
  case 2:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 3:
    digitalWrite(2, LOW);
    ledfadecount ++;
    break;
  case 4:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 5:
    digitalWrite(2, LOW);
    ledfadecount ++;
    break;
  case 6:
    digitalWrite(2, HIGH);
    ledfadecount ++;
    break;
  case 7:
    digitalWrite(2, LOW);
    if(led.active())led.detach();
    led.attach(3, ledBlinkThrice);
    ledfadecount = 0;
    break;

  default:
    ledfadecount = 0;
    break;
  }
}

void ledDimming(){
  ledfadecount += 10;
  analogWrite(2, ledfadecount);
}

void ledDimmingFast(){
  ledfadecount += 20;
  analogWrite(2, ledfadecount);
}
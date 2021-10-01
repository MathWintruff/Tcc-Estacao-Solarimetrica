#include <Arduino.h>

HardwareSerial LoraSerial(1);

void LoraStart(){
    LoraSerial.begin(115200, SERIAL_8N1, 16, 17);
}

void LoraRead(){
    if(LoraSerial.available()>0){
        delay(100);
        while (LoraSerial.available()>0)
        {
            char reading = LoraSerial.read();
            Serial.print(reading);
        }
    }
    
}

void LoraSendAndWaitResponse(String command){
    LoraRead();
    LoraSerial.println(command);
    while (LoraSerial.available() <= 0){};
    LoraRead();
}

void VerifyLoraCommand(){
    if(Serial.available()>0){
        delay(200);
        String SerialMessage = "";
        while (Serial.available()>0)
        {
            char reading = Serial.read();
            SerialMessage.concat(reading);
        }
        if(SerialMessage.substring(0,2) == "AT"){
            LoraSendAndWaitResponse(SerialMessage);
        }
    }
}

void LoraSendMessage(String message){
    String command = "AT+SEND=5:";
    command.concat(message);
    LoraSendAndWaitResponse(command);
}

void GetLoraInfo(){
    LoraRead();
    Serial.print("Dev EUI: ");
    LoraSendAndWaitResponse("AT+DEUI=?");
    Serial.print("Dev Addr: ");
    LoraSendAndWaitResponse("AT+DADDR=?");
    Serial.print("AppKey: ");
    LoraSendAndWaitResponse("AT+APPKEY=?");
    Serial.print("AppSKey: ");
    LoraSendAndWaitResponse("AT+APPSKEY=?");
    Serial.print("NwkSKey: ");
    LoraSendAndWaitResponse("AT+NWKSKEY=?");
    Serial.print("AppEui: ");
    LoraSendAndWaitResponse("AT+APPEUI=?");
    Serial.print("ADR: ");
    LoraSendAndWaitResponse("AT+ADR=?");
    Serial.print("DataRate: ");
    LoraSendAndWaitResponse("AT+DR=?");
    Serial.print("Confirmation enable: ");
    LoraSendAndWaitResponse("AT+CFM=?");
    Serial.print("Retrials count: ");
    LoraSendAndWaitResponse("AT+NBTRIALS=?");
    Serial.print("Ota enable: ");
    LoraSendAndWaitResponse("AT+NJM=?");
    Serial.print("Dev Class: ");
    LoraSendAndWaitResponse("AT+CLASS=?");
    Serial.print("Join Status: ");
    LoraSendAndWaitResponse("AT+NJS=?");
    
}
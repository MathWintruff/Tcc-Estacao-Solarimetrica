#include <Arduino.h>

HardwareSerial LoraSerial(1);

void LoraStart(){
    LoraSerial.begin(115200, SERIAL_8N1, 16, 17);
}

String LoraRead(boolean print){
    String SerialMessage = "";
    if(LoraSerial.available()>0){
        delay(100);
        while (LoraSerial.available()>0)
        {
            char reading = LoraSerial.read();
            SerialMessage.concat(reading);
        }
        if(print == true){
            Serial.print(SerialMessage);
        } 
        
    }
    return SerialMessage;
}

String LoraSendAndWaitResponse(String command){
    LoraRead(false);
    LoraSerial.println(command);
    while (LoraSerial.available() <= 0){};
    String response = LoraRead(true);
    return response;
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

void GetLoraInfoOnSerial(){
    LoraRead(false);
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

struct LoraInfo{
    String DEUI = "N/A";
    String DADDR = "N/A";
    String APPKEY = "N/A";
    String APPSKEY = "N/A";
    String NWKSKEY = "N/A";
    String APPEUI = "N/A";
    String ADR = "N/A";
    String DR = "N/A";
    String CFM = "N/A";
    String NBTRIALS = "N/A";
    String NJM = "N/A";
    String CLASS = "N/A";
    String NJS = "N/A";
};

LoraInfo GetLoraInfoForPage(){
    LoraInfo info;
    info.DEUI = LoraSendAndWaitResponse("AT+DEUI=?");
    info.DADDR = LoraSendAndWaitResponse("AT+DADDR=?");
    info.APPKEY = LoraSendAndWaitResponse("AT+APPKEY=?");
    info.APPSKEY = LoraSendAndWaitResponse("AT+APPSKEY=?");
    info.NWKSKEY = LoraSendAndWaitResponse("AT+NWKSKEY=?");
    info.APPEUI = LoraSendAndWaitResponse("AT+APPEUI=?");
    info.ADR = LoraSendAndWaitResponse("AT+ADR=?");
    info.DR = LoraSendAndWaitResponse("AT+DR=?");
    info.CFM = LoraSendAndWaitResponse("AT+CFM=?");
    info.NBTRIALS = LoraSendAndWaitResponse("AT+NBTRIALS=?");
    info.NJM = LoraSendAndWaitResponse("AT+NJM=?");
    info.CLASS = LoraSendAndWaitResponse("AT+CLASS=?");
    info.NJS = LoraSendAndWaitResponse("AT+NJS=?");

    return info;
}
#include <Arduino.h>

HardwareSerial LoraSerial(1);

void LoraStart(){
    LoraSerial.begin(115200, SERIAL_8N1, 16, 17);
}

String LoraRead(boolean print){
    String SerialMessage = "N/A";
    if(LoraSerial.available()>0){
        SerialMessage = "";
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
    int retryCount = 0;
    LoraSerial.println(command);
    while (LoraSerial.available() <= 0 && retryCount < 100){
        retryCount++;
        delay(20);
    };
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

String JoinNetwork(){
    int count = 0;
    LoraSendAndWaitResponse("AT+JOIN=?");
    while (count < 100){
        LoraRead(false) == "N/A" ? count++ : count = 0;
        delay(20);
    }
    return LoraSendAndWaitResponse("AT+NJS=?");
}

void GetInfoAndSendWithLora(){
    if(CheckIfSunIsPresentAndGetReading()){
      String batPercentage = String(GetBatteryData().percentage);
      String batVoltage = String(GetBatteryData().voltage);
      String temperature = String(GetTemperatureByVoltage());
      String angle = String(lastSunInclinationReading.angle);
      String current = String(lastSunInclinationReading.current);

      String loraDataToSend = batPercentage;
      loraDataToSend.concat("|");
      loraDataToSend.concat(batVoltage);
      loraDataToSend.concat("|");
      loraDataToSend.concat(temperature);
      loraDataToSend.concat("|");
      loraDataToSend.concat(angle);
      loraDataToSend.concat("|");
      loraDataToSend.concat(current);

      LoraSendMessage(loraDataToSend);
    }
}
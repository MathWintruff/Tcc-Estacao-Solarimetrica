#include <Arduino.h>

unsigned long timeOfLastAction = 0;

unsigned long CheckMillisFromLastAction(){
    unsigned long actualTime = millis();
    return (actualTime - timeOfLastAction);
}

bool CheckIfTimeHasPassed(unsigned long minutesToCheck){
    minutesToCheck = minutesToCheck * 60000;
    if((CheckMillisFromLastAction() >= minutesToCheck) || timeOfLastAction == 0){
        timeOfLastAction = millis();
        return true;
    }else{
        return false;
    }
}

String GetTimePassedFromLastAction(){
    unsigned long timePassed = CheckMillisFromLastAction();
    long minutes = timePassed/60000;
    long seconds = (timePassed % 60000) / 1000;
    String response = String(minutes);
    response.concat(":");
    response.concat(String(seconds));
    return response;
}

String GetTimePassedFromBoot(){
    unsigned long timePassed = millis();
    long minutes = timePassed/60000;
    long seconds = (timePassed % 60000) / 1000;
    String response = String(minutes);
    response.concat(":");
    response.concat(String(seconds));
    return response;
}
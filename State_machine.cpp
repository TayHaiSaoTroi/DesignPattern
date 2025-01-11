#include <iostream>


typedef enum State
{
    IDLE,
    NORMAL,
    HIGH_TEMP,
    ALARM
}State;

class Temperature
{
    private:
    State currentState;
    float temperature;
    float TEMP_THRESHOLD_HIGH = 35.0f;
    float TEM_THRESHODE_ALARM = 60.0f;
    bool fanOn;
    bool alarmOn;

    void displayLCD (float temp);
    void controlAlarm (bool state);
    void controlFan (bool state);
    void loop();
    public:
    Temperature();
    void changeState(float temp);
};

Temperature::Temperature()
{
    currentState =NORMAL;
    temperature = 0.0f;
    fanOn = false;
    alarmOn = false;
}

void Temperature::displayLCD(float temp)

{
    std::cout << "Temperature: "<<temp<<std::endl;
}

void Temperature::controlAlarm(bool state)

{
    alarmOn = state;
    std::cout<<"Alarm: " <<(alarmOn ? "ON":"OFF")<<std::endl;
}

void Temperature::controlFan(bool state)

{
    fanOn = state;
    std::cout<<"Fan: "<<(fanOn ? "ON":"OFF")<<std::endl;
}

void Temperature::loop()
{
    switch(currentState)
    {
        case IDLE:
        {
            std::cout<<"IDLE State..... wait temperature increment."<<std::endl;
            break;
        } 
        case NORMAL:
        {
            displayLCD(temperature);
            controlAlarm(false);
            controlFan(false);
            break;
        }
        case HIGH_TEMP:
        {
            displayLCD(temperature);
            controlFan(true);
            controlAlarm(false);
            break;
        }
        case ALARM:
        {
            displayLCD(temperature);
            controlFan(true);
            controlAlarm(true);
            break;
        }
        default:
        break;
    }
}

void Temperature::changeState(float temp)
{
    temperature = temp;
    switch (currentState)
    {
    case /* constant-expression */ IDLE:
        /* code */
        if(temperature > 20)
        currentState = NORMAL;
        break;
    case NORMAL:
    if (temperature > TEMP_THRESHOLD_HIGH)
    currentState = HIGH_TEMP;
    else if ( temperature > TEM_THRESHODE_ALARM)
    currentState = ALARM;
    break;

    case HIGH_TEMP:
    if (temperature < TEMP_THRESHOLD_HIGH)
    currentState = NORMAL;
    else if ( temperature > TEM_THRESHODE_ALARM)
    currentState = ALARM;
    break;

    case ALARM:
    if (temperature < TEM_THRESHODE_ALARM)
    currentState = HIGH_TEMP;
    else if (temperature < TEMP_THRESHOLD_HIGH)
    currentState = NORMAL;
    break;
    default:
    break;
    
    }
    loop();
}
int main(void)

{
    Temperature* tempSystem = new Temperature;
    float tempData[] = {10.0, 24.0, 32.0, 38.7, 41.8, 50.6, 62.3, 70.4, 80.5 };
    for (auto i:tempData)
    {
        std::cout << "Temperature: "<< i<<std::endl;
        tempSystem->changeState(i);
    }
    delete tempSystem;
}
#define RUN 0
#define TEST_INPUT 1
#define TEST_DISPLAY 2
#define TEST_LOGGER 3
#define TEST_THERMOMETER_WRAPPER 4
#define MODE 0


#if MODE == RUN
/// This is the actual implementation that should run on the thermometer
#include "AdvancedThermometerLogic.hpp"

AdvancedThermometerLogic *thermometerLogic;
Input *inputHandler;

void setup() {
    Serial.begin(115200);
    inputHandler = new Input(
            shortTriggerListener,
            longTriggerListener,
            laserClickListener,
            backgroundLightClickListener
    );

    thermometerLogic = new AdvancedThermometerLogic();
}

// listeners because std::bind is too fat for AVRs
void backgroundLightClickListener(bool activated) { thermometerLogic->onBackgroundLightToggled(activated); }
void laserClickListener(bool activated) { thermometerLogic->onLaserToggled(activated); }
void shortTriggerListener(bool activated) { thermometerLogic->onTriggerShortClick(activated); }
void longTriggerListener(bool activated) { thermometerLogic->onTriggerLongClick(activated); }

void loop() {
    inputHandler->update();
    thermometerLogic->update();
}
#elif MODE == TEST_INPUT
#include "Input.hpp"
Input *inputHandler;

void setup() {
    Serial.begin(115200);
    inputHandler = new Input(
            shortTriggerListener,
            longTriggerListener,
            laserClickListener,
            backgroundLightClickListener
    );
    Serial.println("init ok");
}

// listeners because std::bind is too fat for AVRs
void backgroundLightClickListener(bool activated) {
    Serial.print("background light clicked, activated: ");
    Serial.println(activated);
}

void laserClickListener(bool activated) {
    Serial.print("laser clicked, activated: ");
    Serial.println(activated);
}

void shortTriggerListener(bool activated) {
    Serial.print("trigger shortclicked, activated: ");
    Serial.println(activated);
}

void longTriggerListener(bool activated) {
    Serial.print("trigger longclicked, activated: ");
    Serial.println(activated);
}

void loop() {
    inputHandler->update();
}
#elif MODE == TEST_DISPLAY
#include "Display.hpp"

Display* display;
float example_data[] = {0, 1, 2, 3, 4, 501, 6, 7, 8, 9, 999};
float* example_data_full_res;

void setup(){
    display = new Display();

    Serial.begin(115200);
    Serial.print("graph horizontal resolution: ");
    Serial.println(display->getGraphHorizontalResolution());

    example_data_full_res = new float[display->getGraphHorizontalResolution()];
    for(size_t i = 0; i < display->getGraphHorizontalResolution(); i++){
        example_data_full_res[i] = i * i;
    }
}

void loop() {
    Serial.println("display indicators");
    display->update(example_data, 11, true, true, true);
    delay(1000);
    Serial.println("hide indicators");
    display->update(example_data, 11, false, false, false);
    delay(1000);
}
#elif MODE == TEST_LOGGER

#include "Logger.hpp"

void printBuffer(float *buffer, size_t length) {
    for (size_t i = 0; i < length; i++)
        Serial.println(buffer[i]);
    Serial.println("finished buffer printing");
}

void setup() {
    Serial.begin(115200);
    Logger::init();

    Serial.println("appending 1.1, 2.2, 3.3, 4.5 to log");

    long time_logger = millis();
    Logger::append(1);
    Logger::append(1);
    Logger::append(1);
    Logger::append(1);
    Serial.print("appending once took (ms): ");
    Serial.println(millis() - time_logger);

    //Logger::append(2.222);Logger::append(3.333);Logger::append(4.577);

    Serial.print("retrieving last value: ");
    float lastValue;
    Logger::getLastEntry(lastValue);
    Serial.println(lastValue);


    float buffer[10];
    bool success = true;

    Serial.println("retrieving 2 log items:");
    for (size_t i = 0; i < 10; i++) buffer[i] = 0;
    Logger::getLog(buffer, 2, success);
    printBuffer(buffer, 10);

    Serial.println("retrieving exactly the full log:");
    for (size_t i = 0; i < 10; i++) buffer[i] = 0;
    Logger::getLog(buffer, 4, success);
    printBuffer(buffer, 10);

    Serial.println("retrieving more than full log:");
    for (size_t i = 0; i < 10; i++) buffer[i] = 0;
    Logger::getLog(buffer, 12, success);
    printBuffer(buffer, 10);
}

void loop() {

}

#elif MODE == TEST_THERMOMETER_WRAPPER

#include "ThermometerWrapper.h"

Thermometer *thermometer;

void setup() {
    thermometer = new Thermometer();
    Serial.begin(115200);
}

void loop() {
    Serial.print("temperatur: ");
    Serial.println(thermometer->getTemperature());
    delay(1000);
}

#else
#error "INVALID OPERATION MODE"
#endif


#include <string>
#include <vector>
#include <iostream>
#include <obd-cxx/ObdCommand.hpp>
#include <obd-cxx/ObdSerial.hpp>
#include <obd-cxx/ParseConfig.hpp>
#define RPM "010C\r"
#define SPEED "010D\r"
#define FUEL "012F\r"
#define DTC "03\r"
#define SDTC "0902\r"
#define ODOMB "220F00\r"
#define ODO "22F100\r"
#define OIL "015C\r"
int main(int argc, char* argv[]){
    bool rpm, help, fuel, oiltemp, odometer, odoMB, dtc, storedDTC, speed = false;
    for(int i = 0; i < argc; i++){
        if(argv[i] == "h"){
            help = true;
        }
        if(argv[i] == "r"){
            rpm = true;
        }
        if(argv[i] == "f"){
            fuel = true;
        }
        if(argv[i] == "o"){
            oiltemp = true;
        }
        if(argv[i] == "odo") {
            odometer = true;
        }
        if(argv[i] == "dtc"){
            dtc = true;
        }
        if(argv[i] == "stdtc"){
            storedDTC = true;
        }
        if(argv[i] == "s"){
            speed = true;
        }
}
    if(argc == 1){
        std::cerr << "This Program requires Arguments." << std::endl;
        return -1;
    }
    if(help == true){
        std::cout << "[COBD2PP]" << std::endl
                  << "h - Displays this help\n"
                  << "r - Displays Real-Time RPM\n"
                  << "o - Displays Oil Temperature\n"
                  << "odo - Displays Odometer\n"
                  << "odoex - Displays Odometer for Mercedes-Benz Vehicles"
                  << "f - Displays Fuel Level\n"
                  << "dtc - Displays DTC's\n"
                  << "stdtc - Displays Stored DTC's\n"
                  << "s - Displays Real-Time Speed\n";
        return 10; // Exited with Help
    }   
    else if(argc > 1){
    while(true){
        ObdSerial serial("/dev/ttyUSB0");
        serial.openPort("/dev/ttyUSB0", 38400);
        
        if(rpm == true){
            ObdCommand cmd(&serial, "RPM", RPM, "((A*256)+B)/4");
            double rpm = cmd.run();
            std::cout << "\nRT Engine RPM: " << std::to_string(rpm) << std::endl;
        }
        if(speed == true) {
            ObdCommand cmd(&serial, "SPEED", SPEED, "A");
            int speed = cmd.run();
            std::cout << "RT Speed: " << std::to_string(speed) << std::endl;
        }
        if(fuel == true){
            ObdCommand cmd(&serial, "FUEL", FUEL, "(A*100)/255");
            float lvl = cmd.run();
            std::cout << "Fuel Level: " << std::to_string(lvl) << std::endl;
        }
        if(dtc == true){
            ObdCommand cmd(&serial, "DTC's", DTC, "");
            auto dtcs = cmd.run();
            std::cout << "DTC: " << std::to_string(dtcs) << std::endl;
        }
        if(storedDTC == true){
            ObdCommand cmd(&serial, "Stored DTC's", SDTC, "");
            auto sdtcs = cmd.run();
            std::cout << "Stored DTC's: " << std::to_string(sdtcs) << std::endl;
        }
        if(odometer == true){
            ObdCommand cmd(&serial, "ODOMETER", ODO, "(A*256)+B");
            auto odo = cmd.run();
            std::cout << "Odometer: " << std::to_string(odo) << std::endl;
        }
        if(oiltemp == true){
            ObdCommand cmd(&serial, "Oil Temperature", OIL, "A-40");
            auto oiltempValue = cmd.run();
            std::cout << "Oil Temperature: " << std::to_string(oiltempValue) << std::endl;
        }
    }



    }
    return 0;
}
#include "driver.h"
 
matidigo::drivers::Driver::Driver() {
}

matidigo::drivers::Driver::~Driver() {
}
        
void matidigo::drivers::Driver::Activate() {
}

int matidigo::drivers::Driver::Reset() {
    return 0;
}

void matidigo::drivers::Driver::Deactivate() {
}

matidigo::drivers::DriverManager::DriverManager()
{
    numDrivers = 0;
}

void matidigo::drivers::DriverManager::AddDriver(Driver* drv)
{
    drivers[numDrivers] = drv;
    numDrivers++;
}

void matidigo::drivers::DriverManager::ActivateAll()
{
    for(int i = 0; i < this->numDrivers; i++)
        this->drivers[i]->Activate();
}
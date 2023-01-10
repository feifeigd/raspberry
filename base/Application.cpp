#include "Application.h"


using base::Application;


int Application::setup(){
    return wiringPiSetup();
}

 #include "application.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    Application app;
    app.init();
    return app.exec();
}

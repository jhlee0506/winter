#include <stdarg.h>
#include <stdio.h>

#include "winter_application.h"


int main(int argc, char* argv[])
{
    struct winter_application* app = winter_application_create(argc, argv);
    assert(app);
}
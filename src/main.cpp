#include <iostream>

#include "system/modal.h"

int main(int argc, char *argv[])
{
    std::cout << "hello" << std::endl;

    windfall::system::modal::ShowErrorMessage("title", "message");
    windfall::system::modal::ShowErrorMessage("title", "message", "quotation");

    return 0;
}

#include "bank.h"
#include "atm.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./run_atm <path_to_csv>" << std::endl;
        return -1;
    }

    Bank mBank("Test Bank");
    mBank.populateDatabase(argv[1]);


    atm_controller::ATM mATM(mBank, "00001");

    mATM.readCard();
    
    if (!mATM.authenticate())
    {
        return -1;
    }
    
    mATM.makeTransaction();
}
#include "bank.h"

#include <iostream>

int main(int argc, char** argv)
{
    Bank mBank("Test Bank");
    mBank.addUser(Card("001", "John Doe", "01/01/2025"), "1234", SavingAccount("0001", 500));
    mBank.addUser(Card("002", "Mary Smith", "01/01/2025"), "4321", CheckingAccount("0002", 1000));
    mBank.addUser(Card("003", "Tri Khuu", "01/01/2025"), "6789", CheckingAccount("0003", 1500));

    unsigned int balance;
    if (mBank.viewBalance(Card("003", "Tri Khuu", "01/01/2025"), CheckingAccount("0003", 1500), balance))
        std::cout << balance << std::endl;

    mBank.deposit(Card("003", "Tri Khuu", "01/01/2025"), CheckingAccount("0003", 1500), 500);
    if (mBank.viewBalance(Card("003", "Tri Khuu", "01/01/2025"), CheckingAccount("0003", 1500), balance))
        std::cout << balance << std::endl;

    // ATM mATM(mBank, "00001");

    // mATM.readCard();
    
    // if (!mATM.authenticate())
    // {
    //     return -1;
    // }
    
    // mATM.makeTransaction();
}
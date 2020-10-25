#pragma once

#include "bank.h"

namespace atm_controller
{

enum Transaction
{
    WITHDRAWAL,
    DEPOSIT,
    BALANCE,
    EXIT
};

// enum AuthenticationStatus
// {
//     SUCCESS,
//     INVALID_PIN
// };

// enum TransactionStatus
// {
//     SUCCESS,
//     FAIL
// };



/**
 * CardReader is the class that should be integrated with hardware to read info from the physical card
 */
class CardReader
{
    Card cardRead_;
    public:
    CardReader() : cardRead_(){}
    /**
     * This function should instruct the hardware to scan read the information of the card
     * SInce we do not have hardware, this function will serve as a place holder and will generate Card instances for testing
     */
    void readCard();
    void clearCardRead() {cardRead_ = Card();}
    Card getReadCard() const {return cardRead_;}
};

class KeyPad
{
    public:
    string getStringInput(const std::string& messageToUser);
    unsigned int getDigitInput(const string& messageToUser);
};

class CashSlot
{
    public:
    void dispense(const unsigned int& amount) {std::cout << "====> Dispensing " << amount << " dollars\n" << std::endl;}
};

class ATM
{
private:
std::string id_;
CardReader cardReader_;
KeyPad keypad_;
CashSlot cashSlot_;
Bank bank_;

Account _selectAccount(const Card& card);
Transaction _selectTransaction();

public:
ATM(const Bank& bank, const std::string& atmId);
void readCard();
bool authenticate();
bool makeTransaction();

};

}
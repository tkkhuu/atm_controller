# Dependencies

* CMake

# Build Instructions

Clone the project:
```
$ git clone https://github.com/tkkhuu/atm_controller.git
```

From the project directory, create a build directory for CMake to build the code:
```
$ cd atm_controller
$ mkdir -p build/cmake
$ cd build/cmake
$ cmake ../..
$ make
```

# Run Instructions

An executable ```run_atm``` is generated after the build within the ```build/cmake``` directory

Simply run:

```
$ ./run_atm <path_to_bank_database.json>

# For example:
$ ./run_atm ../../data/bank_database.json
```

The bank will populate its internal database from the contents of the CSV file. The format of the CSV file is the following:
```
CardNumber,FirstName,LastName,ExpDate,PIN,AccountNumber,AccountType,AccountBalance
```

Once you run the program, simply follow the prompted instructions, since we do not have the card reader hardware, the program will prompt you to enter your card information instead.

# Implementation
## ATM Class
The ATM class has 3 main functions to support the basic ATM functionalities:

1. Read Card Info
2. Authenticate with PIN number
3. Make Transactions: View Balance, Deposit, Withdraw

```
void readCard();
bool authenticate();
bool makeTransaction();
```

Placeholder classes for interfacing with hardware are also created:
```
KeyPad
CardReader
CashSlot
```

A class ```Bank``` was created to acts as a placeholder for the Bank API when integrating with a real bank

## Bank Class

This is the placeholder for the Bank API for the ATM to interact with a real bank

The Bank stores the following information:
1. Card Info: which was implemented as the class ```Card```, and is used to look up stored PIN info and associated accounts
2. PIN Number: which was implemented as a string
3. Accounts: A list of ```Account``` associated with the card, there are 2 types of accounts ```CheckingAccount``` and ```SavingAccount```, where the actual differences are not implemented in the scope of this program, but are separated as 2 classes for future iterations.

The main functions from the banks are:
```
bool addUser(const Card& card, string pinNumber, const Account& account);
bool populateDatabase(const string& databaseFilePath);
bool verifyPin(const Card& card, const string& pinNumber);
vector<Account> lookUpAccounts(const Card& card);
bool deposit(const Card& card, const Account& account, const unsigned int& amount);
bool withdraw(const Card& card, const Account& account, const unsigned int& amount);
bool viewBalance(const Card& card, const Account& account, unsigned int& balance);
```
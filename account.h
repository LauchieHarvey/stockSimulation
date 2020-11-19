#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

typedef struct Account {
    // The total number of stocks that the account owns.
    unsigned int numStocksHeld;
    // The value of the cash that the account owns.
    double cashValue;
} Account;

// ACCOUNT FUNCTIONS =========================================================

// Instantiate an account struct.
void new_account(Account* account, int initialNumStocks,
	double initialCashValue);

// Buy or sell stocks. If buy, the num of stocks is +ve, -ve if selling.
int exchange_stocks(Account* account, double stockPrice, int numStocks);


#endif

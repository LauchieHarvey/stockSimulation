// This file handles all information relevent to an "account" of stock holdings
// including buying, selling and tracking its performance.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

// Instantiate the account struct.
Account* new_account(double initialCashVal) {
    Account* account = malloc(sizeof(Account)); 
    account->numStocksHeld = 0;
    account->cashValue = initialCashVal;
    return account;
}

// Buy or sell stocks. If buy, the num of stocks is +ve, -ve if selling.
// Returns: 0 on success,
//          1 on not enough cash to buy requested numStocks.
//	   -1 on not enough stocks to sell requested numStocks. 
int exchange_stocks(Account* account, double stockPrice, int numStocks) {

    double transactionValue = numStocks * stockPrice;
    // If they are buying then make the cash transaction negative.
    transactionValue *= (numStocks > 0) ? -1 : 1;
    int returnVal = 0;

    // If the account doesn't have enough cash in the account to afford all of
    // the stocks then buy as many as possible
    if ((numStocks > 0) && (transactionValue > account->cashValue)) {
	numStocks = (int)floor(account->cashValue / stockPrice);
	transactionValue = -1 * (double)numStocks * stockPrice;
	returnVal = 1;

    // Can't sell more stocks than the account has. Sell as many as possible.
    } else if (numStocks < 0 && -numStocks > account->numStocksHeld) {
	transactionValue = account->numStocksHeld * stockPrice;
	numStocks = -account->numStocksHeld;
	returnVal = -1;
    }

    // Make the transaction. This code is agnostic to buying or selling.
    account->cashValue += transactionValue;
    account->numStocksHeld += numStocks;
    return returnVal;
}

// StrategyFn function for the buy and hold strategy
// Buy as many stocks as possible, as soon as possible.
void buy_and_hold(Account* account, double stockPrice) {
    int maxNumStocks = (int)floor(account->cashValue / stockPrice);
    exchange_stocks(account, stockPrice, maxNumStocks); 
}

// StrategyFn function for the dollar cost average strategy 
void dollar_cost_avg(Account* account, double stockPrice) {
   return; 
} 

// Releases memory reserved for the account struct back to heap
void free_account(Account* account) {
    free(account);
    return;
}

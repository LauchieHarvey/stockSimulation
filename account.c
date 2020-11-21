// This file handles all information relevent to an "account" of stock holdings
// including buying, selling and tracking its performance.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

// Instantiate a new account.
void new_account(Account* account, int initialNumStocks,
	double initialCashValue) {
    
    account->cashValue = initialNumStocks;
    account->numStocksHeld = initialNumStocks;
}

// Buy or sell stocks. If buy, the num of stocks is +ve, -ve if selling.
// Returns: 0 on success,
//          1 on not enough cash to buy requested numStocks.
//	   -1 on not enough stocks to sell requested numStocks. 
int exchange_stocks(Account* account, double stockPrice, int numStocks) {

    double transactionValue = numStocks * stockPrice;
    int returnVal = 0;

    // If the account doesn't have enough cash in the account to afford all of
    // the stocks then buy as many as possible
    if ((numStocks > 0) && (transactionValue > account->cashValue)) {
	numStocks = (int)floor(account->cashValue / stockPrice);
	transactionValue = (double)numStocks * stockPrice;
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
void buy_and_hold(Account* account, Stock* stock) {
   return; 
}

// StrategyFn function for the dollar cost average strategy 
void dollar_cost_avg(Account* account, Stock* stock) {
   return; 
} 

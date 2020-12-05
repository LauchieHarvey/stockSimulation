#ifndef __MAIN_H__
#define __MAIN_H__

#include "stack.h"

typedef enum Colour {
    RED, GREEN, DEFAULT
} Colour;

typedef struct Stock {
    // An array of daily stock prices.
    double* prices;
    // Higher volatility factor will result in more drastic 
    // day to day price fluctuations
    int volatilityFactor;

} Stock;

typedef struct Account {
    // The total number of stocks that the account owns.
    unsigned int numStocksHeld;
    // The value of the cash that the account owns.
    double cashValue;
} Account;


// Function pointer definition for buy/sell strategies
typedef void (*StrategyFn)(Account*, double stockPrice, int dayNum);

// The struct that hold the arguments given to the programme.
typedef struct Args {
    // The buy/sell strategy that the account will use.
    StrategyFn strategyFn;
    // Number of months that the simulation should run for.
    int numMonths;
    // The initial price of the stock. Has to be > 0.   
    double initialStockPrice;
    // The initial amount of cash that the account holds.
    double initialCashValue;
    // The stack that contains all of the total account values after each sim
    Stack* stack;

} Args;

// FUNCTION DEFS =============================================================

// Threaded function to run the simulation
void* run_simulation(void* voidArgs);

// Instantiate an account struct.
Account* new_account(double initialCashVal);

// Buy or sell stocks. If buy, the num of stocks is +ve, -ve if selling.
int exchange_stocks(Account* account, double stockPrice, int numStocks);

void buy_and_hold(Account* account, double stockPrice, int dayNum);

void dollar_cost_avg(Account* account, double stockPrice, int dayNum);

void free_account(Account* account);

// Command Line Argument parsing functions. 

StrategyFn str_to_stratFn(char* arg);

double str_to_double(char* arg);

int str_to_int(char* arg);

#endif

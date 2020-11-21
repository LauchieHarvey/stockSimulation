#ifndef __MAIN_H__
#define __MAIN_H__

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
typedef void (*StrategyFn)(Account*, Stock*);

// The struct that hold the arguments given to the programme.
typedef struct Args {
    // The buy/sell strategy that the account will use.
    StrategyFn strategyFn;
    // Number of months that the simulation should run for.
    int numMonths;
    // The initial price of the stock. Has to be > 0.   
    double initialStockPrice;

} Args;

// FUNCTION DEFS =============================================================

// Threaded function to run the simulation
void* run_simulation(Args args);

// Instantiate an account struct.
void new_account(Account* account, int initialNumStocks,
	double initialCashValue);

// Buy or sell stocks. If buy, the num of stocks is +ve, -ve if selling.
int exchange_stocks(Account* account, double stockPrice, int numStocks);

void buy_and_hold(Account* account, Stock* stock);

void dollar_cost_avg(Account* account, Stock* stock);

// Command Line Argument parsing functions. 

StrategyFn str_to_stratFn(char* arg);

double str_to_double(char* arg);

int str_to_int(char* arg);

#endif

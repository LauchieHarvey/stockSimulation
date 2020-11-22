// Monte Carlo simulation of stock price to determine optimal buy/sell strategies.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "main.h"

// Generates pseudo random int between the specified bounds skewed towards lower
// numbers to reduce volatility
double generate_rand_num(double min, double max) {

    // Random number between the max and the min
    double randNum = ((double)rand() / RAND_MAX * (max - min)) + min;

    // Multiply randNum by scale factor (between 0 & 1) to reduce the
    // likelihood of extreme values.
    double randNum2 = (double)rand() / RAND_MAX;
    // y = (2x - 1)^4
    double scaleFactor = pow((2 * randNum2 - 1), 4);
	
    return randNum * scaleFactor; 
}

// Pseudo randomly generate the stock price for the specified day.
void calculate_next_price(Stock* stock, double dpMonth, int dayNum) {

    // random number between 8 & -8 with avg of 8% per year
    double randomPercentChange = generate_rand_num(-8, 8);
    // New price multiple is random plus the average daily change over the last month
    double newPriceMultiple = 1 + (randomPercentChange + 
	(dpMonth / stock->prices[dayNum - 1]) / 1000.0) / 100;

    stock->prices[dayNum] = stock->prices[dayNum - 1] * newPriceMultiple;
    printf("Day %i: %f\n", dayNum, stock->prices[dayNum]);
}

// Returns the change in the stock price over the specified num of days.
double get_price_change(Stock stock, int currDayNum, int numOfDays) {

    int trailingDayNum = currDayNum - numOfDays;
    int monthAgoIndex = trailingDayNum > 0 ? trailingDayNum : 0;

    return stock.prices[currDayNum - 1] - stock.prices[monthAgoIndex];
}

// Runs the simulation of the stock for the specified number of months.
void simulate_stock_price(Stock* stock, int numOfMonths, int dayNum) { 

    double dpMonth = get_price_change(*stock, dayNum, 30);
    printf("dpM: %f\n", dpMonth);
    calculate_next_price(stock, dpMonth, dayNum);	 
}

// Runs the simulation of the stock and handles all of the accounts.
// Will run in its own thread eventually.
void* run_simulation(Args args) {
    int numDays = args.numMonths * 365 / 12;
    Stock stock;
    stock.prices = malloc(sizeof(double) * numDays);
    stock.prices[0] = args.initialStockPrice;

    Account account;
    account.cashValue = args.initialCashValue;

    for (int dayNum = 1; dayNum < numDays; ++dayNum) {
	// The account decides how much to buy, sell and hold.
	args.strategyFn(&account, stock.prices[dayNum - 1]);
	// Update the stock price for the next day.
        simulate_stock_price(&stock, args.numMonths, dayNum);
    }

    return (void*)(0);
}

// Error that handles incorrect usage of the programme.
void usage_err() {
    fprintf(stderr, "Usage: ./runSim strategy numMonths initialStockPrice \
	    initialCashValue\n");
    fprintf(stderr, "strategy:\n    0 = buy and hold\n    1 = dollar cost avg\n");
    fprintf(stderr, "numMonths: int > 0\n");
    fprintf(stderr, "initialStockPrice: double > 0\n");
    fprintf(stderr, "initialCashValue: double > 0\n");
    exit(1);
}

// Exits with appropriate error message if there is invalid command line args.
void parse_args(Args* args, int argc, char** argv) {
    if (argc != 5) {
	usage_err();
    }
    // Convert argv[1] to StrategyFn and store in args->strategyFn
    args->strategyFn = str_to_stratFn(argv[1]);
    // Convert argv[2] to int and store in args->numMonths
    args->numMonths = str_to_int(argv[2]);
    if (args->numMonths < 0) {
	fprintf(stderr, "The number of months must be a positive integer.\n");
	exit(3);
    }
    // Convert argv[3] to double and store in args->initialStockPrice
    args->initialStockPrice = str_to_double(argv[3]);    
    if (args->initialStockPrice < 0) { 
	fprintf(stderr, "The initial stock price must be a positive number.\n");
	exit(4);
    }
    // Convert argv[4] to double and store in args->initialCashValue
    args->initialCashValue = str_to_double(argv[3]);    
    if (args->initialCashValue < 0) { 
	fprintf(stderr, "The initial cash value must be a positive number.\n");
	exit(5);
    }
}

// Converts a string to a double. Returns -1.0 if there is an
// error parsing the string.
double str_to_double(char* rawDoubleArg) {
    double resultDouble;
    char* superfluous = ""; 
    
    resultDouble = strtod(rawDoubleArg, &superfluous);
    if (!rawDoubleArg || strcmp(superfluous, "")) {
	return -1.0;
    }
    return resultDouble;
}

// Convert the command line argument integer to the corresponding 
// buy/sell strategy function pointer.
StrategyFn str_to_stratFn(char* rawStrategyArg) {
    if (!strcmp(rawStrategyArg, "0")) {
	return buy_and_hold;
    } else if (!strcmp(rawStrategyArg, "1")) {
	return dollar_cost_avg;
    }	
    fprintf(stderr, "Invalid buy/sell strategy number provided.\n");
    fprintf(stderr, "strategy:\n    0 = buy and hold\n    1 = dollar cost avg\n");
    exit(2);
}

// Returns -1 if there was an error reading the string as an integer.
int str_to_int(char* rawIntArg) {
    int resultInt;
    char* superfluous = ""; 
    
    resultInt = strtol(rawIntArg, &superfluous, 10);
    if (!rawIntArg || strcmp(superfluous, "")) {
	return -1;
    }
    return resultInt;
}

int main(int argc, char** argv) {

    // Set pseudo-random seed
    srand(time(NULL));

    Args args;
    parse_args(&args, argc, argv);
    run_simulation(args);

   return 0;
}

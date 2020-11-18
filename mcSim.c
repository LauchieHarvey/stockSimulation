// Monte Carlo simulation of stock price to determine optimal buy/sell strategies.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "mcSim.h"

// Generates pseudo random int between the specified bounds skewed towards lower
// numbers to reduce volatility
double generate_rand_num(double min, double max) {

    // Random number between the max and the min
    double randNum = ((double)rand() / RAND_MAX * (max - min)) + min;

    // Multiply randNum by scale factor (between 0 & 1) to reduce the
    // likelihood of extreme values. (2x - 1)^2
    double randNum2 = (double)rand() / RAND_MAX;
    double scaleFactor = (2 * randNum2 - 1) * (2 * randNum2 - 1);
	
    return randNum * scaleFactor; 
}

// Pseudo randomly generate the stock price for the specified day.
void calculate_next_price(Stock* stock, double dpMonth, int dayNum) {

    stock->prices = realloc(stock->prices, sizeof(double) * (dayNum + 1));
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
void simulate_stock_price(Stock* stock, int numOfMonths) {
    int numOfDays = numOfMonths * 365 / 12;  

    int startingStockPrice = 100;
    stock->prices = malloc(sizeof(double));
    stock->prices[0] = startingStockPrice;
    
    for (int dayNum = 1; dayNum < numOfDays; ++dayNum) {
	double dpMonth = get_price_change(*stock, dayNum, 30);
	printf("dpM: %f\n", dpMonth);
	calculate_next_price(stock, dpMonth, dayNum);	
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
	fprintf(stderr, "Usage: ./stockAnalysis numOfMonths volitilityFactor\n");
	exit(1);
    }
    Stock stock;
    srand(time(NULL));
    // Simulate the stock price over time (months)
    //simulate_stock_price(&stock, 1);
    // Simulate how a certain strategy would have performed on this stock.
    simulate_stock_price(&stock, 1); 

    return 0;
}

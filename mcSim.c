// Monte Carlo simulation of stock price to determine optimal buy/sell strategies.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mcSim.h"

void calculate_next_price(Stock* stock, double dpMonth, int dayNum) {

    stock->prices = realloc(stock->prices, sizeof(double) * (dayNum + 1));
    // random number between 1.1 & 0.93
    double randomNum = 1 + ((rand() % 18) - 7) / (double)100;
    double newPriceMultiple = randomNum + 0.1 * 
	(dpMonth / stock->prices[dayNum - 1]);

    stock->prices[dayNum] = stock->prices[dayNum - 1] * newPriceMultiple;
    printf("Day %i: %f\n", dayNum, stock->prices[dayNum]);
}

// Returns the change in the stock price over the specified num of days.
double get_price_change(Stock stock, int currDayNum, int numOfDays) {
    int monthAgoIndex = (currDayNum - numOfDays) > 0 ? 
	(currDayNum - numOfDays) : 0;

    return stock.prices[currDayNum - 1] - stock.prices[monthAgoIndex];
}

// Runs the simulation of the stock for the specified number of months.
void simulate_stock_price(Stock* stock, int numOfMonths) {
    int numOfDays = round(numOfMonths * 365/12);  

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
    simulate_stock_price(&stock, 1);
    return 0;
}

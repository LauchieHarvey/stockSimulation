// Monte Carlo simulation of stock price to determine optimal buy/sell strategies.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "mcSim.h"

// Generates pseudo random int between the specified bounds based of a 
// normal distribution around the mode argument.
double generate_normal_dist_num(double min, double max, double mean) {

    // Random number between the max and the min
    double randNum = ((double)rand() / RAND_MAX * (max - min)) + min;

    // Multiply randNum by scale factor (between 0 & 1) to reduce the
    // likelihood of extreme values. Slightly skewed towards 0. (2x - 1)^2
    double randNum2 = (double)rand() / RAND_MAX;
    double scaleFactor = (2 * randNum2 - 1) * (2 * randNum2 - 1);
	
    return randNum * scaleFactor; 
}

// Pseudo randomly generate the stock price for the specified day.
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
    for (int i = 0; i < 6; i++) {
        double rndNum = generate_normal_dist_num(-5, 5, 1);
	printf("Normal: %f\n", rndNum);
    }

    return 0;
}

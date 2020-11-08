#ifndef MC_SIM_H
#define MC_SIM_H

typedef struct Stock {
    // An array of daily stock prices.
    double* prices;
    // Higher volatility factor will result in more drastic 
    // day to day price fluctuations
    int volatilityFactor;

} Stock;

#endif

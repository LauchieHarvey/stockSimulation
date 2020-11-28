# stockSimulation
![Image unavailable](https://images.unsplash.com/photo-1534951009808-766178b47a4f?ixlib=rb-1.2.1&ixid=MXwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHw%3D&auto=format&fit=crop&w=1350&q=80)
## What is it?
This is a monte carlo simulation of stock prices and investment performance.  
It has been created to help to determine optimal buy/sell investment strategies.

## How it works
### The simulation of the stock price
The change in the stock price will be determined as a function of its recent 
changes and pseudo-randomness (random numbers). A stock thats price recently 
dropped by a lot is more likely to drop further in price than a stock that 
has been stable or increasing. This allows the simulation to mimick the effect of 
the stock market where it goes through periods of rallies and corrections (ups and downs). 

### The code
It is written in C. Runs the simulation concurrently with threading. Any contributions are much appreciated!

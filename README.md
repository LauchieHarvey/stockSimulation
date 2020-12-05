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

## Getting Started
### 1. Download the program and run it on your device.
- Note that this will only run on a linux operating system. If you are using windows, you will need to run it through [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
- See the most recent version [here](https://github.com/LauchieHarvey/stockSimulation/releases)
- Click on 'Assets' to reveal the available downloads.
- Download the programme by clicking on `runSim`.
### 2. Setting the programme up.
- You will need to give the programme appropriate executable permissions for it to run. Once you have downloaded it, run the following command:
`chmod +x runSim`
### 3. Using the programme.
- For usage information run the program without any command line arguments as such:
`./runSim`
This will display the necessary command line argument for the simulation to work.
- The general format for running the programme is:
`./runSim strategy numMonths initialStockPrice initialCashValue`

#### Command line arguments:
- `strategy` must be an integer (whole number)
  - 0 = buy and hold. Buy as much as possible, as often as possible. 
  - 1 = dollar cost average. Buy once a week until you run out of cash. 
- `numMonths` must be an integer (whole number). If you want the simulation to run over a period of two years, then `numMonths` will be 24 (12 months/year x 2 years)
- `initialStockPrice` must be a number above 0 (can be a decimal/double number)
- `initialCashValue` is the amount of cash that the account starts with (positive number). It helps regulate buy and sell strategies to simulate an individual investor following the strategy.  
  
### The code
It is written in C. Runs the simulation concurrently with threading. Any contributions are much appreciated!

The main purpose of this project was to learn C++ while also learning a bit about the orderbook and how markets work in general. I've messed around with number of shares, starting price, how traders decide whether to buy/sell, what price and quantity they put these orders on with, etc. to find something that works best. 

The project started with incredibly inefficient and buggy code. Some changes:
- had to traverse the trees each time it wanted to find the buy and sell prices, even longer if the full order book wanted to be inspected: fixed this
- Added automated tests so that any changes I made ensured nothing got completely broken.
- buy and sell prices could end up crossing as the orders were not really checked (matching only really occured on a buy or sell order that matched perfectly)

I know it's not the most maintainable/readable code: this was literally a summer project to teach myself the language.

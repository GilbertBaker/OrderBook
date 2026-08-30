# C++ Limit Order Book & Market Simulator

A from-scratch limit order book and market simulation written in **C++20**. The project models how buy and sell orders interact in an exchange-style matching engine, including **price-time priority, partial fills, market orders, limit orders, trader balances, and holdings**.

I built this project to learn modern C++ through a systems-style problem where data-structure choices directly affect behaviour and performance.

## What it does

- Maintains separate **bid** and **ask** books organised by price.
- Matches incoming limit orders against the best available opposing price.
- Supports **partial fills** when order quantities differ.
- Preserves **FIFO priority within a price level**.
- Supports market-style orders that consume the best available liquidity.
- Updates each trader's cash balance and share holdings after every trade.
- Simulates a population of traders generating buy and sell activity.
- Prints the best levels of the book and a simple midpoint price during the simulation.

## Matching behaviour

For a buy limit order:

1. Inspect the lowest-priced sell order (best ask).
2. Trade while the ask price is less than or equal to the buyer's limit price.
3. Fill the smaller of the incoming and resting quantities.
4. Remove fully filled resting orders.
5. Add any unfilled remainder to the bid book.

Sell orders use the symmetric process against the highest bid.

Orders at the same price are stored in insertion order, giving earlier orders priority over later orders at that price.

## Data structures

The order book is implemented without relying on a pre-built exchange/order-book library.

- **`OrderTree`** — binary search tree keyed by price.
- **`OrderList`** — linked FIFO queue for orders at the same price.
- **`OrderBook`** — matching engine coordinating bids, asks, fills, and account updates.
- **`Trader` / `TraderAlgo`** — simple market simulation that generates order flow across multiple traders.

This structure separates **price priority** (tree ordering) from **time priority** (FIFO ordering inside each price level).

## Project structure

```text
.
├── DataStructures/
│   ├── OrderBook.*      # Matching engine and bid/ask books
│   ├── OrderTree.*      # Price-indexed binary search tree
│   ├── OrderList.*      # FIFO queue at each price level
│   └── OrdListNode.*
├── Traders/
│   ├── Trader.*         # Trader state and order generation
│   └── TraderAlgo.*     # Multi-trader simulation coordinator
├── Order.*              # Order representation
├── main.cpp             # Simulation entry point
└── CMakeLists.txt
```

## Build and run

Requires a compiler with **C++20** support.

```bash
g++ -std=c++20 -O2 \
  main.cpp Order.cpp \
  DataStructures/OrderTree.cpp \
  DataStructures/OrdListNode.cpp \
  DataStructures/OrderList.cpp \
  DataStructures/OrderBook.cpp \
  Traders/Trader.cpp \
  Traders/TraderAlgo.cpp \
  -o orderbook

./orderbook
```

## Example output

```text
1005

SELLS:
1010 x 10000
BUYS:
1000 x 100
```

The simulation repeatedly updates traders, executes any crossed orders, and displays the current midpoint and top levels of the book.

## Engineering decisions

A few parts of the implementation were deliberately built manually as a learning exercise:

- A custom binary search tree is used to organise price levels.
- A custom linked queue preserves arrival order at each price.
- Matching is performed incrementally, so a single incoming order can execute against multiple resting orders.
- Trading updates both sides of the transaction, keeping cash and share ownership consistent with each fill.

The current tree is **not self-balancing**, so performance can degrade for unfavourable insertion orders. That is one of the main areas I would improve in a production-oriented version.

## Next improvements

The next iteration would focus on turning the prototype into a more robust matching-engine project:

- Add a comprehensive automated test suite for matching, partial fills, FIFO priority, empty books, and crossed markets.
- Replace raw owning pointers with RAII (`std::unique_ptr`) and define clear object ownership.
- Replace or rebalance the current BST to guarantee predictable lookup/insertion performance.
- Add order cancellation and modification by order ID.
- Add deterministic simulation seeds so runs can be reproduced.
- Add benchmarks for order insertion, matching throughput, and best-price lookup.
- Separate the matching engine from the trader simulation so the core book can be tested independently.
- Add assertions/invariants such as non-negative quantities and conservation of shares/cash where appropriate.

## Scope

This is an educational exchange simulation rather than a production trading system. Its purpose is to demonstrate C++ implementation, data-structure design, matching logic, and iterative systems engineering on a concrete problem.

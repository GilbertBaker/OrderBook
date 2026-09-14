#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>

#include "DataStructures/OrderBook.h"
#include "Traders/TraderAlgo.h"
#include "Traders/Trader.h"
#include "Order.h"


struct Fixture {
    OrderBook book;
    TraderAlgo algo;

    Fixture() : book(), algo(&book) {
        book.algo = &algo;

        // Prevent the benchmark from being limited by
        // trader cash/inventory rather than the order book.
        for (int i = 0; i < 100; ++i) {
            Trader* trader = algo.getTrader(i);
            trader->money = 1'000'000'000;
            trader->qOwned = 1'000'000'000;
        }
    }
};


void printResult(
    const char* name,
    std::size_t orders,
    double seconds
) {
    double ordersPerSecond =
        static_cast<double>(orders) / seconds;

    double nanosecondsPerOrder =
        seconds * 1'000'000'000.0 /
        static_cast<double>(orders);

    std::cout << name << '\n';
    std::cout << "  Orders:       " << orders << '\n';
    std::cout << "  Time:         "
              << std::fixed << std::setprecision(6)
              << seconds << " s\n";

    std::cout << "  Orders/sec:   "
              << std::setprecision(2)
              << ordersPerSecond << '\n';

    std::cout << "  ns/order:     "
              << nanosecondsPerOrder << "\n\n";
}


/*
 * Measures insertion into the price tree and FIFO lists.
 *
 * Orders don't cross, so this isolates insertion performance.
 */
void benchmarkInsertion(std::size_t n) {
    Fixture f;

    const auto start =
        std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < n; ++i) {
        // 100 different price levels.
        int price =
            800 + static_cast<int>(i % 100);

        Order* order = new Order(
            price,
            1,
            0,
            1,
            f.algo.getNextID(),
            true
        );

        f.book.placeBuyOrder(order);
    }

    const auto end =
        std::chrono::steady_clock::now();

    double seconds =
        std::chrono::duration<double>(
            end - start
        ).count();

    printResult(
        "Resting-order insertion",
        n,
        seconds
    );
}


/*
 * Measures actual matching.
 *
 * Seed a small ask book and repeatedly send market buys.
 * The ask book is replenished when empty.
 */
void benchmarkMatching(std::size_t n) {
    Fixture f;

    constexpr int levels = 100;
    constexpr int quantityPerOrder = 100;

    auto addLiquidity = [&]() {
        for (int level = 0; level < levels; ++level) {
            Order* order = new Order(
                1000 + level,
                quantityPerOrder,
                0,
                1 + (level % 99),
                f.algo.getNextID(),
                false
            );

            f.book.placeSellOrder(order);
        }
    };

    addLiquidity();

    const auto start =
        std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < n; ++i) {
        if (f.book.getBestAsk() < 0) {
            addLiquidity();
        }

        int traderID =
            1 + static_cast<int>(i % 99);

        f.book.placeBuyInstantOrder(
            1,
            traderID
        );
    }

    const auto end =
        std::chrono::steady_clock::now();

    double seconds =
        std::chrono::duration<double>(
            end - start
        ).count();

    printResult(
        "Market-order matching",
        n,
        seconds
    );
}


int main() {
    constexpr std::size_t N = 1'000'000;

    std::cout << "C++ Limit Order Book Benchmark\n\n";

    benchmarkInsertion(N);
    benchmarkMatching(N);

    return 0;
}
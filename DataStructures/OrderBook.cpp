//
// Created by Gilbe on 17/08/2026.
//
#include <chrono>
#include <algorithm>
#include "OrderBook.h"
#include "../Traders/TraderAlgo.h"
#include "../Traders/Trader.h"
using namespace std::chrono;
void OrderBook::placeBuyOrder(Order* order) {
    int q = order->quantity;

    Trader* buyer = algo->getTrader(order->id);

    while (q > 0) {
        Order* matchedOrd = sellOrders->getLowestOrder();

        // No sellers left
        if (matchedOrd == nullptr) {
            break;
        }

        // Cheapest seller is too expensive
        if (matchedOrd->price > order->price) {
            break;
        }

        int p = matchedOrd->price;
        int fillQuantity = std::min(q, matchedOrd->quantity);

        Trader* seller = algo->getTrader(matchedOrd->id);

        // Transfer money
        buyer->money -= fillQuantity * p;
        seller->money += fillQuantity * p;

        // Transfer shares
        seller->qOwned -= fillQuantity;
        buyer->qOwned += fillQuantity;

        q -= fillQuantity;
        matchedOrd->quantity -= fillQuantity;

        if (matchedOrd->quantity == 0) {
            sellOrders->deleteLowestOrder();
        }
    }

    // Whatever wasn't immediately filled becomes a resting limit order
    if (q > 0) {
        order->quantity = q;
        buyOrders->addOrder(order);
    }
    else {
        // The entire incoming order was filled, so it isn't stored anywhere
        delete order;
    }
}
void OrderBook::placeSellOrder(Order* order) {
    int q = order->quantity;

    Trader* seller = algo->getTrader(order->id);

    while (q > 0) {
        Order* matchedOrd = buyOrders->getHighestOrder();

        // No buyers left
        if (matchedOrd == nullptr) {
            break;
        }

        // Highest buyer isn't offering enough
        if (matchedOrd->price < order->price) {
            break;
        }

        int p = matchedOrd->price;
        int fillQuantity = std::min(q, matchedOrd->quantity);

        Trader* buyer = algo->getTrader(matchedOrd->id);

        // Transfer money
        buyer->money -= fillQuantity * p;
        seller->money += fillQuantity * p;

        // Transfer shares
        seller->qOwned -= fillQuantity;
        buyer->qOwned += fillQuantity;

        q -= fillQuantity;
        matchedOrd->quantity -= fillQuantity;

        if (matchedOrd->quantity == 0) {
            buyOrders->deleteHighestOrder();
        }
    }

    // Unfilled portion stays as a limit order
    if (q > 0) {
        order->quantity = q;
        sellOrders->addOrder(order);
    }
    else {
        delete order;
    }
}

void OrderBook::placeBuyInstantOrder(int quantity, int traderID) {
    int q = quantity;

    while (q > 0) {
        Order* matchedOrd = sellOrders->getLowestOrder();

        if (matchedOrd == nullptr) {
            return;
        }

        int p = matchedOrd->price;

        Trader* seller = algo->getTrader(matchedOrd->id);
        Trader* buyer = algo->getTrader(traderID);

        int fillQuantity = std::min(q, matchedOrd->quantity);

        // Transfer money
        buyer->money -= fillQuantity * p;
        seller->money += fillQuantity * p;

        // Transfer shares
        seller->qOwned -= fillQuantity;
        buyer->qOwned += fillQuantity;

        // Reduce both orders
        q -= fillQuantity;
        matchedOrd->quantity -= fillQuantity;

        // Remove completely filled order
        if (matchedOrd->quantity == 0) {
            sellOrders->deleteLowestOrder();
        }
    }
}
void OrderBook::placeSellInstantOrder(int quantity, int traderID) {
    int q = quantity;

    while (q > 0) {
        Order* matchedOrd = buyOrders->getHighestOrder();

        if (matchedOrd == nullptr) {
            return;
        }

        int p = matchedOrd->price;

        Trader* buyer = algo->getTrader(matchedOrd->id);
        Trader* seller = algo->getTrader(traderID);

        int fillQuantity = std::min(q, matchedOrd->quantity);

        // Transfer money
        buyer->money -= fillQuantity * p;
        seller->money += fillQuantity * p;

        // Transfer shares
        seller->qOwned -= fillQuantity;
        buyer->qOwned += fillQuantity;

        // Reduce both orders
        q -= fillQuantity;
        matchedOrd->quantity -= fillQuantity;

        // Remove completely filled order
        if (matchedOrd->quantity == 0) {
            buyOrders->deleteHighestOrder();
        }
    }
}

int OrderBook::getBestAsk() {
    if (sellOrders->getLowestOrder()==nullptr) {return -1;}
    return sellOrders->getLowestOrder()->price;

}
int OrderBook::getBestBid() {
    if (buyOrders->getHighestOrder()==nullptr) {return -1;}
    return buyOrders->getHighestOrder()->price;
}
int OrderBook::getMeanPrice() {
    int bp = getBestAsk();
    int sp = getBestBid();
    if (bp<0) {bp=sp;}
    if (sp<0) {sp=0; bp=1000000;}
    return (bp+sp)/2;
}

//TODO: make this a better method
OrderBook::OrderBook() {
    buyOrders = new OrderTree(new Order(1000,100,(int) duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count(),0));
    sellOrders = new OrderTree(new Order(1010,10000,(int) duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count(),0));
    algo = nullptr;
}

void OrderBook::outputOrderBook() {
    std::cout << "\nSELLS:\n";

    int count = 0;
    sellOrders->printLowestLevels(count, 3);

    std::cout << "BUYS:\n";

    count = 0;
    buyOrders->printHighestLevels(count, 3);

    std::cout << '\n';
}
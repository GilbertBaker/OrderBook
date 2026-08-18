//
// Created by Gilbe on 17/08/2026.
//
#include <chrono>
#include "OrderBook.h"
using namespace std::chrono;
void OrderBook::placeBuyOrder(Order* order) {
    if (getBuyPrice() < order->price) {
        placeBuyInstantOrder(order->quantity, order->id);
    }
    else {
        buyOrders->addOrder(order);
    }
}
void OrderBook::placeSellOrder(Order* order) {
    if (getSellPrice() > order->price) {
        placeSellInstantOrder(order->quantity, order->id);
    }
    else {
        sellOrders->addOrder(order);
    }
}

void OrderBook::placeBuyInstantOrder(int quantity, int traderID) {
    int q = quantity;
    while (q>0) {
        Order* matchedOrd = sellOrders->getLowestOrder();

        //update money
        int p = matchedOrd->price;
        Trader* seller = algo->getTrader(matchedOrd->id);
        Trader* buyer = algo->getTrader(traderID);

        if (matchedOrd->quantity < quantity) {
            //switch assets arround
            buyer->money -= matchedOrd->quantity*p;
            seller->money += matchedOrd->quantity*p;
            seller->qOwned -= matchedOrd->quantity;
            buyer->qOwned += matchedOrd->quantity;

            q -= matchedOrd->quantity;
            matchedOrd->quantity = 0;

            //seems a dodgey way to do this -> fix
            sellOrders->deleteLowestOrder();
        }
        else {
            //switch assets around
            buyer->money -= quantity*p;
            seller->money += quantity*p;
            seller->qOwned -= quantity;
            buyer->qOwned += quantity;

            matchedOrd->quantity -= quantity;
            q =0;
        }

    }
}
void OrderBook::placeSellInstantOrder(int quantity, int traderID) {
    int q = quantity;
    while (q>0) {
        Order* matchedOrd = buyOrders->getHighestOrder();

        //update money
        int p = matchedOrd->price;
        Trader* buyer = algo->getTrader(matchedOrd->id);
        Trader* seller = algo->getTrader(traderID);

        if (matchedOrd->quantity < quantity) {
            //switch assets arround
            buyer->money -= matchedOrd->quantity*p;
            seller->money += matchedOrd->quantity*p;
            seller->qOwned -= matchedOrd->quantity;
            buyer->qOwned += matchedOrd->quantity;

            q -= matchedOrd->quantity;
            matchedOrd->quantity = 0;

            //seems a dodgey way to do this -> fix
            buyOrders->deleteHighestOrder();
        }
        else {
            //switch assets around
            buyer->money -= quantity*p;
            seller->money += quantity*p;
            seller->qOwned -= quantity;
            buyer->qOwned += quantity;

            matchedOrd->quantity -= quantity;
            q =0;
        }

    }
}

int OrderBook::getBuyPrice() {
    return sellOrders->getLowestOrder()->price;

}
int OrderBook::getSellPrice() {
    return buyOrders->getHighestOrder()->price;
}
int OrderBook::getMeanPrice() {
    return (getBuyPrice()+getSellPrice())/2;
}

//TODO: make this a better method
OrderBook::OrderBook() {
    buyOrders = new OrderTree(new Order(1000,1000,(int) duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count(),-1));
    sellOrders = new OrderTree(new Order(1100,100000,(int) duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count(),-1));
    algo = nullptr;
}
//
// Created by Gilbe on 17/08/2026.
//

#include "Trader.h"
#include "random"
Trader::Trader(int id) : ID(id) {
    money= 100000;
    qOwned = 0;
}

//current strategy:
//1% ish for each market buy/sell and limit buy/sell.
//always put 1000 on the order.
//
void Trader::Update() {
    //TODO: make this more complicated.
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(0, 99);

    int v = dist(gen);
    //2% ish buy chance
    if (v<=1) {
        if (v==0) {
            //market buy
            marketBuy();
        }
        else if (v==1) {
            //limit buy
            limitBuy();
        }
    }
    //2% ishsell chance
    else if (v<=3) {
        if (v==2) {
            //market sell
            marketSell();
        }
        else if (v==3) {
            //limit sell
            limitSell();
        }
    }

}

void Trader::marketBuy() {
    if (money < 0) {
        return;
    }
    algo->orderBook->placeBuyInstantOrder(1000,ID);
}
void Trader::limitBuy() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(-20, 20);

    int l = dist(gen);
    OrderBook* ordBook = algo -> orderBook;
    Order* order = new Order(l+ordBook->getBuyPrice(),1000,algo->getCurrentTime(),ID);
    ordBook->placeBuyOrder(order);
}
void Trader::limitSell() {
    if (qOwned<1000) {return;}
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(-20, 20);

    int l = dist(gen);
    OrderBook* ordBook = algo -> orderBook;
    Order* order = new Order(l+ordBook->getBuyPrice(),1000,algo->getCurrentTime(),ID);
    ordBook->placeSellOrder(order);

}
void Trader::marketSell() {
    if (qOwned<1000) {return;}
    algo->orderBook->placeSellInstantOrder(1000,ID);
}
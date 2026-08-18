//
// Created by Gilbe on 17/08/2026.
//

#include "Trader.h"
#include "TraderAlgo.h"
#include "../DataStructures/OrderBook.h"
#include "../Order.h"
#include <random>
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
    if (v<=2) {
        if (v==0) {
            //market buy
            marketBuy();
        }
        else {
            //limit buy
            limitBuy();
        }
    }
    //2% ishsell chance
    else if (v<=4) {
        if (v==4) {
            //market sell
            marketSell();
        }
        else {
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
    OrderBook* ordBook = algo -> orderBook;
    int buyPrice = ordBook->getBuyPrice();
    int sellPrice = ordBook->getSellPrice();
    if (buyPrice<=0) {buyPrice=sellPrice+20; if (sellPrice <=0) {buyPrice=1000; sellPrice=1000;}}
    int dif = buyPrice-sellPrice;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(sellPrice-20,buyPrice);

    int l = dist(gen);

    //work out quantity
    std::uniform_int_distribution<int> dist2(1, 3000);
    int q = dist2(gen);


    //if no orders default to 1000
    if (buyPrice<=0) {buyPrice=ordBook->getSellPrice(); if (buyPrice<=0) {buyPrice=1000;}}
    Order* order = new Order(l+buyPrice,q,algo->getCurrentTime(),ID);
    ordBook->placeBuyOrder(order);
}
void Trader::limitSell() {
    if (qOwned<=0) {return;}
    OrderBook* ordBook = algo -> orderBook;
    int buyPrice = ordBook->getBuyPrice();
    int sellPrice = ordBook->getSellPrice();
    if (buyPrice<=0) {buyPrice=sellPrice+20; if (sellPrice <=0) {buyPrice=1000; sellPrice=1000;}}
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(sellPrice, buyPrice+20);

    int l = dist(gen);

    //work out quantity
    std::uniform_int_distribution<int> dist2(1, qOwned);
    int q = dist2(gen);


    //if no orders default to 1000
    if (buyPrice<=0) {buyPrice=ordBook->getBuyPrice(); if (buyPrice<=0) {buyPrice=1000;}}
    Order* order = new Order(l+ordBook->getBuyPrice(),q,algo->getCurrentTime(),ID);
    ordBook->placeSellOrder(order);

}
void Trader::marketSell() {
    if (qOwned<=0) {return;}
    std::random_device rd;
    std::mt19937 gen(rd());



    //work out quantity
    std::uniform_int_distribution<int> dist2(1, qOwned);
    int q = dist2(gen);

    //place
    algo->orderBook->placeSellInstantOrder(q,ID);
}
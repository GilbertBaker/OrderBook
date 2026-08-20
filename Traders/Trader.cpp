//
// Created by Gilbe on 17/08/2026.
//

#include "Trader.h"
#include "TraderAlgo.h"
#include "../DataStructures/OrderBook.h"
#include "../Order.h"
#include <random>
Trader::Trader(int id) : ID(id) {
    money= 10000;
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
    if (v<=49) {
        if (v<=25) {
            //market buy
            marketBuy();
        }
        else {
            //limit buy
            limitBuy();
        }
    }
    //2% ishsell chance
    else {
        if (v<=74) {
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
    if (money < 1000*algo->orderBook->getBestAsk()) {
        return;
    }
    algo->orderBook->placeBuyInstantOrder(1000,ID);
}
void Trader::limitBuy() {
    OrderBook* ordBook = algo -> orderBook;
    int buyPrice = ordBook->getBestAsk();
    int sellPrice = ordBook->getBestBid();
    if (buyPrice<=0) {buyPrice=sellPrice+20; if (sellPrice <=0) {buyPrice=1000; sellPrice=1000;}}
    int dif = buyPrice-sellPrice;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(sellPrice-50,buyPrice+50);

    int l = dist(gen);

    //work out quantity
    std::uniform_int_distribution<int> dist2(1, 3000);
    int q = dist2(gen);


    //if no orders default to 1000
    if (buyPrice<=0) {buyPrice=ordBook->getBestBid(); if (buyPrice<=0) {buyPrice=1000;}}
    if (l*q>money) {return;}
    Order* order = new Order(l,q,algo->getCurrentTime(),ID);
    ordBook->placeBuyOrder(order);
}
void Trader::limitSell() {
    if (qOwned<=0) {return;}
    OrderBook* ordBook = algo -> orderBook;
    int buyPrice = ordBook->getBestAsk();
    int sellPrice = ordBook->getBestBid();
    if (buyPrice<=0) {buyPrice=sellPrice+20; if (sellPrice <=0) {buyPrice=1000; sellPrice=1000;}}
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random integer from 1 to 10 inclusive
    std::uniform_int_distribution<int> dist(sellPrice-50, buyPrice+50);

    int l = dist(gen);

    //work out quantity
    std::uniform_int_distribution<int> dist2(1, qOwned);
    int q = dist2(gen);


    //if no orders default to 1000
    if (buyPrice<=0) {buyPrice=ordBook->getBestAsk(); if (buyPrice<=0) {buyPrice=1000;}}
    Order* order = new Order(l,q,algo->getCurrentTime(),ID);
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
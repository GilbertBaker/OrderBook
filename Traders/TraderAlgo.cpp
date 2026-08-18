//
// Created by Gilbe on 17/08/2026.
//

#include "TraderAlgo.h"

#include <chrono>
#include <memory>
#include <unordered_map>



TraderAlgo::TraderAlgo(OrderBook* ordBook) : orderBook(ordBook) {
    curID=1;
    //for now:
    noOfTraders=500;
    for (int i=curID;i<noOfTraders;i++) {
        traders[i] = new Trader(i);
        traders[i] ->algo = this;
        curID+=1;
    }
}

void TraderAlgo::Update() {
    for (int i=1;i<noOfTraders;i++) {
        traders[i]->Update();
    }
}

Trader* TraderAlgo::getTrader(int id) {
    return traders[id];
}

int TraderAlgo::getCurrentTime() {
    return (int) duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
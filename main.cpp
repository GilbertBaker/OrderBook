#include <iostream>


#include "Traders/TraderAlgo.h"
int main() {
    std::cout << "Hello, World!" << std::endl;

    OrderBook orderBook = OrderBook();
    TraderAlgo tAlgo =  TraderAlgo(&orderBook);
    orderBook.algo=&tAlgo;
    while (true) {
        tAlgo.Update();
        std::cout << tAlgo.orderBook->getMeanPrice();
    }
    return 0;
}

cmake_minimum_required(VERSION 4.3)
project(OrderBook)

set(CMAKE_CXX_STANDARD 20)

add_executable(OrderBook main.cpp
        Order.cpp
        Order.h
        DataStructures/OrderTree.cpp
        DataStructures/OrderTree.h
        DataStructures/OrdListNode.cpp
        DataStructures/OrdListNode.h
        DataStructures/OrdListNode.h
        DataStructures/OrderList.cpp
        DataStructures/OrderList.h)

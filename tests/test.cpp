#include <iostream>
#include "OrderBook.hpp"
#include <vector>

void readResults(std::vector<bool> tests){
    for(int i = 0; i < tests.size(); i++){
        if (tests[i]){
            std::cout << "Passed Test " << i + 1 << "\n";
        } else {
            std::cout << "Failed Test " << i + 1 << "\n";
        }
    }
}

std::vector<bool> testAddOrder(){
    OrderBook b (false);

    std::vector<bool> tests;

    b.addOrder(0, true, 100, -1);

    tests.push_back(b.bids.size() == 0); 

    b.addOrder(0, false, 100, -1);
    tests.push_back(b.asks.size() == 0);

    b.addOrder(0, true, -1, 100);
    tests.push_back(b.bids.size() == 0);

    b.addOrder(0, false, -1, 100);
    tests.push_back(b.asks.size() == 0);

    b.addOrder(1, true, 10, 10);
    tests.push_back(b.bids.size() == 1);

    b.addOrder(2, true, 10, 10);
    tests.push_back(b.bids.size() == 1);

    b.addOrder(2, true, 101, 10);
    tests.push_back(b.bids.size() == 1);

    b.addOrder(3, false, 11, 10);
    tests.push_back(b.asks.size() == 1);

    b.addOrder(4, false, 11, 10);
    tests.push_back(b.asks.size() == 1);

    b.addOrder(4, false, 11, 10);
    tests.push_back(b.asks.size() == 1);

    b.addOrder(5, true, 10.5, 100);
    tests.push_back(b.bids.size() == 2);

    b.addOrder(6, false, 10.75, 100);
    tests.push_back(b.asks.size() == 2);

    tests.push_back(b.bids[1].orderids[1] == 2);
    tests.push_back(b.asks[1].orderids[1] == 4);

    return tests;
}

std::vector<bool> testDeleteOrder(){
    OrderBook b(false);

    std::vector<bool> tests;

    b.addOrder(0, true, 100, 10);
    b.deleteOrder(0);

    tests.push_back(b.bids.size() == 0);

    b.addOrder(0, false, 100, 10);
    tests.push_back(b.asks.size() == 1);

    b.deleteOrder(0);
    tests.push_back(b.asks.size() == 0);

    b.addOrder(0, true, 100, 10);
    b.addOrder(1, true, 100, 20);

    tests.push_back(b.bids[0].volume == 30);
    b.deleteOrder(1);
    tests.push_back(b.bids[0].volume == 10);
    tests.push_back(b.bids[0].getIds()[0] == 0);
    b.deleteOrder(0);

    b.addOrder(0, false, 100, 10);
    b.addOrder(1, false, 100, 10);

    tests.push_back(b.asks[0].volume == 20);
    b.deleteOrder(0);
    tests.push_back(b.asks[0].volume == 10);
    tests.push_back(b.asks[0].getIds()[0] == 1);

    b.deleteOrder(1);

    return tests;

}

std::vector<bool> testUpdateOrder(){
    OrderBook b (false);

    std::vector<bool> tests;

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, true, 10, 10);
    b.updateOrder(1, 20);

    tests.push_back(b.bids.size() == 1);
    tests.push_back(b.bids[0].getIds()[1] == 1);

    b.updateOrder(0, 20);
    tests.push_back(b.bids[0].getIds()[1] == 0);

    b.updateOrder(10, 20);
    tests.push_back(b.bids.size() == 1);
    tests.push_back(b.asks.size() == 0);

    b.updateOrder(1, 0);
    tests.push_back(b.bids[0].getIds()[1] == 0);
    tests.push_back(b.bids[0].volume == 40);

    b.deleteOrder(0);
    b.deleteOrder(1);

    b.addOrder(0, false, 10, 10);
    b.addOrder(1, false, 10, 10);
    b.updateOrder(0, 20);

    tests.push_back(b.asks[0].getIds()[1] == 0);

    b.updateOrder(1, 0);

    tests.push_back(b.asks[0].getIds()[1] == 0);
    tests.push_back(b.asks[0].volume == 30);

    return tests;
    
}

std::vector<bool> testMatchAlgo(){
    OrderBook b (false);

    std::vector<bool> tests;

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, false, 10, 10);

    tests.push_back(b.bids.size() == 0 && b.asks.size() == 0);

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, false, 8, 10);

    tests.push_back(b.bids.size() == 0 && b.asks.size() == 0);

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, false, 10, 5);

    tests.push_back(b.bids[0].volume == 5 && b.asks.size() == 0);

    b.deleteOrder(0);

    b.addOrder(0, true, 10, 5);
    b.addOrder(1, false, 10, 10);

    tests.push_back(b.bids.size() == 0 && b.asks[0].volume == 5);

    b.deleteOrder(1);

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, true, 9.50, 10);
    b.addOrder(2, true, 9, 10);

    b.addOrder(3, false, 8, 30);

    tests.push_back(b.bids.size() == 0 && b.asks.size() == 0);

    b.addOrder(0, false, 10, 10);
    b.addOrder(1, false, 9.50, 10);
    b.addOrder(2, false, 9, 10);

    b.addOrder(3, true, 11, 30);

    tests.push_back(b.bids.size() == 0 && b.asks.size() == 0);

    b.deleteOrder(0);
    b.deleteOrder(1);
    b.deleteOrder(2);
    b.deleteOrder(3);

    b.addOrder(0, true, 10, 10);
    b.addOrder(1, true, 10, 10);
    b.addOrder(2, false, 10, 11);

    tests.push_back(b.asks.size() == 0 && b.bids[0].volume == 9);

    b.deleteOrder(0);
    b.deleteOrder(1);
    b.deleteOrder(2);

    b.addOrder(0, false, 10, 10);
    b.addOrder(1, false, 10, 10);
    b.addOrder(2, true, 10, 11);

    tests.push_back(b.asks[0].volume == 9 && b.bids.size() == 0);
    return tests;


}



int main(){
    std::vector<bool> tests;

    std::cout << "Testing Add Order Functionality\n";
    tests = testAddOrder();
    readResults(tests);

    std::cout << "\nTesting Delete Order Functionality\n";
    tests = testDeleteOrder();
    readResults(tests);

    std::cout << "\nTesting Update Order Functionality\n";
    tests = testUpdateOrder();
    readResults(tests);

    std::cout << "\nTesting Matching Functionality\n";
    tests = testMatchAlgo();
    readResults(tests);

}
#include "OrderBook.hpp"

int main(){
    OrderBook b(true);

    b.addOrder(1, true, 105, 100);
    b.addOrder(2, true, 105, 100);
    b.addOrder(3, true, 105, 100);
    b.addOrder(4, true, 104, 100);
    b.addOrder(5, false, 103.5, 399);

    b.printBook();
}
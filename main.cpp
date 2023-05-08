#include "OrderBook.hpp"

int main(){
    OrderBook b(true);

    
    b.add_order(1, false, 100, 1);
    b.add_order(2, true, 100, 1);
    b.add_order(6, false, 105, 100);
    b.add_order(3, true, 105, 1);
    b.add_order(4, false, 103, 1);
    b.add_order(5, false, 102, 2);
    
    //b.update_order(5, 199);
    b.update_order(3, 2);
    b.update_order(3, 1);
    b.delete_order(3);
    b.delete_order(1);
    b.delete_order(6);
    //b.add_order(6, true, 102,11);
    //b.add_order(7, false, 102.1515,11);

   b.print_book();
}
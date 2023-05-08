#include <vector>

class PriceLevel {
    public:
        double price {};
        long volume{};
        std::vector <long> orderids{};
    
    PriceLevel(double act_price){
        volume = 0; 
        price = act_price; 
    }

    void add_id(long amount, long id);
    void adjust_id(long adj, long id, bool put_back);
    std::vector<long> get_ids();

};
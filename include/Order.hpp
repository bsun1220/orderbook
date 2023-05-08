
class Order{
    public:
        long uid{};
        double price{};
        bool side{};
        int volume{}; 
    
    Order(long act_uid, double act_price, bool act_side, int act_volume){
        uid = act_uid;
        price = act_price;
        side = act_side;
        volume = act_volume;
    }

    void update_quantity(double act_volume);
    
};
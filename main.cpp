#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// first user defines tax rate and action price
// user can buy shares: enter ticker, price, num of shares
// for each new ticker symbol new shares list/queue is created
// user can sell shares: enter ticker, price, num of shares
// shares will be sold in fifo order


class Share{
    private:
        std::string ticker_symbol;
        double share_price;
    public:
        Share(std::string, double);
        Share();
        ~Share();
        std::string GetTicker() {
            return this->ticker_symbol;
        }
        double GetSharePrice() {
            return this->share_price;
        }

};


class User{
    private:
        std::string name;
        double USD_CASH;
    
    public:
        std::map<std::string, std::vector<Share> > all_shares;

        double GetCash(){
            return this->USD_CASH;
            }

        void AddCash(double amount){
            this->USD_CASH += amount;
            }

        std::string GetName() {
            return this->name;
        }

        void SetName(std::string name) {
            this->name = name;
        }
                
        void AddShare(std::string ticker, double price) {
            Share added_share = Share(ticker, price);
            if (this->all_shares.find(ticker) == this->all_shares.end()) {
                std::vector<Share> ticker_vector{added_share};
                this->all_shares.insert({ticker, ticker_vector});
            }
            else {
                this->all_shares[ticker].push_back(added_share);
            }
        }

        User() {
            SetName("user");
            AddCash(0.0);
        };
        User(std::string name, double cash) {
            SetName(name);
            AddCash(cash);
        };

};

int main() {

    std::cout << "--------- Stock Market Tax Calculator ---------\n\n\n" << std::endl;

    std::string user_name;
    double initial_cash;

    std::cout << "Please Enter Your Name: " << std::endl;
    std::cin >> user_name;
    std::cout << "Initial Cash position (in $): " << std::endl;
    std::cin >> initial_cash;
    User user = User(user_name, initial_cash);

    double tax_rate;
    double action_fee;

    std::cout << "What is your tax rate? (enter a number representing the % value): " << std::endl;
    std::cin >> tax_rate;
    std::cout << "Your broker's action fee (in $): " << std::endl;
    std::cin >> action_fee;

    // Main loop
    bool exit = false;
    while (not exit) {

        std::cout << user.GetName() + "'s brokerage account" << std::endl;
        std::cout << "Current cash position: " + std::to_string(user.GetCash()) << std::endl;
        // if (not user.all_shares.empty()) {
        //     std::for_each(user.all_shares.begin(), user.all_shares.end(), [](const auto &myMapPair)) {
        //         std::cout << myMapPair.first;       
        //     }
    }

    std::cout << "Program closed" << std::endl;
}

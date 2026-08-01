#include <vector>
#include <string>
#include <numeric> 

class Solution {
public:
    int calPoints(vector<std::string>& operations) {
        vector<int> record;
        
        for (const string& op : operations) {
            if (op == "+") {
                int last = record.back();
                int second_last = record[record.size() - 2];
                record.push_back(last + second_last);
            } 
            else if (op == "D") {
                record.push_back(record.back() * 2);
            } 
            else if (op == "C") {
                record.pop_back();
            } 
            else {
                record.push_back(std::stoi(op));
            }
        }
        
        int total_sum = 0;
        for (int score : record) {
            total_sum += score;
        }
        
        return total_sum;
    }
};

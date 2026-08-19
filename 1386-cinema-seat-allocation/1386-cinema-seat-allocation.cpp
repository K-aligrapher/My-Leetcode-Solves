#include <vector>
#include <unordered_map>

class Solution {
public:
    int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats) {
        // Group reservations by row using a bitmask for the 10 seats
        std::unordered_map<int, int> rowToSeats;
        for (const auto& reservation : reservedSeats) {
            int row = reservation[0];
            int seat = reservation[1];
            // Set the bit corresponding to the reserved seat (1-indexed to 0-indexed)
            rowToSeats[row] |= (1 << (seat - 1));
        }
        
        // Base answer: assume all rows are completely empty and can host 2 families
        int maxGroups = (n - rowToSeats.size()) * 2;
        
        // Bitmask definitions for our 3 valid blocks (0-indexed bits)
        // Seats 2,3,4,5 -> bits 1,2,3,4   -> 0b0000011110 (decimal 30)
        // Seats 4,5,6,7 -> bits 3,4,5,6   -> 0b0001111000 (decimal 120)
        // Seats 6,7,8,9 -> bits 5,6,7,8   -> 0b0111100000 (decimal 480)
        int left_mask   = 0b0000011110; 
        int middle_mask = 0b0001111000; 
        int right_mask  = 0b0111100000; 
        
        // Process only the rows that have reservations
        for (const auto& [row, seatsBitmask] : rowToSeats) {
            bool left_free = (seatsBitmask & left_mask) == 0;
            bool right_free = (seatsBitmask & right_mask) == 0;
            
            if (left_free && right_free) {
                // Both sides are clear, fits 2 groups
                maxGroups += 2;
            } else if (left_free || right_free || (seatsBitmask & middle_mask) == 0) {
                // If left or right is free (but not both), OR if the middle is free
                maxGroups += 1;
            }
            // If none are true, 0 groups fit in this row, so we add nothing
        }
        
        return maxGroups;
    }
};

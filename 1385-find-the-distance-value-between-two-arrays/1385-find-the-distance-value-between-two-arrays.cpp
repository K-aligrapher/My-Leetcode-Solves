class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count=0;

        for(int num : arr1)
        {
            bool has_conflict=false;

            for(int val=num-d;val<=num+d;val++)
            {
                if(binary_search(arr2.begin(),arr2.end(),val))
                {
                    has_conflict=true;
                    break;
                }
            }

            if(!has_conflict)
            count++;
        }
        return count;
    }
};
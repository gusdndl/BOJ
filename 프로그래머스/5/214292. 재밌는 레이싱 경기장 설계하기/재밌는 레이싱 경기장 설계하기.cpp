#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> heights) {
    sort(heights.begin(),heights.end());
    vector<int> minusV; 
    if (heights.size()%2==1) //홀수
    {
        for (int i=0; i<heights.size()/2; i++)
        {
            minusV.push_back(heights[i+heights.size()/2]-heights[i]);
        }
        minusV.push_back(heights[heights.size()-1]-heights[heights.size()/2]);
        sort(minusV.begin(),minusV.end());
        return minusV[1];
    }
    else
    {
        for (int i=0; i<heights.size()/2; i++)
        {
            minusV.push_back(heights[i+heights.size()/2]-heights[i]);
        }
        sort(minusV.begin(),minusV.end());
        return minusV[0];
    }
    return 0;
}
 
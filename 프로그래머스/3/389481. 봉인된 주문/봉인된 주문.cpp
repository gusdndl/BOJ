#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
long long N;
int num = 26;

string Find()
{   
    int len = 0;
    vector<int> digit;
    while(pow(num, len) < N)
    {
        int idx = N / (long long)pow(num, len) % num;
        if(idx == 0) idx = num;
        if(!digit.empty() && digit.back() == num-1) idx--;
        digit.push_back(idx - 1);
        len++;
    }
    
    string result;
    
    for(int i = 0; i < digit.size(); i++)
    {
        int d = digit[i];
        
        char temp = d + 'a';
        result += temp;
    }
    
    reverse(result.begin(), result.end());
    
    return result;
}

string NextMove(string target)
{
    int idx = target.length() - 1;
    int carry = 0;
    string result;
    
    int temp = target[idx] - 'a';
    temp++;
    if(temp < num)
    {
        result = target;
        result[idx] = temp + 'a';
    }
    else
    {
        while(idx >= 0)
        {
            carry += temp / num;
            temp %= num;
            
            result += temp + 'a';
            idx--;
            
            temp = target[idx] - 'a' + carry;
            carry = 0;
        }
    
        if(carry != 0)
        {
            result += carry + 'a';
        }
    
        reverse(result.begin(), result.end());
    }
    
    return result;
}

string solution(long long n, vector<string> bans) {
    N = n;
    
    string target = Find();
    
    sort(bans.begin(), bans.end(), [](string& a, string& b){
        if(a.length() == b.length()) return a < b;
        return a.length() < b.length();
    });
    
    int pos = 0;
    for(; pos < bans.size(); pos++)
    {
        auto bansLen = bans[pos].length();
        auto targetLen = target.length();
        
        if(bansLen > targetLen) break;
        else if(bansLen == targetLen)
        {
            if(bans[pos] > target) break;
        }
    }
    
    int cnt = pos;
    while(cnt > 0)
    {
        auto next = NextMove(target);
        target = next;
        
        if(pos >= bans.size())
        {
            cnt--;
            continue;
        }
        
        if(bans[pos] != next) cnt--;
        if(bans[pos] <= next) pos++;
    }
    
    return target;
}
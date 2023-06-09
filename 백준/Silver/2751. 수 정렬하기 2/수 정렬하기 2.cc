#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(NULL); 
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }

    std::sort(numbers.begin(), numbers.end());

    for (int i = 0; i < n; i++) {
        std::cout << numbers[i] << '\n';
    }

    return 0;
}

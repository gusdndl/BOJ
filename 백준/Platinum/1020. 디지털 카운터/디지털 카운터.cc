#include<iostream>
#include<algorithm>
#include<string>
#include<math.h>
#include<cstring>

using namespace std;

string inputNum;
int digitLines[10] = { 6,2,5,5,4,5,6,3,7,5 };
char memCache[16][16][16][16][16][16][2];
long long finalRes;

int edgeCount(long long curNum, int size) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		count += digitLines[curNum % 10];
		curNum /= 10;
	}

	return count;
}

int calculateTime(long long curNum, int count2, int count3, int count4, int count5, int count6, int count7, int targetCount, int bypass, int len, int index, long long num) {
	if (index == len) {
		if (2 * count2 + 3 * count3 + 4 * count4 + 5 * count5 + 6 * count6 + 7 * count7 == targetCount) {
			if (bypass == 0 && curNum == num)
				return 0;
			finalRes = curNum;
			return 1;
		}
		return 0;
	}
	
	char& refResult = memCache[count2][count3][count4][count5][count6][count7][bypass];

	if (refResult != -1)
		return refResult;

	refResult = 0;
	for (int i = bypass == 1 ? 0 : (inputNum[index] - '0'); i < 10; i++) {
		int newBypass = bypass == 1 || i > inputNum[index] - '0';

		refResult = calculateTime(10 * curNum + i, count2 + (int)(digitLines[i] == 2), count3 + (int)(digitLines[i] == 3), count4 + (int)(digitLines[i] == 4), count5 + (int)(digitLines[i] == 5), count6 + (int)(digitLines[i] == 6), count7 + (int)(digitLines[i] == 7), targetCount, newBypass, len, index + 1, num);
		if (refResult != 0)
			return refResult;
		if (index == 0 && i == 9) {
			i = -1;
			bypass = 1;
		}
	}
	return refResult;
}

int main(void) {
	int N, count;
	long long upperLimit;
	memset(memCache, -1, sizeof(memCache));
	cin >> inputNum;
	N = inputNum.size();
	upperLimit = pow(10, N);
	count = edgeCount(stoll(inputNum), N);

	calculateTime(0, 0, 0, 0, 0, 0, 0, count, 0, N, 0, stoll(inputNum));

	if (finalRes - stoll(inputNum) == 0)
		cout << (finalRes - 1 - stoll(inputNum) + upperLimit) % upperLimit + 1;
	else
		cout << (finalRes - stoll(inputNum) + upperLimit) % upperLimit;
	return 0;
}

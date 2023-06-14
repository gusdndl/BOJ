#include <cstdio>

int main() {
    int arraySize, numbers[51], index, constant, isFunction = 1, coefficient1, coefficient2, multiplier;
    scanf("%d", &arraySize);
    for (index = 0; index < arraySize; index++)
        scanf("%d", &numbers[index]);

    if (arraySize == 1) printf("A");
    else if (arraySize == 2) {
        if (numbers[0] == numbers[1]) printf("%d",numbers[0]);
        else printf("A");
    }
    else {
        multiplier = 0;
        coefficient1 = numbers[1] - numbers[0];
        coefficient2 = numbers[2] - numbers[1];
        if (coefficient1 != 0) multiplier = coefficient2 / coefficient1;
        constant = numbers[1] - multiplier * numbers[0];
        for (index = 1; index < arraySize; index++) {
            if (numbers[index] != (numbers[index - 1] * multiplier + constant)) {
                isFunction = 0;
                break;
            }
        }
        if (isFunction) printf("%d", (numbers[arraySize - 1] * multiplier + constant));
        else printf("B");
    }

    return 0;
}

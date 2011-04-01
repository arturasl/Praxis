// http://programmingpraxis.com/2011/04/01/maximum-difference-in-an-array/

#include      <iostream>
#include      <cstdlib>
#include      <ctime>

std::pair<int, int> fnQuaratic(const int anArray[], int nSize) {
	std::pair<int, int> result(0, 0);
	int nMax = 0;

	for (int i = 0; i < nSize; ++i) {
		for (int j = i + 1; j < nSize; ++j) {
			if (nMax < anArray[j] - anArray[i]) {
				nMax          = anArray[j] - anArray[i];
				result.first  = i;
				result.second = j;
			}
		}
	}

	return result;
}
std::pair<int, int> fnLinear(const int anArray[], int nSize) {
	std::pair<int, int> result(0, 0);
	int nMax = 0;
	int nSmallest = anArray[0], nLargest = anArray[0];
	int nSmallestPos = 0, nLargestPos = 0;

	for (int i = 1; i < nSize; ++i) {
		if (nSmallest > anArray[i]) {
			nSmallest = anArray[i];
			nSmallestPos = i;
			nLargest = anArray[i];
			nLargestPos = i;
		}

		if (nLargest < anArray[i]) {
			nLargest = anArray[i];
			nLargestPos = i;
		}

		if (nMax < nLargest - nSmallest) {
			nMax          = nLargest - nSmallest;
			result.first  = nSmallestPos;
			result.second = nLargestPos;
		}
	}

	return result;
}

int main(int argc, char **argv) {
	int anArray[10];
	const int nArray = sizeof(anArray) / sizeof(int);
	std::pair<int, int> result1, result2;

	for (int nTest = 1; nTest <= 1000000; ++nTest) {
		for (int i = 0; i < nArray; ++i) {
			anArray[i] = rand() % 10 + 1;
		}

		if ((result1 = fnQuaratic(anArray, nArray)) != (result2 = fnLinear(anArray, nArray))) {
			for (int j = 0; j < nArray;  ++j) {
				std::cout << anArray[j] << ' ';
			}

			std::cout << std::endl << result1.first << ", " << result1.second << std::endl;
			std::cout << result2.first << ", " << result2.second << std::endl;
		}
	}

	return 0;
}

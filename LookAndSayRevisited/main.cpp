//http://programmingpraxis.com/2011/03/28/look-and-say-revisited/

#include      <iostream>
#include      <cmath>
#include      <iomanip>

double fnCalcFunc(const int anCoef[], int nSize, double x){
	double fResult = 0;
	for (int j = 0; j < nSize; ++j) fResult += anCoef[j] * pow(x, j);
	return fResult;
}
int main(int argc, char **argv) {
	const int anCoef[] = {-6, 3, -6, 12, -4, 7, -7, 1, 0, 5, -2, -4, -12, 2, 7, 12, -7, -10, -4, 3, 9, -7, 0, -8, 14, -3, 9, 2, -3, -10, -2, -6, 1, 10, -3, 1, 7, -7, 7, -12, -5, 8, 6, 10, -8, -8, -7, -3, 9, 1, 6, 6, -2, -3, -10, -2, 3, 5, 2, -1, -1, -1, -1, -1, 1, 2, 2, -1, -2, -1, 0, 1};
	const int nCoef = sizeof(anCoef) / sizeof(int);
	int anDeri[nCoef - 1];
	const double fEpsilon = 1e-9;
	double x = 5, fValueAtX;

	for (int i = 1; i < nCoef;  ++i) anDeri[i - 1] = anCoef[i] * i;

	while ((fValueAtX = fnCalcFunc(anCoef, nCoef, x)) > fEpsilon)
		x = x - fValueAtX/fnCalcFunc(anDeri, nCoef - 1, x);

	std::cout << std::setprecision(10);
	std::cout << std::fixed << x << std::endl;
}

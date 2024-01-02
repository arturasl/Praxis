#include      <iostream>
#include      <map>
#include      <cmath>

using namespace std;

unsigned int *g_ptnPrimes;
bool *g_ptbSieve;

void sieve(int nTill) {
	for (int i = 0; i < nTill; ++i) {
		g_ptbSieve[i] = true;
	}

	for (int i = 2; i <= sqrt(nTill); ++i) {
		if (g_ptbSieve[i]) {
			for (int j = i * i; j < nTill; j += i) {
				 g_ptbSieve[j] = false;
			}
		}
	}

	unsigned int nLastPrime = 1;
	g_ptnPrimes[0] = 2;

	for (int i = 3; i < nTill; i += 2) {
		if (g_ptbSieve[i]) {
			g_ptnPrimes[nLastPrime++] = i;
		}
	}
}
int fi(int x, int a){
	static map<pair<int, int>, int> MapCache;

	if (a == 1) {
		return x / 2 + (x % 2 != 0);
	}

	pair<int, int> args(x, a);

	if (MapCache.find(args) != MapCache.end()){
		return MapCache[args];
	}

	MapCache[args] = fi(x, a - 1) - fi(x / g_ptnPrimes[a - 1], a - 1);

	return MapCache[args];
}
int n(int x){
	int a = static_cast<int>(sqrt(x));
	return fi(x, a) + a - 1;
}

int main(int argc, char **argv) {
	unsigned int nFind;

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [number]" << std::endl;
		return 1;
	}

	if(EOF == sscanf(argv[1], "%ud", &nFind)) {
		std::cerr << "Could not convert first argument to integer" << std::endl;
		return 1;
	}

	if (nFind <= 1) {
		std::cerr << "Input should be in range [2, 1000000]" << std::endl;
		return 1;
	}

	// sqrt(10e6) = 1000th prime is 7919
	const unsigned int nMaxPrime = 7919;
	g_ptnPrimes = new unsigned int[1000];
	g_ptbSieve = new bool[nMaxPrime + 1];
	sieve(nMaxPrime + 1);

	std::cout << n(nFind) << std::endl;

	delete[] g_ptnPrimes;
	delete[] g_ptbSieve;

	return 0;
}

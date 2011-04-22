// http://programmingpraxis.com/2011/04/22/xref/

#include      <iostream>
#include      <fstream>
#include      <string>
#include      <map>
#include      <list>
#include      <iomanip>
#include      <cstring>

static const char* szAddSymbols = "_";

void fnIgnoreString(std::ifstream &in, char chQuote) {
	char ch;

	while (in.good() && (ch = in.get())) {
		if (ch == chQuote) {
			break;
		}

		// if we encouter '\', eat next character
		if (ch == '\\' && in.good()) {
			ch = in.get();
		}
	}
}
void fnIgnoreNum(std::ifstream &in) {
	char ch;

	while (in.good() && (ch = in.get())) {
		if (!isalnum(ch) && !strchr(szAddSymbols, ch)) {
			break;
		}
	}
}
void fnIgnoreTillNL(std::ifstream &in) {
	char ch;

	while (in.good() && (ch = in.get())) {
		if (ch == '\n') {
			break;
		}
	}
}
void fnIgnoreTillEndComment(std::ifstream &in, int &nLine) {
	char ch1 = 0, ch2;

	while (in.good() && (ch2 = in.get())) {
		if (ch1 == '*' && ch2 == '/') {
			break;
		}

		if (ch2 == '\n') {
			++nLine;
		}

		ch1 = ch2;
	}
}

void fnAddIdentifier(std::map< std::string, std::list<int> > &aIdentifiers, std::string &strIdentifier, int nLine) {
	if (!strIdentifier.empty()) {
		aIdentifiers[strIdentifier].push_back(nLine);
		strIdentifier = "";
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " file_name" << std::endl;
		return 1;
	}

	std::ifstream in(argv[1]);

	if (!in.is_open()) {
		std::cerr << "Could not open file" << std::endl;
		return 1;
	}

	char ch;
	std::string strIdentifier;
	std::map< std::string, std::list<int> > aIdentifiers;
	int nLine = 1;

	while (in.good()) {
		ch = in.get();

		if (ch == '\n') {
			fnAddIdentifier(aIdentifiers, strIdentifier, nLine);

			++nLine;
		} else if (ch == '"' || ch == '\'') {
			fnAddIdentifier(aIdentifiers, strIdentifier, nLine);

			fnIgnoreString(in, ch);
		} else if (ch == '/' && in.good() && in.peek() == '/') {
			fnAddIdentifier(aIdentifiers, strIdentifier, nLine);

			in.get(); // eat second '/'
			fnIgnoreTillNL(in);
			++nLine;
		} else if (ch == '/' && in.good() && in.peek() == '*') {
			fnAddIdentifier(aIdentifiers, strIdentifier, nLine);

			in.get(); // second '/'
			fnIgnoreTillEndComment(in, nLine);
		} else if (!isalnum(ch) && !strchr(szAddSymbols, ch)) {
			fnAddIdentifier(aIdentifiers, strIdentifier, nLine);
		} else if (strIdentifier.empty() && isdigit(ch)) {
			fnIgnoreNum(in);
		} else {
			strIdentifier += ch;
		}
	}

	in.close();

	for (
		std::map< std::string, std::list<int> >::iterator it = aIdentifiers.begin();
		it != aIdentifiers.end();
		++it
	) {
		it->second.sort();
		it->second.unique();

		std::cout << std::left << std::setw(20) << it->first;

		for (
			std::list<int>::const_iterator lineIt = it->second.begin();
			lineIt != it->second.end();
			++lineIt
		) {
			std::cout << ' ' << *lineIt;
		}

		std::cout << std::endl;
	}

	return 0;
}

// http://programmingpraxis.com/2011/05/06/entab-and-detab/

#include      <string.h>
#include      <stdio.h>

int main(int argc, char **argv) {
	int bEntab = 0, nSize = 4;
	int chCur, bStartOfLine = 1, i, nSpaces = 0;

	while (--argc) {
		++argv;
		bEntab = (strcmp(*argv, "e") == 0);
	}

	while ((chCur = getchar()) != EOF) {
		if (bEntab == 1 && chCur == ' ' && bStartOfLine == 1) {
			++nSpaces;

			if (nSpaces == nSize) {
				putchar('\t');
				nSpaces = 0;
			}
		} else if (bEntab == 0 && chCur == '\t' && bStartOfLine == 1) {
			for (i = 0; i < nSize; ++i) {
				putchar(' ');
			}
		} else if (chCur == '\n') {
			putchar(chCur);
			bStartOfLine = 1;
			nSpaces = 0;
		} else {
			putchar(chCur);
			bStartOfLine = 0;
		}
	}

	return 0;
}

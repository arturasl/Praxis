#!/usr/bin/python3
# Solution to http://programmingpraxis.com/2011/07/08/vedic-divisibility/

import sys
import fractions

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.stderr.write('Usage: {0} inches'.format(sys.argv[0]))
        sys.exit(2)

    inches = round(float(sys.argv[1]) * 32) / 32
    feets = int(inches // 12)
    inches -= feets * 12

    full = int(inches)
    inches -= full

    numerator = int(inches * 32)

    if (feets, full, numerator) == (0, 0, 0):
        print('0 feet 0 inches')
    else:
        if feets != 0:
            print(feets, 'foot' if feets == 1 else 'feet', end = ' ')

        if full != 0:
            print(full, end = ' ')

        if numerator != 0 and full != 0:
            print('and', end = ' ')

        if numerator != 0:
            print(fractions.Fraction(numerator, 32), end = ' ')

        if numerator != 0 or full != 0:
                print('inches' if full > 1 or (full == 1 and numerator != 0) else 'inch', end = '')

        print()

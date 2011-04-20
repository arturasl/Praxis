#!/usr/bin/python

# http://programmingpraxis.com/2011/04/15/partition-numbers/

aMem = {0: 1}
aStackNeedto = []


def Update(nParent, nSum):
    if (aStackNeedto[nParent]['Num'] * 2 - aStackNeedto[nParent]['Count'] - 1) // 2 % 2 != 0:
        nSum *= -1

    aStackNeedto[nParent]['Count'] += 1
    aStackNeedto[nParent]['Sum'] += nSum
    aStackNeedto.pop()


def Partition(n):
    aStackNeedto.append({
        'Num': n,
        'Count': 0,
        'Sum': 0,
        'Parent': 0,
        })

    while aStackNeedto:
        nNewParent = len(aStackNeedto) - 1
        aCur = aStackNeedto[nNewParent]

        if aCur['Num'] < 0:
            Update(aCur['Parent'], 0)
        elif aCur['Num'] in aMem:
            Update(aCur['Parent'], aMem[aCur['Num']])
        elif aCur['Count'] == aCur['Num'] * 2:
            aMem[aCur['Num']] = aCur['Sum']
            Update(aCur['Parent'], aMem[aCur['Num']])
        else:
            for k in range(1, aCur['Num'] + 1):
                aStackNeedto.append({
                    'Num': aCur['Num'] - k * (3 * k - 1) / 2,
                    'Count': 0,
                    'Sum': 0,
                    'Parent': nNewParent,
                    })
                aStackNeedto.append({
                    'Num': aCur['Num'] - k * (3 * k + 1) / 2,
                    'Count': 0,
                    'Sum': 0,
                    'Parent': nNewParent,
                    })

    return aMem[n]


print Partition(1000)

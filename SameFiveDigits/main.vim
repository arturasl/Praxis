" http://programmingpraxis.com/2011/04/19/same-five-digits/

" find all 5 digit perfect squares which consist only from 1, 2, 3, 4, 5
" because x1 + x2 + x3 + x4 + x5 = 15 (x_i 1 <= i <= 5 frequency of digit a_i)
" and the only unique way to get this is 1 + 2 + 3 + 4 + 5
let aInitial = []
for i in range(100, 236)
	let aTimes = split(i * i, '\zs')
	if max(aTimes) <= 5 && count(aTimes, '0') == 0
		call add(aInitial, aTimes)
	endif
endfor

" fill up aMatrix with unique triplets
let aMatrix = []
for i in range(0, len(aInitial) - 1)
	for j in range(i + 1, len(aInitial) - 1)
		for k in range(j + 1, len(aInitial) - 1)
			call add(aMatrix, [aInitial[i], aInitial[j], aInitial[k]])
		endfor
	endfor
endfor

" fill aNewMatrix with triplets which consists of triplets that have:
" five unique digits
" five digits are used a different number of time
" five number of times being same as the five digits of the perfect squares
" no digit is used its own number of times
let aNewMatrix = []
for aLine in aMatrix
	let aNewLine = copy(aLine)
	let aCounts = []

	for i in range(1, 5)
		call add(aCounts, count(extend(extend(copy(aLine[0]), aLine[1]), aLine[2]), string(i)))
		call extend(aNewLine, [[i, aCounts[i - 1]]])
	endfor

	let bAdd = 1

	for i in range(1, 5)
		if aCounts[i - 1] == i || count(aCounts, i) != 1
			let bAdd = 0
		endif
	endfor

	if bAdd
		call add(aNewMatrix, aNewLine)
	endif
endfor

" aUniqueOnes will hold pairs so that pair at index i will show how
" many times frequency 1 was with digit i + 1 and that was the last
" line in aNewMatrix with such a property
let aUniqueOnes = [[0, 0], [0, 0], [0, 0], [0, 0], [0, 0]]
for i in range(0, len(aNewMatrix) - 1)
	for j in range(3, 7)
		if aNewMatrix[i][j][1] == 1
			let aUniqueOnes[j - 3][0] += 1
			let aUniqueOnes[j - 3][1] = i
			break
		endif
	endfor
endfor

for a in aUniqueOnes
	if a[0] == 1
		echo 'Output: ' . string(aNewMatrix[a[1]])
	endif
endfor

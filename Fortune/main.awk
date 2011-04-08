# http://programmingpraxis.com/2011/04/05/fortune/
BEGIN{srand()}
rand()<1/++n{l=$0}
END{print l}

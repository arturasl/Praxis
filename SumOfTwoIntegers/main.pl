#!/usr/bin/pl -s
% vim:ft=prolog
% Solution to http://programmingpraxis.com/2011/07/19/sum-of-two-integers/

s([X1 | _], [X2 | _], C, X1, X2) :- C is X1 + X2.
s([X1 | T1], [_ | T2], C, A, B) :- s([X1 | T1], T2, C, A, B).
s([_ | T1], [_ | T2], C, A, B) :- s(T1, T2, C, A, B).
s([X1 | T1], C, A, B) :- s([X1 | T1], T1, C, A, B).

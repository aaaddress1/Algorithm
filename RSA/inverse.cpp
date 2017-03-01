/**
 * @file inverse.cpp
 * @author 10303118a
 * @date 2017/03/01
 **/
#include <stdio.h>

/*
function inverse(a, n)
    t := 0;     newt := 1;    
    r := n;     newr := a;    
    while newr ≠ 0
        quotient := r div newr
        (t, newt) := (newt, t - quotient * newt) 
        (r, newr) := (newr, r - quotient * newr)
    if r > 1 then return "a is not invertible"
    if t < 0 then t := t + n
    return t
*/

int inverse(int a, int n) {
	int t = 0;
	int newt = 1;
	int r = n;
	int newr = a;

	while (newr) {
		int quotient = r / newr;
		int tmp_t = t;
		t = newt;
		newt = tmp_t - quotient * newt;

		int tmp_r = r;
		r = newr;
		newr = tmp_r - quotient * newr;
	}
	if (r > 1) {
		puts("a is not invertible");
		return -1;
	}
	if (t < 0) 	
		t = t + n;
	return t;
}

int main(void) {
	printf("%d\n", inverse(11,24));
	return 0;
}
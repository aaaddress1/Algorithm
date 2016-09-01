'''
Brute Force RC4 Secret (Find key and plantext), by. aaaddress1.
date: 2016/9/1
'''
from brute import brute
import re

def rc4crypt( data, key ):
    s = range(256)
    j = 0
    keylen = len(key)
    for i in range(256):
        j = ( j + s[i] + ord(key[ i % keylen ]) ) % 256
        s[i] ,s[j] = s[j] ,s[i]
    
    i = j = 0
    out = ''
    for p in range(len(data)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i],s[j] = s[j],s[i]
        out += chr( ord(data[p]) ^ s[ (s[i] + s[j]) % 256 ])
    return out

def checkingASCII( s ):
    for i in s:
        if (ord(i) >= 0x7f) or (ord(i) < 0x20):
            return False
    return True

def bruteRC4( secret, keyMaxLen, regPattern ):

    for s in brute(length=keyMaxLen):
        tmp = rc4crypt( secret, s )
        if checkingASCII(tmp):
            if re.match( regPattern, tmp):
                print 'key is "%s"' % s
                print 'plan text = "%s"' % tmp

    print 'brute force finish.'
    return 

bruteRC4( rc4crypt('gg in in der','adr'), 5, 'gg.*?' )
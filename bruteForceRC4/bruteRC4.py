'''
Brute Force RC4 Secret (Find key and plantext), by. aaaddress1.
date: 2016/9/1
'''
from brute import brute
import re
import time
 
def getSBoxFromKey( key, keylen ):
    s = range(256)
    j = 0
    for i in range(256):
        j = ( j + s[i] + ord(key[ i % keylen ]) ) % 256
        s[i] ,s[j] = s[j] ,s[i]
    return s

def rc4crypt( data, key ):
    s = getSBoxFromKey( key, len(key) )
    i = j = 0
    out = ''
    for p in range(len(data)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i],s[j] = s[j],s[i]
        out += chr( ord(data[p]) ^ s[ (s[i] + s[j]) % 256 ])
    return out

def bruteRC4decrypt( data, key ):
    s = getSBoxFromKey( key, len(key) )
    i = j = 0
    out = ''
    for p in range(len(data)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i],s[j] = s[j],s[i]

        tmp = ord(data[p]) ^ s[ (s[i] + s[j]) % 256 ]
        if (tmp < 0x7f) and (tmp >= 0x20):
            out += chr( tmp )
        else:
            return ''
    return out

def bruteRC4( secret, keyMaxLen, regPattern ):
    tStart = time.time()
    for s in brute(length=keyMaxLen):
        tmp = bruteRC4decrypt( secret, s )
        if not tmp:
            continue

        if re.match( regPattern, tmp):
            print 'found a result in %f s' % ( time.time() - tStart )
            print 'key is "%s"' % s
            print 'plan text = "%s"' % tmp

    print 'brute force finish.'
    return;

testDeta = rc4crypt('gg in in der','adr')
bruteRC4( testDeta, 5, 'gg.*?' )
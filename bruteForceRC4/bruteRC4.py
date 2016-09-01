'''
Brute Force RC4 Secret (Find key and plantext), by. aaaddress1.
fixed PEP8, add parallel brute force, by louie.lu.
date: 2016/9/1
'''
from brute import brute
import re
import time
import multiprocessing

CHUNKS_NUM = 1024
POOL_SIZE = 10


def getSBoxFromKey(key, keylen):
    s = range(256)
    j = 0
    for i in range(256):
        j = (j + s[i] + ord(key[i % keylen])) % 256
        s[i], s[j] = s[j], s[i]
    return s


def rc4crypt(data, key):
    s = getSBoxFromKey(key, len(key))
    i = j = 0
    out = ''
    for p in range(len(data)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i], s[j] = s[j], s[i]
        out += chr(ord(data[p]) ^ s[(s[i] + s[j]) % 256])
    return out


def bruteRC4decrypt(data, key):
    s = getSBoxFromKey(key, len(key))
    i = j = 0
    out = ''
    for p in range(len(data)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i], s[j] = s[j], s[i]

        tmp = ord(data[p]) ^ s[(s[i] + s[j]) % 256]
        if (tmp < 0x7f) and (tmp >= 0x20):
            out += chr(tmp)
        else:
            return ''
    return out


def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]


def _bruteRC4(slice_, secret, regPattern, event):
    for s in slice_:
        tmp = bruteRC4decrypt(secret, s)
        if not tmp:
            continue

        if re.match(regPattern, tmp):
            event.set()
            print('[*]\tkey is "%s"' % (s))
            print('[*]\tplan text = "%s"' % (tmp))


def bruteRC4(secret, keyMaxLen, regPattern):
    tStart = time.time()

    print('[*] Preparing brute list')
    brute_list = list(chunks(list(brute(length=keyMaxLen)), CHUNKS_NUM))
    pool = multiprocessing.Pool(POOL_SIZE)
    manager = multiprocessing.Manager()
    event = manager.Event()

    print('[*] Start brute force')
    for b in brute_list:
        pool.apply_async(_bruteRC4, (b, secret, regPattern, event))
    pool.close()

    event.wait()
    pool.terminate()

    print('[*] found a result in %f s' % (time.time() - tStart))


if __name__ == '__main__':
    print('[*] Generate test serect key')
    testDeta = rc4crypt('gg in in der', 'adr')

    bruteRC4(testDeta, 3, 'gg.*?')
    print('[*] Brute force end.')

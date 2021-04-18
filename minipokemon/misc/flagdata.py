loop = '''0,0
2,2
3,6
4,2
5,6
6,2
8,1
3,0
9,5
8,3
7,6
9,9
8,7
6,8
7,9
2,8
5,7
1,9
0,6
2,3
1,4'''
loop = loop.replace(',','').replace('\n','')
loop = loop[-2:] + loop[:-2]
loop = int(loop[::-1])
l = []
while len(l) < 24:
    l.append(loop % 64)
    loop //= 64
l = l[::-1]

print(l)

import string
flag = 'PCTF{5EEth4tFURR3Tw4lcc}'
alphabet = string.ascii_uppercase + string.ascii_lowercase + string.digits + '{}'
flag = [alphabet.index(i) for i in flag]

flag = [i^j for i,j in zip(flag, l)]
print(flag)

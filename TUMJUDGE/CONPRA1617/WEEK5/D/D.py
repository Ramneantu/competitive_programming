def f(n):
    l = map(int, [e for e in map(str,' '.join(str(n))) if e is not ' '])
    nr = 0
    b = 1
    for i in xrange(len(l)-1, -1, -1):
        nr += l[i]*b
        b *= 8
    return nr

def g(x):
    return (2+x)%13+1



'''
N = 8**(2*10**5)
print 20
for t in xrange(20):
    sn = str(N)
    S = ""
    for i in xrange(len(sn)):
        if int(sn[i]) >= 8:
            S += '7'
        else:
            S += sn[i]
    print S
'''

t = int(raw_input().strip())
for _t in xrange(t):
    x = int(raw_input())
    print "days_8 =",x,"days_10 =", f(x), " day =", g(f(x))

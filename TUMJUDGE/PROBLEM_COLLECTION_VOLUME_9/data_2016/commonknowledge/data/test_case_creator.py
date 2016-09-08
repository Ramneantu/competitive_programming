def create_case(n):
   with open("secret/%d.in"%n, 'w') as f:
     f.write("%d\n"%n)
     
   with open("secret/%d.ans"%n, 'w') as f:
     f.write("%d\n"%(8**n))
     
for n in xrange(1,21):
    if n != 10 and n!= 13:#samples!
        create_case(n)
 

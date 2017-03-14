import sys

sum = 0
for line in sys.stdin:
    sum += int(line.strip())
print str(sum)[:10]

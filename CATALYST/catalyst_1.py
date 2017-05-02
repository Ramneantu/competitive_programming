import math

def l2(x,y,z,w):
    return math.sqrt((x-z)**2 + (y-w)**2)

def read():
    stations = []
    d = {}

    nr_stations = int(input())
    for i in range(nr_stations):
        line = input().split(' ')
        station_name = line[0]
        stations.append(station_name)
        x, y = float(line[1]), float(line[2])
        d[station_name] = (i, x, y)
    start, goal = input().split(' ')
    return d, stations


d, stations = read()
for k,v in d.items():
    print(k, v)
print(stations)

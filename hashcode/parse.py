from objects import *


def read_input(fname):
	with open(fname, 'r') as f:
	    lid = 0
	    lines = f.read().split('\n')
	    V, E, R, C, X = map(int, lines[lid].split())
	    lid += 1
	    
	    # create video objects
	    video_sizes = list(map(int, lines[lid].split()))
	    videos = []
	    for i in range(V):
	        videos.append(Video(i, video_sizes[i]))
	    
	    lid += 1
	    
	    # create endpoint objects
	    cs = {}
	    endpoints = {}
	    for e in range(E):
	        endpoints[e] = {'latency' : None,
	                       'nr_cache_servers' : None,
	                       'cache_servers' : {}
	                      }
	        endpoints[e]['latency'], endpoints[e]['nr_cache_servers'] = map(int, lines[lid].split())        
	        lid += 1
	        for k in range(endpoints[e]['nr_cache_servers']):
	            c, L_c = map(int, lines[lid].split())
	            lid += 1
	            endpoints[e]['cache_servers'][c] = L_c
	            
	            # create cache object
	            if c not in cs:
	                cs[c] = CacheServer(c, X)
	        
	    # read requests
	    endpoint_to_requests = {}
	    requests = []
	    request_objs = []
	    for r in range(R):
	        R_v, R_e, R_n = map(int, lines[lid].split())
	        requests.append([R_v, R_e, R_n])
	        if R_e not in endpoint_to_requests:
	            endpoint_to_requests[R_e] = []
	        endpoint_to_requests[R_e].append(r)
	        lid += 1
	        request_objs.append(Request(videos[R_v], R_n))
	        

	    # map requests to endpoint objects
	    endpoint_objs = []
	    for k,v in endpoints.items():
	        if v['nr_cache_servers'] > 0:
	            
	            # create list of cache references
	            tmp_cs = []
	            for c in v['cache_servers'].keys():
	                tmp_cs.append((cs[c],v['cache_servers'][c]))
	                
	            # create list of request references
	            tmp_rs = []
	            for r in endpoint_to_requests[k]:
	                tmp_rs.append(request_objs[r])
	            endpoint_objs.append(EndPoint(k, tmp_cs, tmp_rs))
	        
	    # print(requests)
	    # # test output        
	    # print(V, E, R, C ,X)
	    # for v in videos:
	    #     print('Video %d has size %dMB' % (v.id, v.size))
	    # #print(' '.join(map(str,video_sizes)))
	    # for k,v in endpoints.items():
	    #     print('Endpoint %d has %dms data center latency and is connected to %d caches:' % (k, v['latency'], v['nr_cache_servers']))
	    #     for c,w in v['cache_servers'].items():
	    #         print('The latency (of endpoint %d) to cache %d is %dms.' % (k, c, w))
	    # for r in requests:
	    #     print('%d requests for video %d coming from endpoint %d.' % (r[2], r[0], r[1]))

	    return endpoint_objs, cs.values()

        
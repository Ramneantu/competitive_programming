class Video:
    def __init__(self,id, size):
        self.id = id
        self.size = size


class CacheServer:
    def __init__(self, id, capacity):
        self.id = id
        self.capacity = capacity
        self.ava_space = capacity
        self.videos = []
        self.vidids = set()

    def addVideo(self, video):
        if video.size > self.ava_space:
            raise Exception('video too large')
        self.videos.append(video)
        self.ava_space -= video.size
        self.vidids.add(video.id)


class EndPoint:
    def __init__(self, id, css, req):
        self.id = id
        self.caches = css
        self.caches.sort(key=lambda a : a[1])
        self.req = req
        self.req.sort(key=lambda a : a.nrreq)


class Request:
    def __init__(self, video, nrreq):
        self.video = video
        self.nrreq = nrreq

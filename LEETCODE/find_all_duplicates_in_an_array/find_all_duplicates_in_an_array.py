import sys

    def findDuplicates(self, nums):
        n = len(nums)
        nums = [0] + nums
        duplicates = []
        for i in xrange(1,len(nums)):
            if nums[i] > n:
                next_pos = nums[i] - n
            else:
                next_pos = nums[i]
            if nums[next_pos] > n:
                duplicates += [next_pos]
            else:
                nums[next_pos] += n
        return duplicates


t = int(raw_input())
for _t in xrange(t):
    A = [0] + map(int,raw_input().strip().split())
    duplicates = get_duplicates(A)
    if not duplicates:
        print "No duplicates!"
    else:
        print "duplicates:", ' '.join(map(str,duplicates))

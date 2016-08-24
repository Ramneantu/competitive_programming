'''
Problem Statement: https://www.hackerrank.com/challenges/attribute-parser
'''

import re

def get_attributes(line):
    # return end position in line and a list of (attribute, value) tuples
    attribute_found = True
    attrs = []
    while attribute_found:
        m = re.search(r'(\w+) = "([^"]+)"', line)
        if m:
            attribute_found = True
            end = m.end()
            attr_val = m.groups()
            attrs.append(attr_val)
            line = line[end:]
        else:
            attribute_found = False
    return line, attrs

def get_tag_start(line):
    m = re.search(r'<(\w+)', line)
    tag = None
    if m:
        tag = m.groups()[0]
        line = line[m.end():]
        return line, tag
    else:
        return None

def get_tag_end(line):
    m = re.search(r'</(\w+)>', line)
    tag = None
    end = None
    if m:
        tag = m.groups()[0]
        line = line[m.end():]
        return line, tag
    else:
        return None


def remove_from_absolute_tag(tag):
    global absolute_tag
    absolute_tag = absolute_tag[:len(absolute_tag)-len(tag)]
    if len(absolute_tag) > 0 and absolute_tag[-1] == '.':
        absolute_tag = absolute_tag[:-1]

def append_to_absolute_tag(tag):
    global absolute_tag
    if absolute_tag == "":
        absolute_tag += tag
    else:
        absolute_tag += '.' + tag

attributes = {}
absolute_tag = ""
n, q = map(int, raw_input().split(' '))
for i in xrange(n):
    line = raw_input().strip()

    while line:
        res = get_tag_start(line)
        if res:
            line, tag = res
            append_to_absolute_tag(tag)

        res = get_attributes(line)
        if res:
            line, attrs = res
            for a in attrs:
                attributes[absolute_tag+'~'+a[0]] = a[1]

        res = get_tag_end(line)
        if res:
            line, tag = res
            remove_from_absolute_tag(tag)
        if line and line[0] == '>':
            line = line[1:]
        #print "line, attributes", line#, attributes

for i in xrange(q):
    attribute = raw_input().strip()
    if attribute in attributes:
        print attributes[attribute]
    else:
        print "Not Found!"

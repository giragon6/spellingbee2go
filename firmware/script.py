import re

with open('english.txt') as f:
    lines = f.readlines()

p = re.compile('^([a-z]+)\n$')

matches = [ p.match(w) for w in lines ]
filtered = [ m.group(1) for m in matches if m ]

with open('filtered.txt', 'w+') as f:
    for w in filtered:
        f.write(f'{w}\n')
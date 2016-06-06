import sys, os, subprocess
from render import get_path_from_test_name

def run(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    p.wait()
    return p.stdout.read().strip()

def get_cpu():
    cmd = 'sysctl -n machdep.cpu.brand_string'
    return run(cmd.split())
    
def get_machine():
    cmd = 'sysctl -n hw.model'
    return run(cmd.split())

def get_log(path):
    lines = []
    with open(path, 'rb') as f:
        for line in f.readlines():
            if line.startswith('# '):
                continue
            lines.append(line)
    return lines
    
def get_tests(log):
    tests = []
    for line in log:
        if not line.startswith('## '):
            continue
        tokens = line.strip().split(' ', 1)
        tests.append(tokens[1])
    return tests

def sub(x):
    if x[0] in ('|', '#'):
        return x
    return '<sub>%s</sub>' %x
        
if __name__ == '__main__':

    log1    = sys.argv[1]
    log2    = sys.argv[2]
    title   = sys.argv[3]
    
    print "# %s benchmarks" % title
    print ""
    print "Benchmarks run on a:", get_machine(), " ", get_cpu() 
    print ""

    lines1 = get_log(log1)
    lines2 = get_log(log2)

    print "# Images"

    tests1 = get_tests(lines1)
    tests2 = get_tests(lines2)
    for test1, test2 in zip(tests1,tests2):
        if ('dmHashTable' in test1) or ('dmHashTable' in test2):
            continue
        print '<img src="%s" alt="%s" width="350">' % (get_path_from_test_name(test1), test1)
        print '<img src="%s" alt="%s" width="350">' % (get_path_from_test_name(test2), test2)
        print '<br/>'

    print "# Tables"

    print ""
    print "### %s" % log1
    print "<sub>"
    for line in lines1:
        if 'dmHashTable' in line:
            continue
        tokens = line.split()
        tokens = map(sub, tokens)
        print " ".join(tokens)

    print ""
    print "### %s" % log2
    print "<sub>"
    for line in lines2:
        if 'dmHashTable' in line:
            continue
        tokens = line.split()
        tokens = map(sub, tokens)
        print " ".join(tokens)

    
    
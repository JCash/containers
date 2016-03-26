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

    log     = sys.argv[1]
    title   = sys.argv[2]
    
    print "# %s benchmarks" % title
    print ""
    print "Benchmarks run on a:", get_machine(), " ", get_cpu() 
    print ""

    lines = get_log(log)

    print "# Images"

    tests = get_tests(lines)
    for test in tests:
        print '<img src="%s" alt="%s" width="350">' % (get_path_from_test_name(test), test)

    print "# Tables"
    
    print "<sub>"
    for line in lines:
        tokens = line.split()
        tokens = map(sub, tokens)
        print " ".join(tokens)
    
    
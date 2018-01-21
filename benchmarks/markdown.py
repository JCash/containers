import sys, os, subprocess


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

def get_path_from_test_name(category, name):
    return './images/%s/%s.png' % (category, name.lower().replace(' ', '_'))

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

    title   = sys.argv[1]
    category= sys.argv[2]
    log     = sys.argv[3]

    print "# %s benchmarks" % title
    print ""
    print "Benchmarks run on a:", get_machine(), " ", get_cpu() 
    print ""

    lines = get_log(log)

    print "# Images"

    tests = get_tests(lines)
    i = 0
    for test in tests:
        if ('dmHashTable' in test):
            continue
        if (i % 2) == 0:
            print '_\n<br/>'
        i = i + 1
        print '<img src="%s" alt="%s" width="350">' % (get_path_from_test_name(category, test), test)


    print ""
    print "# Tables"
    print ""

    print "### %s" % log
    print ""
    for line in lines:
        if 'dmHashTable' in line:
            continue
        tokens = line.split()
        tokens = map(sub, tokens)
        print " ".join(tokens)

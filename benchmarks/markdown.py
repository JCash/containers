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

def get_log(path):
    lines = []
    with open(path, 'rb') as f:
        for line in f.readlines():
            if line.startswith('# '):
                continue
            lines.append(line)
    return lines
        
if __name__ == '__main__':

    log     = sys.argv[1]
    title   = sys.argv[2]
    
    print "# %s benchmarks" % title
    print ""
    print "Benchmarks run on a:", get_machine(), " ", get_cpu() 
    print ""
    print "".join(get_log(log))

import sys, os, time, subprocess

if __name__ == '__main__':
    tstart = time.time()
    p = subprocess.Popen(sys.argv[1:])
    p.wait()
    tend = time.time()
    print("%s took %f ms" % (sys.argv[1], (tend-tstart)*1000.0))

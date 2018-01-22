#! /usr/bin/python

import os
import sys
import subprocess
import random
from collections import OrderedDict
import numpy as np
import matplotlib.pyplot as plt

def convert_time(t, unit):
    if unit == 'ns':
        return t / 1000000000.0
    if unit == '\xc2\xb5s':
        return t / 1000000.0
    if unit == 'ms':
        return t / 1000.0
    return t
    
def parse_log(path):
    tests = []
    with open(path, 'rb') as f:
        lines = f.readlines()
        
        headers = None
        test = None
        for line in lines:
            line = line.strip()
            if not line:
                continue
            tokens = line.split(' ', 1)
            if tokens[0] == '##':
                test = OrderedDict()
                test['name'] = tokens[1]
                test['counts'] = list()
                headers = None        
                tests.append(test)
                continue
            elif tokens[0] == '#':
                continue
            
            tokens = line.split('|')
            tokens = [ x.strip() for x in tokens if x]
            
            if tokens[0][0] == '-':
                continue
            if tokens[0] == 'counts': # the headers line
                headers = tokens[1:]
                test['headers'] = OrderedDict()
                for header in headers:
                    test['headers'][header] = list()
                continue
                
            count = int(tokens[0])
            test['counts'].append(count)
            for i, header in enumerate(headers):
                timingtokens = tokens[i+1].split()
                time        = float(timingtokens[0])
                unit        = timingtokens[1] if (len(timingtokens) > 1 ) else '#'
                time        = convert_time(time, unit)
                test['headers'][header].append( time )
                test['unit'] = unit

    return tests

def random_color():
    r = 100 + random.randint(0, 155) % 155
    g = 100 + random.randint(0, 155)*3 % 155
    b = 100 + random.randint(0, 155)*7 % 155
    return '#%0x%0x%0x' % (r, g, b)

def render_matplotlib(test, outputdir):
    random.seed(0)

    unit = test['unit']
    scale = 1.0
    if unit == 'ms':
        scale = 1000.0
    elif unit == 'kb':
        scale = 1
    elif unit == '\xc2\xb5s':
        scale = 1000000.0
    
    n = len(test['counts'])
    index = np.arange(n)
    
    bar_width = 1.0 / (len(test['headers']) + 1)
    opacity = 0.8
    
    fig, _ = plt.subplots()
    
    #colormap = plt.cm.gist_ncar
    #plt.gca().set_prop_cycle([colormap(i) for i in np.linspace(0, 0.9, len(test['headers']))])

    bars = []
    offset = 0
    markers='ov*sxd'
    for i, (name, values) in enumerate(test['headers'].iteritems()):
        values = [x * scale for x in values]
        plt.plot(test['counts'], values, label=name, color=random_color(), marker=markers[i % len(markers)])
        offset += bar_width
    
    plt.xlabel('Elements')
    plt.ylabel(test['unit'])
    plt.title(test['name'])
    plt.legend(loc=[0.03, 1.0 - len(test['headers']) * 0.068])
     
    #plt.tight_layout()
    
    outpath = '%s/%s.png' % (outputdir, test['name'].lower().replace(' ', '_'))
    plt.savefig(outpath)
    plt.close()

    print "Wrote", outpath
            
if __name__ == '__main__':
    tests = parse_log(sys.argv[1])
    outputdir = '.'
    if len(sys.argv) > 2:
        outputdir = sys.argv[2]
    if not os.path.exists(outputdir):
        os.makedirs(outputdir)
    
    for test in tests:
        render_matplotlib(test, outputdir)
    
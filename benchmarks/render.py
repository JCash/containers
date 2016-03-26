#! /usr/bin/python

import os
import sys
import subprocess
import random
from collections import OrderedDict
import plotly.plotly as py
from plotly.graph_objs import Data, Figure, XAxis, YAxis, Bar, Layout, Font, Legend
import pygal
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
                unit        = timingtokens[1]
                time        = convert_time(time, unit)
                test['headers'][header].append( time )
                test['unit'] = unit

    return tests


def render(test):
    scale = 1.0 #test['scale']
    unit = test['unit']
    
    bars = []
    for name, values in test['headers'].iteritems():
        values = map(lambda x: x * scale, values)

        bar = Bar(  x=test['counts'],
                    y=values,
                    name=name )
        bars.append(bar)

    layout = Layout(title=test['name'],
                    font=Font(family='Raleway, sans-serif'),
                    showlegend=True,
                    barmode='group',
                    bargap=0.15,
                    bargroupgap=0.1,
                    legend=Legend(x=0, y=1.0),
                    xaxis=XAxis(title='Num Elements', type='category'),
                    yaxis=YAxis(title=unit)
                    )
    
    data = Data(bars)
    fig = Figure(data=data, layout=layout)
    outpath = get_path_from_test_name(test['name'])
    py.image.save_as(fig, outpath)
    
    print "Wrote", outpath
    
def get_path_from_test_name(name):
    return '../images/%s.png' % name.lower().replace(' ', '_')

def render_pygal(test):

    chart = pygal.Bar()
    chart.x_labels = map(str, test['counts'])
    chart.title = test['name']
    
    unit = test['unit']
    chart.value_formatter = lambda x: '%.2f %s' % ((x if x is not None else ''), unit)
    
    scale = 1.0 #test['scale']
    
    for name, values in test['headers'].iteritems():
        chart.add(name, map(lambda x: x * scale, values))
        
    chart.render()
    #outpath = '../images/%s%s.svg' % (category, suffix)
    #chart.render_to_file(outpath)
    outpath = '../images/%s.png' % test['name'].lower().replace(' ', '_')
    chart.render_to_png(outpath)
    print "Wrote", outpath

def random_color():
    r = 100 + random.randint(0, 155) % 155
    g = 100 + random.randint(0, 155)*3 % 155
    b = 100 + random.randint(0, 155)*7 % 155
    return '#%0x%0x%0x' % (r, g, b)

def render_matplotlib(test):
    random.seed(0)

    unit = test['unit']
    scale = 1.0
    if unit in ('ms', 'kb'):
        scale = 1000.0
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
        """plt.bar(index + offset, values, bar_width,
                     alpha=opacity,
                     #color=random_color(),
                     label=name)
        """
        plt.plot(test['counts'], values, label=name, color=random_color(), marker=markers[i % len(markers)])
        offset += bar_width
    
    plt.xlabel('Elements')
    plt.ylabel(test['unit'])
    plt.title(test['name'])
    plt.legend(loc=[0.03, 1.0 - len(test['headers']) * 0.068])
     
    #plt.tight_layout()
    
    outpath = '../images/%s.png' % test['name'].lower().replace(' ', '_')
    plt.savefig(outpath)

    print "Wrote", outpath
            
if __name__ == '__main__':
    tests = parse_log(sys.argv[1])
    for test in tests:
        render_matplotlib(test)
    
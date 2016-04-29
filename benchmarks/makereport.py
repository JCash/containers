#! /usr/bin/python

import os
import sys
import time
import subprocess
from collections import OrderedDict


def find_time_unit(t):
    if t < 0.000001:
        return 'ns'
    if t < 0.001:
        return '\xc2\xb5s'
    if t < 0.1:
        return 'ms'
    return 's'

def convert_time(t, unit):
    if unit == 'ns':
        return t / 1000000000.0
    if unit == '\xc2\xb5s':
        return t / 1000000.0
    if unit == 'ms':
        return t / 1000.0
    return t


def run_test(test, report, *args):
    cmd = [test]+map(str, args)
    print "# cmd:", ' '.join(cmd)
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    p.wait()
    d = p.stdout.read()
    
    lines = d.replace('\r', '\n').split('\n')
    
    for line in lines[1:]:
        tokens = line.split()
        if not tokens:
            continue
        
        if tokens[0][0] == '#':
            print line
            continue
        
        # print [ (i, x) for (i, x) in enumerate(tokens) ]
            
        name = tokens[0] # container name
        testname = tokens[1]
        if not testname in report['timings']:
            report['memory'][testname]      = OrderedDict()
            report['allocations'][testname] = OrderedDict()
            report['timings'][testname]     = OrderedDict()
        
        if not name in report['timings'][testname]:
            report['memory'][testname][name]      = list()
            report['allocations'][testname][name] = list()
            report['timings'][testname][name]     = list()
            
        if 'used' == tokens[2]:
            memory      = int(tokens[3])
            allocations = int(tokens[6])
            report['memory'][testname][name].append(memory)
            report['allocations'][testname][name].append(allocations)
            
        else: # timings
            index       = tokens.index("min:") # avg, median, min, max
            timing      = float(tokens[index+1])
            unit        = tokens[index+2]
            timing      = convert_time(timing, unit)
            report['timings'][testname][name].append(timing)
            
        #print tokens



"""

* memory usage
* num allocations
* avg time


fmt:
libname testname    used 8371052 bytes in 497 allocations
libname testname    iterations: 1    avg: 51.633 ms    median: 51.633 ms    min: 51.633 ms    max: 51.633 ms

"""

def collect_table_data(counts, report, tabledata):

    for category, tests in report.iteritems():
        for testname, results in tests.iteritems():
            if testname in ['title', 'scale', 'unit']:
                continue
            
            if not category in tabledata:
                tabledata[category] = OrderedDict()
            if not testname in tabledata[category]:
                tabledata[category][testname] = OrderedDict()
            
            if not 'counts' in tabledata[category][testname]:
                tabledata[category][testname]['counts'] = list()
            tabledata[category][testname]['counts'].extend(counts)
            
            for name, values in results.iteritems():
                if not name in tabledata[category][testname]:
                    tabledata[category][testname][name] = list()
                if name in ['title', 'scale', 'unit']:
                    tabledata[category][testname][name] = values
                    continue
                tabledata[category][testname][name].extend(values)
            

def make_table_report(data):
    usediff = False

    for category, tests in data.iteritems():
    
        totaldiff = 0.0
    
        for testname, results in tests.iteritems():
            if testname in ['title', 'scale', 'formatter', 'unit']:
                continue
            
            columns = list()
            for name, values in results.iteritems():
                if len(values) < len(results['counts']):
                    values.extend( (len(results['counts']) - len(values)) * [0.0])
                columns.append( [name]+values )
            
            formatter = tests['formatter']
            scale = tests['scale']
            title = tests['title']
            
            matrix = zip(*columns)
            
            rows = [list(matrix[0])]
            for row in matrix[1:]:
                rows.append( [str(row[0])] + map(formatter, map(lambda x: scale * x, row[1:]) ) )
            
            lengths = [0] * len(rows[0])
            for row in rows:
                for ic, v in enumerate(row):
                    lengths[ic] = max(lengths[ic], len(v))
            
            # header
            headers = []
            headersunderline = []
            for ic, v in enumerate(rows[0]):
                length = lengths[ic]
                headers.append( ' ' + v.ljust(length) + ' ' )
                if ic == 0:
                    headersunderline.append( '-' * (length + 1) + ':' )
                else:
                    headersunderline.append( '-' * (length + 2) )
                    
            print "## " + title + " " + testname
            print ""
            print '|' + '|'.join(headers) + '|'
            print '|' + '|'.join(headersunderline) + '|'

            for row in rows[1:]:
                values = []
                for ic, v in enumerate(row):
                    length = lengths[ic]
                    value = v.ljust(length)
                    values.append( ' ' + value + ' ')
                
                print '|' + '|'.join(values) + '|',
                if not usediff:
                    print ""
                
                diff = 0.0
                if usediff:
                    tokens = values[-1].split()
                    diff = float(tokens[0]) - float(values[-2].split()[0])
                    print diff, tokens[1]
                    
            totaldiff += diff
            
            print ""
            print ""
        
        if usediff:
            print "Total diff:", totaldiff



if __name__ == '__main__':
    timestart = time.time()
    
    tests = [   #'./build/ht_stl_map',
                './build/ht_stl_unordered_map',
                './build/ht_boost_unordered_map',
                './build/ht_eastl_hash_map',
                #'./build/ht_boost_flat_map',
                './build/ht_google_dense_hash_map',
                #'./build/ht_google_sparse_hash_map',
                './build/ht_dm_hashtable',
                #'./build/ht_jc_hashtable_ch',
                #'./build/ht_jc_hashtable_rh',
                './build/ht_jc_hashtable',]
                
    testsx = [   './build/ht_boost_flat_map',
                #'./build/ht_dm_hashtable',
                './build/ht_jc_hashtable']
    testsx = [   './build/ht_google_dense_hash_map',
                './build/ht_dm_hashtable',
                './build/ht_jc_hashtable_ch',
                './build/ht_jc_hashtable_oa',
                './build/ht_jc_hashtable_rh']
    
    iterations = 10
    counts = [1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000]
    #counts = [1000, 5000, 10000, 20000, 30000]
    #counts = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000]
    #counts = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 10000, 20000, 30000, 40000]
    #counts = [1000, 2000, 3000, 4000, 5000, 6000]
    #counts = [10000]
    #counts = [100]
    
    tabledata = OrderedDict()
    tabledata['timings'] = OrderedDict()
    tabledata['memory'] = OrderedDict()
    tabledata['allocations'] = OrderedDict()
    
    report = OrderedDict()
    report['timings'] = OrderedDict()
    report['memory'] = OrderedDict()
    report['allocations'] = OrderedDict()
    
    report['timings']['title'] = 'Timings (microseconds)'
    report['timings']['scale'] = 1000000.0
    report['timings']['unit']  = 'us'
    report['memory']['title'] = 'Memory (kb)'
    report['memory']['scale'] = 1 / 1024.0
    report['memory']['unit']  = 'kb'
    report['allocations']['title'] = '# Allocations'
    report['allocations']['scale'] = 1
    report['allocations']['unit']  = ''
        
    for count in counts:
        for testname in tests:
            run_test( testname, report, count, iterations )
    collect_table_data(counts, report, tabledata)

    if './build/ht_boost_flat_map' in tests:
        tests.remove('./build/ht_boost_flat_map')

    if False:
        iterations = 2
        counts = [1000000, 2000000, 3000000, 4000000, 5000000]
        #counts = [1000000]
        #counts = [1000]
        
        report = OrderedDict()
        report['timings'] = OrderedDict()
        report['memory'] = OrderedDict()
        report['allocations'] = OrderedDict()
        
        report['timings']['title'] = 'Timings (milliseconds)'
        report['timings']['scale'] = 1000.0
        report['timings']['unit']  = 'ms'
        report['memory']['title'] = 'Memory (kb)'
        report['memory']['scale'] = 1 / 1024.0
        report['memory']['unit']  = 'kb'
        report['allocations']['title'] = '# Allocations'
        report['allocations']['scale'] = 1
        report['allocations']['unit']  = ''
            
        for count in counts:
            for testname in tests:
                run_test( testname, report, count, iterations )
                
        collect_table_data(counts, report, tabledata)

    
    tabledata['timings']['title'] = 'Timings'
    tabledata['timings']['scale'] = 1000.0
    tabledata['timings']['formatter'] = lambda x: '%.4f ms' % x
    tabledata['memory']['title'] = 'Memory'
    tabledata['memory']['scale'] = 1 / 1024.0
    tabledata['memory']['formatter']  = lambda x: '%d kb' % x
    tabledata['allocations']['title'] = '# Allocations'
    tabledata['allocations']['scale'] = 1
    tabledata['allocations']['formatter'] = lambda x: str(x)
    
    del tabledata['memory']
    del tabledata['allocations']
    make_table_report(tabledata)
    
    timeend = time.time()
    print "# Report made in %f seconds" % (timeend - timestart)
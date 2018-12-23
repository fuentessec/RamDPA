import sys
import scipy.io
import numpy as np

def printFloat (matrix):
    min = sys.float_info.max;
    max = sys.float_info.min;
    
    for tr in matrix:
        for val in tr:
            if val > max:
                max = val;
            if val < min:
                min = val;
            if val.astype(int) != val:
                print (val);    

    print ('max value=' ,max);
    print ('min value=' ,min);


def native_to_matlab(prefix):
    tracedata = np.load(prefix + '_traces.npy')
    textin = np.load(prefix + '_textin.npy')
    textout = np.load(prefix + '_textout.npy')
    key = np.load(prefix + '_keylist.npy')

    tracedataRaw = (tracedata * 1024) + 83;
    
    
    np.savetxt('key.txt', key, fmt='%03.3d');
    np.savetxt('data.txt', textin, fmt='%03.3d');
    np.savetxt('out.txt', textout, fmt='%03.3d');
    
    np.savetxt('keyHex.txt', key, fmt='%02.2x');
    np.savetxt('dataHex.txt', textin, fmt='%02.2x');
    np.savetxt('outHex.txt', textout, fmt='%02.2x');
    
    np.savetxt('traces.txt', tracedata);
    np.savetxt('tracesRaw.txt', tracedataRaw);
    np.savetxt('tracesRawIntPrint.txt', tracedataRaw, fmt='%03.3d');

    printFloat (tracedataRaw)
    
    #print (key.dtype);
    #print (tracedataRaw.dtype);
    #tracedataRawInt = tracedataRaw.astype(int);
    #print (tracedataRaw == tracedataRawInt);
    

 #   scipy.io.savemat('fileout.mat', {
 #    "traces":tracedata,
 #    "textin":textin,
 #    "textout":textout,
 #    "key":key
 #   })

prefix = r'2016.06.01-09.41.16'
#Can point to full directory like:
#prefix = r'C:\Temp\demo\traces_capdir48\knownrand_fixed\knownrand_fixed_P48_data\traces\2016.02.24-19.07.03'

native_to_matlab(prefix)

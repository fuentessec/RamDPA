import scipy.io
import numpy as np

def native_to_matlab(prefix):
    tracedata = np.load(prefix + '_traces.npy')
    textin = np.load(prefix + '_textin.npy')
    textout = np.load(prefix + '_textout.npy')
    key = np.load(prefix + '_keylist.npy')

    scipy.io.savemat('fileout.mat', {
     "traces":tracedata,
     "textin":textin,
     "textout":textout,
     "key":key
    })

prefix = r'2016.02.24-19.07.03'
#Can point to full directory like:
#prefix = r'C:\Temp\demo\traces_capdir48\knownrand_fixed\knownrand_fixed_P48_data\traces\2016.02.24-19.07.03'

native_to_matlab(prefix)

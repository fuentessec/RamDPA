### Testing the Toolbox
RamDPA is designed for be used and extended by the scientific comunity. To get use to it, the `main.cpp` provided in this repository executes a DPA attack with traces obtained from the CHES2016 contest.

Follow the steps below to get the traces from contest, transform them to RamDPA format and execute the Toolbox.

#### Obtaining key from CHES2016 traces:
1. Download contest traces
	- Go to https://ctf.newae.com/flags/.
	- Download traces (Trace File) from challenge called **Stagegate #1**. Filename is `Traces57.7z`.
	- Extract compressed folder generating a folder callded `traces57`.

2. Transform traces to RamDPA format.
	- move file `./traces/transformTraces.py` found in this repository to the trace data folder `traces57/traces_capdir57/knownfixed_rand/knownfixed_rand_P57_data/traces/`.
	- open a terminal
	- go to folder `traces57/traces_capdir57/knownfixed_rand/knownfixed_rand_P57_data/traces/`
	- execute `python transformTraces.py`. (*NOTE python-numpy package is required, install it for your linux distribution*).

3. This process generates .txt files with traces, input data and the real key:
	- `data.txt`: contains the plaintexts used during cryptoraphic opearation.
	- `tracesRawIntPrint.txt`: contains the traces obtained from each encryption process.
	- `key.txt`: contains the key used from encription (this is used for checking toolbox output).

#### Compile and execute the RamDPA:

4. Compile The toolbox. The Toolbox has been developed with **Netbeans 8.1 IDE** so it recomended to open and compile it with Netbeans. Compilers used are GNU (*gcc and g++*). The Toolbox has been tested in an *Ubuntu* distribution.

5. By default executable is generated under `dist` folder.

6. Executing the Toolbox. The Toolbox is a command line executable with parameters:

```	
Usage: ramdpa-master NumThreds TraceElementPrecision floatPrecision traceFile
	Numthreads = number of threads for parallel calculations
	TraceElementPrecision = 1->8-bits, 2->16-bits, 3->32-bits
	floatPrecision = 1->float(32-bits), 2->double(64bits)
	traceFile = file with traces in integer text format
	dataFile = file with input plaintexts in integer text format
```

**NOTE: traceFile is the path to "tracesRawIntPrint.txt" generated in previous steps and dataFile is the path to "data.txt" generated in previous steps.**

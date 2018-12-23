Obtaining key from CHES2016 traces:
1 - Download contest traces
	- Go to https://ctf.newae.com/flags/.
	- Download traces (Trace File) from challenge called "Stagegate #1". Filename is Traces57.7z.
	- Extract compressed folder generating a folder callded "traces57".

2 - Transform traces to RAMdpa format.
	- move file ./traces/transformTraces.py found in this repository to the trace data folder "traces57/traces_capdir57/knownfixed_rand/knownfixed_rand_P57_data/traces/"
	- open a terminal
	- go to folder "traces57/traces_capdir57/knownfixed_rand/knownfixed_rand_P57_data/traces/"
	- execute python transformTraces.py. (NOTE python-numpy package is required, install it for your linux distribution).

This process generates .txt files with traces, input data and the real key (for checkin purposes).




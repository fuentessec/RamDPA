// ======================================================================
// Copyright (C) 2018 Alberto Fuentes Rodríguez <fuentessec@gmail.com>
// This file is part of RamDPA <https://github.com/fuentessec/RamDPA>.
//
// RamDPA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RamDPA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RamDPA.  If not, see <http://www.gnu.org/licenses/>.
// ======================================================================


#include "trace_set.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <thread>
#include <condition_variable>


TraceSet::TraceSet (){
  this -> lenTrace = 0;
  this -> lenSlice = 0;

  // alignment mode at init.
  this -> StatMode = false;
}

TraceSet::TraceSet (vector <Trace*> &traces){
  this -> lenTrace = traces[0] -> size();
  this -> lenSlice = traces.size ();
  this -> samplingRate = traces[0] -> getSamplingRate();
  (this -> traces) = vector <Trace*> (traces);
  this -> lenSlice = traces.size ();

  // alignment mode at init
  this -> StatMode = false;
}


TraceSet::TraceSet (TraceSet &set, size_t begin, size_t len){ 
  uint64_t samplingRate = set.getSamplingRate ();  // sampling rate is the same as original
  size_t lenTrace = len;                              // trace length is the length that is required
  size_t lenSlice = set.getLenSlice ();            // the length of the slice is the same
  bool StatMode = set.getStatMode ();
  

  if (StatMode){  // if stat mode only get slices from begin to begin+len
    for (size_t i = begin; i < begin + len - 1; i++)
      slices.push_back (set.getNSlice (i));
  }
  else{
    Trace *aux;
    
    // in alignment mode it is needed to create the new shorter traces and push them.
    for (size_t i = 0; i < set.getLenSlice (); i++){
      switch (set.getNTraceRef (0) -> sizeElem ()){
      case 32:
	aux = new Trace32 (set.getNTraceRef (0) -> getSamplingRate (),  // electrical values keep the same.
			    set.getNTraceRef (0) -> getVoltConversion (), 
			    set.getNTraceRef (0) -> getDisplacement (), 
			    len);
	break;
      case 16:
	aux = new Trace16 (set.getNTraceRef (0) -> getSamplingRate (),  // electrical values keep the same.
			    set.getNTraceRef (0) -> getVoltConversion (), 
			    set.getNTraceRef (0) -> getDisplacement (), 
			    len);
	break;
      case 8:
	aux = new Trace8 (set.getNTraceRef (0) -> getSamplingRate (),   // electrical values keep the same.
			   set.getNTraceRef (0) -> getVoltConversion (), 
			   set.getNTraceRef (0) -> getDisplacement (), 
			   len);
	break;
      default:
	fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
      }
      
      // populate the trace with values.
      for (size_t j = begin; j < begin + len; j++){
	aux -> setValue (set.getNTraceRef (i) -> getRawValue (j), j - begin);
      }
    
      addTrace (aux);
    }
  }
}


TraceSet::~TraceSet (){
    
  if (StatMode){
    for (size_t i = 0; i < lenTrace; i++){
      delete slices [i];
    }
  }
  else{
    for (size_t i = 0; i < lenSlice; i++){
      delete traces [i];
    }
  }
   
}


float TraceSet::getValue (size_t NTrace, size_t NSlice){
  if (StatMode)
    return slices [NSlice] -> getValue (NTrace);
  else
    return traces [NTrace] -> getValue (NSlice);
}


int TraceSet::addTrace ( Trace *trace){
  if (StatMode){  // cannot addTraces in StatMode.
    fprintf (stderr, "CTraceSet::addTrace: Added trace at Statistical Mode\n");
    return -1;
  }
  
  // it is alignemnt mode. Traces can be added...

  if (traces.size () == 0){ // First trace?  
    this -> samplingRate = trace -> getSamplingRate ();
    this -> lenTrace = trace -> size ();
    this -> lenSlice = 1;
    traces.push_back (trace); // Trace is not copied. Must not be deleted by the caller.
    return 0;
  }

  // It was not the first trace...
  
  if ((trace -> size() != lenTrace) || (trace -> getSamplingRate() != samplingRate)){ // Not first trace. Must hold the properties of the first trace.
    fprintf (stderr, "CTraceSet::addTrace: trace params differs from inserted traces\n");
    return -1;
  }
  else{
    lenSlice++;
    traces.push_back (trace);
    return 0;
  }

  return -2;
}

#ifdef MULTITHREAD // if not defined -> this function is not defined
void TraceSet::statModeThread (int nThread){


  int num_threads = 1; // default value if NTHREADS environment variable is not defined
  
  if (getenv ("NTHREADS"))
    num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

  for (int i = lenTrace - nThread - 1; i >= 0; i -= num_threads){
    // create the slice that corresponds to this iteration.
    TimeSlice *aux;

    switch (traces[0] -> sizeElem ()){  // create the slice with the resolution of traces.
    case 32:
      aux = new TimeSlice32 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    case 16:
      aux = new TimeSlice16 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    case 8:
      aux = new TimeSlice8 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    default:
      fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
    }

    // assign the values of the timeslice
    for (int j = 0; j < lenSlice; j++){
      aux -> setValue (traces [j] -> getRawValue (i), j); // writing the values to the slice.
    }
    slices [i] = aux;

    // check if all thread have finish (it is the last thread), if not wait.
    unique_lock<mutex> lock (*mutexFinished); // use this mutex to increase, check  and reset finished variable.
    finished++;
    if ((finished == num_threads) || (finished == lenTraceImp)){ // it is the last
      // update value of lenTrace
      if (finished == lenTraceImp)
	lenTraceImp = 0;             // there are as many threads than values in lenTrace. lenTrace can erased
      else
	lenTraceImp -= num_threads;   // each thread erases a value of the trace.

      // reset the finished value for the next iteration
      finished = 0;

      waitThreads -> notify_all ();      
    }
    else{
      waitThreads -> wait (lock);//, [](){return (finished == num_threads) || (finished == lenTrace);});  // waiting that the last thread finish.
    }

    // resize traces to save memory.
    for (int k = nThread; k < lenSlice; k+=num_threads){
      traces [k] -> resize (lenTraceImp);
    }
  }
}
#endif

void TraceSet::statMode (){
  if (!StatMode){
    slices.resize (lenTrace); // as many slices as trace size.
    
#ifdef MULTITHREAD

    // create mutex, and conditional_variable
    mutexFinished = new mutex ();
    waitThreads = new condition_variable ();
    lenTraceImp = lenTrace;   // value of the traces length in the implementation CTraceSet::traces

    int num_threads = 1; // default value if NTHREADS environment variable is not defined
    
    if (getenv ("NTHREADS"))
      num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

    vector <thread> threads;
    
    finished = 0;
    // create threads
    for (int i = 0; i < num_threads; i++){
      threads.push_back (thread (&TraceSet::statModeThread, this,  i));
    }
    
    // join threads and clean threads vector.
    for (int i = 0; i < num_threads; i++){
      threads [i].join ();
    }
    threads.clear();

    delete mutexFinished;
    delete waitThreads;

#else
    for (int i = lenTrace - 1; i >= 0; i--){  // from last to first element of the traces...
      TimeSlice *aux;
      switch (traces[0] -> sizeElem ()){  // create the slice with the resolution of traces.
      case 32:
	aux = new TimeSlice32 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
	break;
      case 16:
	aux = new TimeSlice16 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
	break;
      case 8:
	aux = new TimeSlice8 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
	break;
      default:
	fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
      }
      

      for (int j = 0; j < lenSlice; j++){
	aux -> setValue (traces [j] -> getRawValue (i), j); // writing the values to the slice.
	traces [j] -> resize (traces [j] -> size () - 1);   // the element is in the slice yet. Erase it from trace.
      }
      slices [i] = aux;
    }

#endif
    StatMode = true;
  
  
    //free the traces stored.
    for (int i = 0; i < lenSlice; i++)
      delete traces [i];
  }
}

Trace* TraceSet::getNTrace (int pos){
  if (!StatMode){
    switch (traces[pos] -> sizeElem ()){
    case 32:
      return new Trace32 (*(static_cast<Trace32*>(traces[pos])));
      break;
    case 16:
      return new Trace16 (*(static_cast<Trace16*>(traces[pos])));
      break;
    case 8:
      return new Trace8 (*(static_cast<Trace8*>(traces[pos])));
      break;
    default:
      fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
    }
  }
  else{
    Trace* res = NULL;
    switch (slices[0] -> sizeElem ()){
    case 32:
      res = new Trace32 (samplingRate, slices[0] -> getVoltConversion (), slices[0] -> getDisplacement (), lenTrace);
      break;
    case 16:
      res = new Trace16 (samplingRate, slices[0] -> getVoltConversion (), slices[0] -> getDisplacement (), lenTrace);
      break;
    case 8:
      res = new Trace8 (samplingRate, slices[0] -> getVoltConversion (), slices[0] -> getDisplacement (), lenTrace);
      break;
    default:
      fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
    }
    
    for (int i = 0; i < lenTrace; i++)
      res -> setValue (slices [i] -> getRawValue (pos), i);
    
    return res;
  }

  return NULL;
}

TimeSlice* TraceSet::getNSlice (int pos){
  if (StatMode){
    switch (slices[pos] -> sizeElem ()){
    case 32:
      return new TimeSlice32 (*(static_cast<TimeSlice32*>(slices[pos])));
      break;
    case 16:
      return new TimeSlice16 (*(static_cast<TimeSlice16*>(slices[pos])));
      break;
    case 8:
      return new TimeSlice8 (*(static_cast<TimeSlice8*>(slices[pos])));
      break;
    default:
      fprintf (stderr, "CTraceSet::getNTrace: slices[0].sizeElem () != 8, 16, 32\n");
    }
  }
  else{
    TimeSlice* res = NULL;
    switch (traces[0] -> sizeElem ()){
    case 32:
      res = new TimeSlice32 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    case 16:
      res = new TimeSlice16 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    case 8:
      res = new TimeSlice8 (traces[0] -> getVoltConversion (), traces[0] -> getDisplacement (), lenSlice);
      break;
    default:
      fprintf (stderr, "CTraceSet::getNSlice: traces[0].sizeElem () != 8, 16, 32\n");
    }
    
    for (int i = 0; i < lenSlice; i++)
      res -> setValue (traces [i] -> getRawValue (pos), i);
    
    return res;
  }
}

Trace* TraceSet::getNTraceRef (int pos){
  if (!StatMode)
    return traces [pos];
  else{
    fprintf (stderr, "CTraceSet::getNTraceRef: cannot be used in statistical mode\n");
    return NULL;
  }
}

TimeSlice* TraceSet::getNSliceRef (int pos){
  if (StatMode)
    return slices [pos];
  else{
    fprintf (stderr, "CTraceSet::getNSliceRef: cannot be used in alignment mode\n");
    return NULL;
  }
}


StatTrace* TraceSet::meanTraces (){
  if (traces.size () == 0){
    fprintf (stderr, "CTraceSet::meanTraces: Error setEmpty");
    return NULL;
  }
  
  StatTrace *vals = new StatTrace (samplingRate, lenTrace);
  for (int i = 0; i < lenTrace; i++){
    vals -> setValue (0.0, i);
    for (int j = 0; j < lenSlice; j++){
      vals -> setValue (vals -> getValue (i) + getValue (j, i), i);
    }
    vals -> setValue (vals -> getValue (i) / (float) lenSlice, i);
  }
  
  return vals;

}
 
StatTrace* TraceSet::varianceTraces (StatTrace *mean){
  if (lenSlice == 0){
      fprintf (stderr, "CTraceSet::meanTraces: Error setEmpty");
      return NULL;
  }

  StatTrace *vals = new StatTrace (samplingRate, lenTrace);
  
  if (!mean){
    mean = meanTraces();
  }

  for (int i = 0; i < lenTrace; i++){
    vals -> setValue (0.0, i);
    for (int j = 0; j < lenSlice; j++){
      vals -> setValue (vals -> getValue (i) + ((getValue (j,i) - mean -> getValue (i)) * 
						(getValue (j,i) - mean -> getValue (i))), i);
    }
    vals -> setValue (vals -> getValue (i) / (float) (lenSlice - 1), i);
  }
  return vals;
}


int TraceSet::toPng (char *fileName, list<string> *gnuplotCmds){
  FILE *gnuplotPipe = popen("gnuplot -persist","w");
  map <pair<int,float>,int> elemRepts;                           // structure containing the n� of repetitions of each element ((x,y) -> z).
  
  if (gnuplotPipe <= 0) 
    {  
      return -1;
    }
  
  // loop for counting the ocurrencies of each element in the TraceSet. Depending on the mode, iteration trough traces or slices
  if (!StatMode){
    for (int i = 0; i < lenSlice; i++){                                                // iterating trough traces (cache friendly).
      for (int j = 0; j < lenTrace; j++){                                              // iterating trough trace elements.
	if (elemRepts.find (make_pair(j, getValue (i,j))) == elemRepts.end()){         // it is the first time that the element is found -> element count = 1.
	  elemRepts [make_pair(j, getValue (i,j))] = 1;
	}
	else{
	  (elemRepts.find(make_pair(j, getValue (i,j)))->second)++;                    // it exist in the map, so the count is increased.
	}
      }
    }
  }
  else{
    for (int j = 0; j < lenTrace; j++){                                                // iterating trough slices (cache friendly).
      for (int i = 0; i < lenSlice; i++){                                              // iterating trough slices elements.
	if (elemRepts.find (make_pair(j, getValue (i,j))) == elemRepts.end()){         // it is the first time that the element is found -> element count = 1.
	  elemRepts [make_pair(j, getValue (i,j))] = 1;
	}
	else{
	  (elemRepts.find(make_pair(j, getValue (i,j)))->second)++;                    // it exist in the map, so the count is increased.
	}
      }
    }
  }
      
  // find the correct x-axis scale (ns, us, ms, sec)
  char* unit = NULL;
  unsigned int magnitude = log10 ((double) lenSlice * samplingRate) / 3;       // axis values shall be less than 1000. 
                                                                               // [0..999] -> 0, [1000, 999999] -> 1, 
                                                                               // [1000000, 999999999] -> 2 ...
  uint64_t divisor = 1;

  switch (magnitude){
  case 0:
    unit = strdup ("ps");
    divisor = 1;
    break;
  case 1:
    unit = strdup ("ns");
    divisor = 1000;
    break;
  case 2:
    unit = strdup ("us");
    divisor = 1000000;
    break;
  case 3:
    unit = strdup ("ms");
    divisor = 1000000000;
    break;    
  default:
    unit = strdup ("sec");
    divisor = 1000000000000ULL;
    break;
  }

  // send commands to gnuplot
  fprintf(gnuplotPipe, "set terminal png\n");                                             // output as png
  fprintf(gnuplotPipe, "set output \"%s\"\n ",fileName);                                  // output name
  fprintf(gnuplotPipe, "set xlabel \"time [%s]\"\n", unit);                               // set x label
  fprintf(gnuplotPipe, "set ylabel \"voltage [mv]\"\n");                                  // set y label
  fprintf(gnuplotPipe, "set pm3d map\n");
  fprintf(gnuplotPipe, "set isosample 400\n");
  fprintf(gnuplotPipe, "set palette defined (-1 \"white\", 0 \"blue\", 1 \"red\")\n");
  fprintf(gnuplotPipe, "set cbrange [0:]\n");
  fprintf(gnuplotPipe, "splot '-' using ($1 / %ld.):2:3 notitle with dots palette\n", divisor);   // set scale and representation mode
  // set samples

  //send added commands to gnuplot
  if (gnuplotCmds)
    for (list<string>::iterator it = gnuplotCmds->begin() ; it != gnuplotCmds->end(); it++)
      fprintf(gnuplotPipe, "%s\n", it->data());     // print nth command.

  // send data to gnuplot

  map <pair<int,float>,int>::iterator it;
  for (it = elemRepts.begin (); it != elemRepts.end(); it++){
    fprintf(gnuplotPipe, "%d %f %d\n", (it->first).first, (it->first).second, it->second);
  }


  // metadata for "end of data"
  fprintf(gnuplotPipe, "e");

  // close gnuplot interface
  fprintf(gnuplotPipe, "\n");
  fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);

  // free memory and structures.
  free (unit);
  fclose (gnuplotPipe);
}

int TraceSet::toDisk (FILE *fd){
    // class serialized as: samplingRate || lenTrace || lenSlice || StatMode || data resolution || if !StatMode -> Data Trace 0... || Data Trace 1...
    //                                                                                          || else         -> Data Slice 0... || Data Slice 1...

  if (fwrite (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&lenTrace, sizeof (lenTrace), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&lenSlice, sizeof (lenSlice), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&StatMode, sizeof (StatMode), 1, fd) != 1){
    return -1;
  }

  if (!StatMode){
    size_t resolution = traces [0] -> sizeElem ();
    if (fwrite (&resolution, sizeof (resolution), 1, fd) != 1){
      return -1;
    }

    for (int i = 0; i < lenSlice; i++)
      traces [i] -> toDisk (fd);
  }
  else{
    size_t resolution = slices [0] -> sizeElem ();
    if (fwrite (&resolution, sizeof (resolution), 1, fd) != 1){
      return -1;
    }

    for (int i = 0; i < lenTrace; i++)
      slices [i] -> toDisk (fd);
  }

  return 0;
}

int TraceSet::fromDisk (FILE *fd){

}



PreProcTraceSet::PreProcTraceSet (vector <Trace*> &traces) : TraceSet (traces){

}

PreProcTraceSet::PreProcTraceSet () : TraceSet (){

}


AlignSumTraceSet::AlignSumTraceSet (int windowSize) : PreProcTraceSet (){
  this -> windowSize = windowSize;
}

AlignSumTraceSet::AlignSumTraceSet (vector <Trace*> &traces, 
				      int windowSize) : PreProcTraceSet (traces){

  this -> windowSize = windowSize;
}

uint32_t AlignSumTraceSet::sumWindow (Trace *trace, int pos){
  float result = 0.0;

  if (pos < windowSize - 1){ // window is higher that the n� of previous values in trace.
    for (int i = 0; i <= pos; i++){
      result += trace -> getRawValue (i);
    }
  }
  else{
    for (int i = 0; i < windowSize; i++){
      result += trace -> getRawValue (pos - i);
    }
  }
  
  return result;
}

void AlignSumTraceSet::alignThread (int nThread){
  int num_threads = 1; // default value if NTHREADS environment variable is not defined
  
  if (getenv ("NTHREADS"))
    num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

  for (int nthTrace = nThread; nthTrace < lenSlice; nthTrace += num_threads){
    for (int i = lenTrace - 1; i >= 0; i--){      
      traces [nthTrace] -> setValue (sumWindow (traces [nthTrace], i), i);
    }
  }
}

int AlignSumTraceSet::preProcess (){
  if (StatMode){
    fprintf (stderr, "AlignSumTraceSet::preProcess: TraceSet in Statistical mode\n");
    return -1;
  }

  #ifdef MULTITHREAD
  int num_threads = 1; // default value if NTHREADS environment variable is not defined
  
  if (getenv ("NTHREADS"))
    num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

  vector <thread> threads;

  // create threads
  for (int i = 0; i < num_threads; i++){
    threads.push_back (thread (&AlignSumTraceSet::alignThread, this, i));
  }

  // join threads and clean threads vector.
  for (int i = 0; i < num_threads; i++){
    threads [i].join ();
  }
  threads.clear();

  #else
  for (int nthTrace = 0; nthTrace < lenSlice; nthTrace++){
    for (int i = lenTrace - 1; i >= 0; i--){      
      traces [nthTrace] -> setValue (sumWindow (traces [nthTrace], i), i);
    }
  }
  #endif

  return 0;
}



AlignMatchSqrTraceSet::AlignMatchSqrTraceSet (int iniPatern,
						int lenPatern,
						int maxDisp) : PreProcTraceSet (){
  
  this -> iniPatern = iniPatern;
  this -> lenPatern = lenPatern; // The object stores the number of elements after iniPatern.
  this -> maxDisp = maxDisp;
}

AlignMatchSqrTraceSet::AlignMatchSqrTraceSet (vector <Trace*> &traces,
						int iniPatern,
						int lenPatern,
						int maxDisp) : PreProcTraceSet (traces){
  
  this -> iniPatern = iniPatern;
  this -> lenPatern = lenPatern; // The object stores the number of elements after iniPatern.
  this -> maxDisp = maxDisp;
}


int AlignMatchSqrTraceSet::leastSquareDisp (Trace *trace){
  uint64_t leastSquare = 0xFFFFFFFFFFFFFFFF;  // value of the least square found (init value = MAX)
  int resultDisp;                             // displacement of the LeastSquare.

  // select the i-th displacement: i bellongs to [-maxDisp, maxDisp]
  for (int i = -maxDisp; i <= maxDisp; i++){ 
    uint64_t auxLS = 0;

    // calculate the leastSquare for this displacement
    for (int j = 0; j < lenPatern; j++){  
      auxLS += (traces [0] -> getRawValue (iniPatern + j) - trace -> getRawValue (iniPatern + i + j))*
	       (traces [0] -> getRawValue (iniPatern + j) - trace -> getRawValue (iniPatern + i + j));
    }
    
    // update  min-value and position if necesary.
    if (auxLS < leastSquare){
      leastSquare = auxLS;
      resultDisp = i;
    }
  }
  return -resultDisp; // positive -> shift left, negative -> shift rigth
}  

void AlignMatchSqrTraceSet::alignThread (int nThread){
  int num_threads = 1; // default value if NTHREADS environment variable is not defined
  
  if (getenv ("NTHREADS"))
    num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

  // align all traces with the first trace
  for (int i = nThread + 1; i < lenSlice; i+= num_threads){ 
    // get best displacement
    int disp = leastSquareDisp (traces [i]);

    // no displacement needed.
    if (disp == 0)
      continue;

    // displace
    if (disp > 0){  // shift right (>>)
      for (int j = lenTrace - 1; j >= 0; j--){
	if ((j - disp >= 0) && (j - disp < lenTrace)){
	  // move values
	  traces [i] -> setValue (traces [i] -> getRawValue (j-disp), j);
	}
	else{
	  // set to 0 undefined values
	  traces [i] -> setValue (0, j);
	}
      }
    }    
    else{
      for (int j = 0; j < lenTrace; j++){ // shift right (<<)
	if ((j - disp >= 0) && (j - disp < lenTrace)){
	  // move values
	  traces [i] -> setValue (traces [i] -> getRawValue (j-disp), j);
	}
	else{
	  // set to 0 undefined values
	  traces [i] -> setValue (0, j);
	}
      }
    }
  }
  
}

int AlignMatchSqrTraceSet::preProcess (){  

  if (StatMode){
    fprintf (stderr, "CAlignMatchSqrTraceSet::preProcess: TraceSet in Statistical mode\n");
    return -1;
  }

#ifdef MULTITHREAD
  int num_threads = 1; // default value if NTHREADS environment variable is not defined
  
  if (getenv ("NTHREADS"))
    num_threads = atoi (getenv ("NTHREADS")); // number of threads as specified by NTHREADS.

  vector <thread> threads;

  // create threads
  for (int i = 0; i < num_threads; i++){
    threads.push_back (thread (&AlignMatchSqrTraceSet::alignThread, this, i));
  }

  // join threads and clean threads vector.
  for (int i = 0; i < num_threads; i++){
    threads [i].join ();
  }
  threads.clear();

#else
  // align all traces with the first trace
  for (int i = 1; i < lenSlice; i++){ 
    // get best displacement
    int disp = leastSquareDisp (traces [i]);

    // no displacement needed.
    if (disp == 0)
      continue;

    // displace
    if (disp > 0){  // shift right (>>)
      for (int j = lenTrace - 1; j >= 0; j--){
	if ((j - disp >= 0) && (j - disp < lenTrace)){
	  // move values
	  traces [i] -> setValue (traces [i] -> getRawValue (j-disp), j);
	}
	else{
	  // set to 0 undefined values
	  traces [i] -> setValue (0, j);
	}
      }
    }    
    else{
      for (int j = 0; j < lenTrace; j++){ // shift right (<<)
	if ((j - disp >= 0) && (j - disp < lenTrace)){
	  // move values
	  traces [i] -> setValue (traces [i] -> getRawValue (j-disp), j);
	}
	else{
	  // set to 0 undefined values
	  traces [i] -> setValue (0, j);
	}
      }
    }
  }
#endif

  return 0;
}



/*
//////////////////////////
//// CPreProcTraceSet ////
//////////////////////////

template <class T> CPreProcTraceSet<T>::CPreProcTraceSet (CTraceSet<T> &set) : CTraceSet<T> (set){

}


//////////////////////////
//// CAlignSumTraceSet////
//////////////////////////
template <class T> CAlignSumTraceSet<T>::CAlignSumTraceSet (CTraceSet<T> &set,
							    int windowSize) : CPreProcTraceSet<T> (set){

  this -> windowSize = windowSize;
}

template <class T> T CAlignSumTraceSet<T>::sumWindow (const CTrace<T> &trace, int pos){
  T result = 0;

  if (pos < windowSize - 1){ // window is higher that the n� of previous values in trace.
    for (int i = 0; i <= pos; i++){
      result += trace [i];
    }
  }
  else{
    for (int i = 0; i < windowSize; i++){
      result += trace [pos - i];
    }
  }
  
  return result;
}


template <class T> int CAlignSumTraceSet<T>::preProcess (){
  
  for (int nthTrace = 0; nthTrace < CTraceSet<T>::traces.size(); nthTrace++){
    for (int i = CTraceSet<T>::lenTrace - 1; i >= 0; i--){
      CTraceSet<T>::traces [nthTrace][i] = sumWindow (CTraceSet<T>::traces [nthTrace], i);
    }
  }

  return 0;
}

//////////////////////////////
////CAlignMatchSqrTraceSet////
//////////////////////////////

template <class T> CAlignMatchSqrTraceSet<T>::CAlignMatchSqrTraceSet (CTraceSet<T> &set,
								      int iniPatern,
								      int lenPatern,
								      int maxDisp) : CPreProcTraceSet<T> (set){

  this -> iniPatern = iniPatern;
  this -> lenPatern = lenPatern; // The object stores the number of elements after iniPatern.
  this -> maxDisp = maxDisp;
}

template <class T> int CAlignMatchSqrTraceSet<T>::leastSquareDisp (const CTrace<T> &trace){
  uint32_t leastSquare = 0xFFFFFFFF;  // value of the least square found (init value = MAX)
  int resultDisp;                     // displacement of the LeastSquare.

  // select the i-th displacement: i bellongs to [-maxDisp, maxDisp]
  for (int i = -maxDisp; i <= maxDisp; i++){ 
    uint32_t auxLS = 0;

    // calculate the leastSquare for this displacement
    for (int j = 0; j < lenPatern; j++){  
      auxLS += (CTraceSet<T>::traces [0][iniPatern + j] - trace [iniPatern + i + j])*
	       (CTraceSet<T>::traces [0][iniPatern + j] - trace [iniPatern + i + j]);
    }
    
    // update  min-value and position if necesary.
    if (auxLS < leastSquare){
      leastSquare = auxLS;
      resultDisp = i;
    }
  }
  
  return -resultDisp; // positive -> shift left, negative -> shift rigth
}  

template <class T> int CAlignMatchSqrTraceSet<T>::preProcess (){  

  // align all traces with the first trace
  for (int i = 1; i < CTraceSet<T>::traces.size(); i++){ 
    // get best displacement
    int disp = leastSquareDisp (CTraceSet<T>::traces [i]);
    printf ("disp: %d\n", disp);
    // displace
    for (int j = 0; j < CTraceSet<T>::lenTrace; j++){
      if ((j - disp >= 0) && (j - disp < CTraceSet<T>::lenTrace)){
	// move values
	CTraceSet<T>::traces [i][j]= CTraceSet<T>::traces [i][j-disp]; 
      }
      else{
	// set to 0 undefined values
	CTraceSet<T>::traces [i][j]= 0;
      }
    }
  }

  return 0;
}


template class CTraceSet<uint8_t>;
template class CTraceSet<uint16_t>;
template class CTraceSet<uint32_t>;

template class CPreProcTraceSet<uint8_t>;
template class CPreProcTraceSet<uint16_t>;
template class CPreProcTraceSet<uint32_t>;

template class CAlignSumTraceSet<uint8_t>;
template class CAlignSumTraceSet<uint16_t>;
template class CAlignSumTraceSet<uint32_t>;

template class CAlignMatchSqrTraceSet<uint8_t>;
template class CAlignMatchSqrTraceSet<uint16_t>;
template class CAlignMatchSqrTraceSet<uint32_t>;
*/

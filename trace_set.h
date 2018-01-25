/**
 * @file   traceset.h
 * @author fuentes <fuentes@fuentes-desktop>
 * @date   Mon Dec  3 18:30:28 2012
 * 
 * @brief  Contains the representation of sets of traces.
 *
 * This file contains sets of traces of the same device taken with the same timming, in order to do
 * statistical analysis. It is also containded traces sets for process the traces before the statistical analysis.
 * Trace Sets can be in two states Statistical Mode and Alignemnt Mode. Method availability or performance may
 * depend on the mode.
 * 
 * 
 */
#ifndef CTRACESET_H
#define CTRACESET_H

#include <vector>

#ifndef CTRACE
#include "trace.h"
#endif 

#ifndef CTIMESLICE
#include "time_slice.h"
#endif 

#ifndef CINTERFACES
#include "cinterfaces.h"
#endif 

#include <mutex>
#include <condition_variable>

#define MULTITHREAD

using namespace std;

/**
 * @brief It contains a set of traces and its asociated operations.
 * 
 *
 * This class contains sets of traces of the same device taken with the same timming, in order to do
 * statistical analysis.
 * Trace Sets can be in two states Statistical Mode and Alignemnt Mode. Method availability or performance may
 * depend on the mode.
 * 
 */

class TraceSet : virtual public FileStorage, virtual public Graphicable{
private:
#ifdef MULTITHREAD
  size_t lenTraceImp;
  void statModeThread (int nThread);
  mutex *mutexFinished;
  condition_variable *waitThreads;
#endif
  int finished;
protected:
  vector <Trace*> traces;     ///< set of ordered traces. (used in Alignment Mode, for cache performance).
  vector <TimeSlice*> slices; ///< set of ordered time slices. (used in Statistical Mode, for cache performance).
  uint64_t samplingRate;       ///< picoSeconds between trace values.
  size_t lenTrace; ///< lengths of data specified in traces in any mode.
  size_t lenSlice; ///< lengths of data specified in traces in any mode.
  bool StatMode;  ///< true = statistical mode, false = alignment mode

  /** 
   * takes the value in mV in the specified position in any mode.
   * 
   * @param NTrace Trace from which obtain the value (val = value [NTrace, NSlice]).
   * @param NSlice TimeSlice from which obtain the value (val = value [NTrace, NSlice]).
   * 
   * @return Returns the value in mV.
   */
  float getValue (size_t NTrace, size_t NSlice); 
public:
  /** 
   * Creates an empty set of traces. 
   * A clean object to be filled from a method (i.e. addTrace, FromDisk).
   * 
   * 
   * @return 
   */
  TraceSet ();

  /** 
   * Object is initialiced with the values contained in traces.
   * traces contained as input value must have the same length, sampling rate and 
   * conversion variables.
   * Traces are stored as references. CTraceSet destructor will free the memory.
   * 
   * @param traces traces to be inserted.
   * 
   * @return 
   */
  TraceSet (vector <Trace*> &traces);

  /** 
   * Creates a TraceSet from part of other TraceSet.
   * TraceSet created with len TimeSlices contained in set from the begin position.
   * 
   * 
   * @param set Original TraceSet from which the TraceSet will be created
   * @param begin Initial Timeslice position.
   * @param len Number of Timeslices taken form begin.
   * 
   * @return 
   */
  TraceSet (TraceSet &set, size_t begin, size_t len);

  /** 
   * Returns the number of elements in each trace.
   * 
   * 
   * @return Number of elements per trace.
   */

  ~TraceSet ();

  /** 
   * Returns the sampling rate of the stored traces.
   * 
   * 
   * @return sampling rate.
   */
  uint64_t getSamplingRate (){return samplingRate;};

  /** 
   * Returns the number of elements in each trace.
   * 
   * 
   * @return Number of elements per trace.
   */

  bool getStatMode (){return StatMode;};

  int getLenTrace (){return lenTrace;};

  /** 
   * Returns the number of elements in each time slice.
   * 
   * 
   * @return Number of elements per time slice.
   */
  int getLenSlice (){return lenSlice;};

  /** 
   * Inserts a trace at the end of the trace set. Traces are stored
   * as references. CTraceSet destructor will free the memory.
   * This method can only be used in alignment mode.
   * @param[in] trace pointer to the trace to be added.
   * 
   * @return 0 if success, -1 e.o.c.
   */
  int addTrace (Trace *trace);  // only in alignment mode.

  /** 
   * Changes the internal representation for statistical mode. Improving the performance in
   * operations that require usage of time slices.
   * 
   */
  void statMode ();

  /** 
   * Returns a copy of the trace stored in the position specified. The caller shall free
   * the returned value when required. (faster in alignment mode).
   * 
   * @param pos position of the trace to be copied.
   * 
   * @return Returns a pointer to the copy of the trace in the specified position.
   */
  Trace* getNTrace (int pos);

  /** 
   * Returns a copy of the time slice stored in the position specified. The caller shall free
   * the returned value when required. (faster in statistical mode).
   * 
   * @param pos position of the time slice to be copied.
   * 
   * @return Returns a pointer to the copy of the time slice in the specified position.
   */
  TimeSlice* getNSlice (int pos);

  /** 
   * Returns a pointer to the trace stored in the position specified. The caller must not free
   * the returned value. (faster in alignment mode).
   * 
   * @param pos position of the trace to be retuned.
   * 
   * @return Returns a pointer to the trace in the specified position.
   */
  Trace* getNTraceRef (int pos);     // only in alignment mode.

  /** 
   * Returns a pointer to the time slice stored in the position specified. The caller must not free
   * the returned value. (faster in alignment mode).
   * 
   * @param pos position of the time slice to be returned.
   * 
   * @return Returns a pointer to the time slice in the specified position.
   */
  TimeSlice* getNSliceRef (int pos); // only in statistical mode.

  /** 
   * Returns a vector (StatTrace) with the arithmetical mean of all the traces stored.
   * Caller shall free the returned value when required. (faster in statistical mode).
   * 
   * @return mean of the contained traces.
   */
  virtual StatTrace* meanTraces ();

  /** 
   * Returns a vector (StatTrace) with the statistical variance of all the traces stored.
   * Caller shall fre the returned value when required. (faster in statistical mode).
   * 
   * @param mean optionally the caller may provide the mean to the method in order to get faster results.
   * 
   * @return variance of the contained traces.
   */
  virtual StatTrace* varianceTraces (StatTrace* mean = NULL);

  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
};


/**
 * @brief CTraceSet subclass with the added property that the traces can be preprocessed: aligned, compressed...
 * 
 */
class PreProcTraceSet : public TraceSet {

public:
  PreProcTraceSet ();  
  PreProcTraceSet (vector <Trace*> &traces);
  
  virtual int preProcess () = 0;
};

/** 
 * @brief CTraceSet subclass with the property of align the traces through integration.
 * 
 * Integration sums up the power consumption of the previows n positions of each trace.
 * Take into account that the selected trace resolution must be enough to store the sume of n positions.
 */
class AlignSumTraceSet : virtual public PreProcTraceSet{
protected:
  int windowSize;  ///< number of positions to be sumed up.

  /** 
   * Used to return the value of the sum of the previous values.
   * 
   * @param trace reference to the trace.
   * @param pos position that will be the result of the sum of its previous values.
   * 
   * @return the sum of the previos values (windowsSize).
   */
  uint32_t sumWindow (Trace *trace, int pos);
  void alignThread (int nThread);
public:

  AlignSumTraceSet (int windowSize);  
  AlignSumTraceSet (vector <Trace*> &traces, int windowSize);

  virtual int preProcess ();
};


/** 
 * @brief CTraceSet subclass with the property of align the traces through least square matching pattern technique.
 * 
 * The displacement between the pattern (first trace of the set) and the power trace is calculated. 
 */
class AlignMatchSqrTraceSet : virtual public PreProcTraceSet{
protected:
  int iniPatern; ///< Initial position of the pattern (first trace of the set).
  int lenPatern; ///< length of the pattern. 
  int maxDisp;   ///< maximun displacement of the traces in each direction.

  /** 
   * Obtains the displacement of the trace provided to match with the first trace.
   * 
   * @param trace 
   * 
   * @return if > 0 right displacement, if < 0 left displacement, if 0 no displacement.
   */
  int leastSquareDisp (Trace *trace);
  void alignThread (int nThread);
public:
  
  
  AlignMatchSqrTraceSet (int iniPatern, int lenPatern, int maxDisp);
  AlignMatchSqrTraceSet (vector <Trace*> &traces, int iniPatern, int lenPatern, int maxDisp);
  virtual int preProcess ();
};

#endif /* TRACESET_H */
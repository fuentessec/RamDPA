/**
 * @file   trace.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @date   Thu Nov 29 19:49:03 2012
 * 
 * @brief  This file contains the classes that define a trace. 
 *
 * Trace elements are stored as obtained from the oscilloscope
 * due to optimization (adjust size to the oscilloscope resolution).
 * 
 * 
 */
#ifndef CTRACE_H
#define CTRACE_H


#include <vector>
#include <stdint.h>
#include <string>
#include <list>
#include <stdio.h>

#ifndef CINTERFACES
#include "interfaces.h"
#endif 

#define CTRACE

using namespace std;

/**
 * @brief This class is used as an abstraction to caller objects of the resolution of the trace.
 * 
 */

class Trace : virtual public FileStorage, virtual public Graphicable{
protected:
  uint64_t samplingRate; ///< picoSeconds between values.
  double voltConversion; ///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
  double displacement; ///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
public:
  /** 
   * Constructor that initialices the variables for conversion from raw oscilloscope values to "mV"
   * 
   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * 
   * @return
   */
  Trace (uint64_t samplingRate, double voltConversion, double displacement); 

  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  Trace ();
 
  // get methods for class parameters
  /** 
   * Returns the voltConversion attribute.
   * 
   * 
   * @return voltConversion value.
   */
  double getVoltConversion (){return voltConversion;};
  /** 
   * Returns the displacement attribute.
   * 
   * 
   * @return displacement value.
   */
  double getDisplacement (){return displacement;};
  /** 
   * Returns the samplingRate attribute.
   * 
   * 
   * @return sampling rate.
   */
  uint64_t getSamplingRate (){return samplingRate;};


  /** 
   * Returns the value in "mV" of the specified trace position.
   * 
   * @param pos trace position.
   * 
   * @return the trace position value measured in "mV".
   */
  virtual float getValue (size_t pos) = 0;                  
  /** 
   * Returns the value as obtained from the oscilloscope.
   * 
   * @param pos trace position.
   * 
   * @return the trace position value in raw.
   */
  virtual uint32_t getRawValue (size_t pos) = 0;            // returns the oscilloscope value.
  /** 
   * Set the specified trace position with the given value.
   * 
   * @param value raw value as obtained from the oscilloscope
   * @param pos trace position to be set.
   * 
   * @return 
   */
  virtual int setValue (uint32_t value, size_t pos) = 0;    // set oscilloscope value.
  /** 
   * Obtains the size of the trace (number of values).
   * 
   * 
   * @return number of values stored.
   */
  virtual size_t size () = 0;                               // returns its size.
  /** 
   * Resizes the trace erasing the last elements trace (required by TraceSet).
   * 
   * @param size new size of the trace.
   */
  virtual void resize (size_t size) = 0;                    // erases last element (req. by TraceSet::statMode)
  /** 
   * Obtains the resolution of the raw values in Bytes.
   * 
   * 
   * @return 1 -> 8bits, 2 -> 16bits, 4 -> 32bits.
   */
  virtual size_t sizeElem () = 0;  // used to know the value resolution (subClass used).
};


/**
 * @brief Implementation of Trace with 32 bits of resolution.
 * 
 */
class Trace32 : public Trace{
protected:
  vector <uint32_t> values;	///< Ordered storage of raw values
public:
  /** 
   * Creates a trace with the specified values, sampling rate and the conversion parameters specified.
   *
   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */
  Trace32 (uint64_t samplingRate, 
	    double voltConversion, 
	    double displacement, 
	    uint32_t* values, 
	    size_t size);

  /** 
   * Creates a trace with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  Trace32 (uint64_t samplingRate, double voltConversion, double displacement, size_t size);
  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  Trace32 ();
  
  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  int setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};
  void resize (size_t size){values.resize(size);};

  size_t sizeElem (){return 32;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

/**
 * @brief  Implementation of Trace with 16 bits of resolution.
 * 
 */
class Trace16 : public Trace{
protected:
  vector <uint16_t> values; ///< Ordered storage of raw values
public:
    /** 
   * Creates a trace with the specified values, sampling rate and the conversion parameters specified.

   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */
  Trace16 (uint64_t samplingRate, double voltConversion, double displacement, uint16_t* values, size_t size);
  /** 
   * Creates a trace with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  Trace16 (uint64_t samplingRate, double voltConversion, double displacement, size_t size);
  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  Trace16 ();


  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  int setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};
  void resize (size_t size){values.resize (size);};

  size_t sizeElem (){return 16;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

/**
 * @brief Implementation of Trace with 8 bits of resolution.
 * 
 */
class Trace8 : public Trace{
protected:

  vector <uint8_t> values; ///< Ordered storage of raw values
public:
  /** 
   * Creates a trace with the specified values, sampling rate and the conversion parameters specified.

   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */
  Trace8 (uint64_t samplingRate, double voltConversion, double displacement, uint8_t* values, size_t size);
  /** 
   * Creates a trace with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param samplingRate picoSeconds between values.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  Trace8 (uint64_t samplingRate, double voltConversion, double displacement, size_t size);
  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  Trace8 ();
  

  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  int setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};
  void resize (size_t size){values.resize(size);};

  size_t sizeElem (){return 8;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

/**
 * @brief This class represents statistical data obtained from several traces (i.e. mean, variance).
 * 
 */
class StatTrace : virtual public FileStorage, virtual public Graphicable{
protected:
  uint64_t samplingRate; ///< picoSeconds between values.
  vector <float> values; ///< Ordered storage of values.
public:
  /** 
   * Constructor that allocates memory for storage of size elemnts
   * 
   * @param samplingRate sampling rate.
   * @param size size of elements
   */
  StatTrace (uint64_t samplingRate, size_t size);
  
  /** 
   * Returns the samplingRate attribute.
   * 
   * 
   * @return sampling rate.
   */
  uint64_t getSamplingRate (){return samplingRate;};

  /** 
   * Returns the statistical value in "mV" of the specified position.
   * 
   * @param pos statistical trace position.
   * 
   * @return the statistical value measured in "mV".
   */
  float getValue (size_t pos){return values [pos];};                   // returns the float value in mV.

  /** 
   * Set the specified trace position with the given value.
   * 
   * @param value statistical value.
   * @param pos statistical trace position to be set.
   * 
   * @return 
   */
  void setValue (float value, size_t pos){values [pos] = value;};       // set oscilloscope value.
  /** 
   * Obtains the size of the statistical trace (number of values).
   * 
   * 
   * @return number of values stored.
   */
  size_t size (){return values.size ();};                              // returns its size.
  
  int toDisk (FILE *fd);   // initializes the object stored in the file descriptor.
  int fromDisk (FILE *fd); // stores the object in the file descriptor.
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);  // graphical representation in file.
};
#endif /* TRACE_H */
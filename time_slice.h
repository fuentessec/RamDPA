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


/**
 * @file   timeslice.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @date   Thu Nov 29 19:49:03 2012
 * 
 * @brief  This file contains the classes that define a time slice. 
 *
 *A time slice contains the values taken at a time point
 * from several traces. Time slice elements are stored as obtained from the oscilloscope due to optimization 
 *(adjust size to the oscilloscope resolution).
 */

#include <vector>
#include <list>
#include <string>
#include <stdint.h>

#ifndef CINTERFACES
#include "interfaces.h"
#endif 


#define CTIMESLICE

using namespace std;
/**
 * @brief A time slice contains the values taken at a time point from several traces.
 * 
 *
 * This class is used as an abstraction to caller objects of the resolution of the time slice.
 * 
 */
class TimeSlice : virtual public FileStorage, virtual public Graphicable{
protected:
  double voltConversion;	///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
  double displacement;          ///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
public:
  /** 
   * Constructor that initialices the variables for conversion from raw oscilloscope values to "mV"
   * 
   * @param voltConversion ///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement   ///< Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * 
   * @return 
   */
  TimeSlice (double voltConversion, double displacement);

  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  TimeSlice ();

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
   * Returns the value in "mV" of the specified time slice position.
   * 
   * @param pos trace position.
   * 
   * @return the trace position value measured in "mV".
   */
  virtual float getValue (size_t pos) = 0;

  /** 
   * Returns the value as obtained from the oscilloscope.
   * 
   * @param pos time slice position.
   * 
   * @return the time slice position value in raw.
   */
  virtual uint32_t getRawValue (size_t pos) = 0;

    /** 
   * Set the specified trace position with the given value.
   * 
   * @param value raw value as obtained from the oscilloscope
   * @param pos time slice position to be set.
   * 
   * @return 
   */
  virtual void setValue (uint32_t value, size_t pos) = 0;

  /** 
   * Obtains the size of the trace (number of values).
   * 
   * 
   * @return number of values stored.
   */
  virtual size_t size () = 0;

  /** 
   * Obtains the resolution of the raw values in Bytes.
   * 
   * 
   * @return 1 -> 8bits, 2 -> 16bits, 4 -> 32bits.
   */
  virtual size_t sizeElem () = 0;
};

/**
 * @brief Implementation of TimeSlice with 32 bits of resolution.
 * 
 */
class TimeSlice32 : public TimeSlice{
protected:
  vector <uint32_t> values; ///< Ordered storage of raw values
public:
    /** 
   * Creates a time slice with the specified values, sampling rate and the conversion parameters specified.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */
  TimeSlice32 (double voltConversion, double displacement, uint32_t* values, size_t size);

  /** 
   * Creates a time slice with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  TimeSlice32 (double voltConversion, double displacement, size_t size);
  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  TimeSlice32 ();
  
  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  void setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};

  size_t sizeElem (){return 32;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

/**
 * @brief Implementation of TimeSlice with 16 bits of resolution.
 * 
 */
class TimeSlice16 : public TimeSlice{
protected:
  vector <uint16_t> values; ///< Ordered storage of raw values
public:
    /** 
   * Creates a time slice with the specified values, sampling rate and the conversion parameters specified.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */  
  TimeSlice16 (double voltConversion, double displacement, uint16_t* values, size_t size);
  /** 
   * Creates a time slice with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  TimeSlice16 (double voltConversion, double displacement, size_t size);
  TimeSlice16 ();

  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  void setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};

  size_t sizeElem (){return 16;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

/**
 * @brief Implementation of TimeSlice with 8 bits of resolution.
 * 
 */
class TimeSlice8 : public TimeSlice{
protected:
  vector <uint8_t> values;///< Ordered storage of raw values
public:
  /** 
   * Creates a time slice with the specified values, sampling rate and the conversion parameters specified.
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).    
   * @param[in] values  list of values. The values are copied. Caller can free them.
   * @param size size of the list of values.
   * 
   * @return 
   */
  TimeSlice8 (double voltConversion, double displacement, uint8_t* values, size_t size);
  /** 
   * Creates a time slice with the sampling rate and the conversion parameters specified. Memory for allocate
   * values is reserved.
   * 
   * @param voltConversion Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).
   * @param displacement Conversion variables: Oscilloscope -> mV, (rawValue*voltConversion + displacement).   
   * @param size size of elements.
   * 
   * @return 
   */
  TimeSlice8 (double voltConversion, double displacement, size_t size);
  /** 
   * It creates a clean object to be filled from a method (i.e. "fromFile").
   * 
   * 
   * @return 
   */
  TimeSlice8 ();

  float getValue (size_t pos){return float(values[pos]) * voltConversion + displacement;};
  uint32_t getRawValue (size_t pos) {return uint32_t (values[pos]);};
  void setValue (uint32_t value, size_t pos){values[pos] = value;};
  size_t size (){return values.size();};

  size_t sizeElem (){return 8;};

  int toDisk (FILE *fd);
  int fromDisk (FILE *fd);
  int toPng (char *fileName, list<string> *gnuplotCmds = NULL);
};

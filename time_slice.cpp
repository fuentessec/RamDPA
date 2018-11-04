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


#include "time_slice.h"
#include <map>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

TimeSlice::TimeSlice (double voltConversion, double displacement){
  this -> voltConversion = voltConversion;
  this -> displacement = displacement;
}

TimeSlice::TimeSlice (){
  
}


TimeSlice32::TimeSlice32 (double voltConversion, 
		    double displacement, 
		    uint32_t* values, 
		    size_t size) : TimeSlice (voltConversion, displacement){

  this -> values.resize (size);

  for (size_t i = 0; i < size; i++){
    this -> values [i] = values [i];
  }
}

TimeSlice32::TimeSlice32 (double voltConversion, 
			    double displacement, 
			    size_t size) : TimeSlice (voltConversion, displacement){

  values.resize (size);
}

TimeSlice32::TimeSlice32 () : TimeSlice (){}

int TimeSlice32::toDisk (FILE *fd){
  // class serialized as: voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&displacement, sizeof (displacement), 1, fd) != 1){
    return -1;
  }

  uint8_t bytesData = (uint8_t) sizeof (uint32_t);
  if (fwrite (&bytesData, sizeof (bytesData), 1, fd) != 1){
    return -1;
  }
  
  uint32_t sizeData = (uint32_t)  values.size ();
  if (fwrite (&sizeData, sizeof (sizeData), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&(values[0]), bytesData, sizeData, fd) != sizeData){
    return -1;
  }

  return 0;
}


int TimeSlice32::fromDisk (FILE *fd){
    // class serialized as:  voltConversion || displacement || bytesData || sizeData || Data...

  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint32_t)){
    fprintf (stderr, "ctrace.cpp::CTrace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("CTrace::CTrace(int): error reading Data");
  }

  return 0;
}

int TimeSlice32::toPng (char *fileName, list<string> *gnuplotCmds){
  map <uint32_t,int> elemRepts;                        // structure containing the n� of repetitions of each element.
  FILE *gnuplotPipe = popen("gnuplot -persist","w");   // gnuplot pipe.


  // problem opening the gnuPlot interface.
  if (gnuplotPipe <= 0) 
    {  
      perror ("CTimeSlice::toPng(char*): error opening gnuplot pipe");
      return -1;
    }


  // loop for counting the ocurrencies of each element in the TimeSlice.
  for (uint32_t i = 0; i < (values.size()); i++){
    if (elemRepts.find (values [i]) == elemRepts.end()){  // it is the first time that the element is found -> element count = 1.
      elemRepts [values[i]] = 1;
    }
    else{
      (elemRepts.find(values[i])->second)++; // it exist in the map, so the count is increased.
      }
  }

  // send commands to gnuplot
  fprintf(gnuplotPipe, "set terminal png\n");                                             // output as png
  fprintf(gnuplotPipe, "set output \"%s\"\n ",fileName);                                  // output name
  fprintf(gnuplotPipe, "set xlabel \"voltage [mv]\"\n");                                  // set x label
  fprintf(gnuplotPipe, "set ylabel \"Frequency of occurrence\"\n");                       // set y label
  fprintf(gnuplotPipe, "plot '-' using 1:2 notitle with boxes\n");                        // set scale and representation mode

  map <uint32_t,int>::iterator it;

  // set 0 counts to voltage values that are not found in the slice (to be shown in the histogram).
  for (uint32_t i = elemRepts.begin () -> first; i < (elemRepts.rbegin()) -> first; i++){  // search between the lower and higher voltage

    if (elemRepts.find (i) == elemRepts.end()){  // voltage not found.
      elemRepts [i] = 0;  // 0 assigned to the not found voltage.
    }
  }

  // send data to gnuplot
  for (it = elemRepts.begin (); it != elemRepts.end(); it++){
    fprintf(gnuplotPipe, "%d %d\n", it->first, it->second);
  }

  // metadata for "end of data"
  fprintf(gnuplotPipe, "e");

  // close gnuplot interface
  fprintf(gnuplotPipe, "\n");
  fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);

  // free memory and structures.
  fclose (gnuplotPipe);

  return 0;
}

TimeSlice16::TimeSlice16 (double voltConversion, 
			    double displacement, 
			    uint16_t* values, 
			    size_t size) : TimeSlice (voltConversion, displacement){

  this -> values.resize (size);

  for (size_t i = 0; i < size; i++){
    this -> values [i] = values [i];
  }
}
TimeSlice16::TimeSlice16 (double voltConversion, 
			    double displacement, 
			    size_t size) : TimeSlice (voltConversion, displacement){

  values.resize (size);
}

TimeSlice16::TimeSlice16 () : TimeSlice (){}

int TimeSlice16::toDisk (FILE *fd){
  // class serialized as: voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&displacement, sizeof (displacement), 1, fd) != 1){
    return -1;
  }

  uint8_t bytesData = (uint8_t) sizeof (uint16_t);
  if (fwrite (&bytesData, sizeof (bytesData), 1, fd) != 1){
    return -1;
  }
  
  uint32_t sizeData = (uint32_t)  values.size ();
  if (fwrite (&sizeData, sizeof (sizeData), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&(values[0]), bytesData, sizeData, fd) != sizeData){
    return -1;
  }

  return 0;
}

int TimeSlice16::fromDisk (FILE *fd){
  // class serialized as: voltConversion || displacement || bytesData || sizeData || Data...

  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint16_t)){
    fprintf (stderr, "ctrace.cpp::CTrace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("CTrace::CTrace(int): error reading Data");
  }

  return 0;
}

int TimeSlice16::toPng (char *fileName, list<string> *gnuplotCmds){
  map <uint16_t,int> elemRepts;                        // structure containing the n� of repetitions of each element.
  FILE *gnuplotPipe = popen("gnuplot -persist","w");   // gnuplot pipe.


  // problem opening the gnuPlot interface.
  if (gnuplotPipe <= 0) 
    {  
      perror ("TimeSlice::toPng(char*): error opening gnuplot pipe");
      return -1;
    }


  // loop for counting the ocurrencies of each element in the TimeSlice.
  for (uint32_t i = 0; i < (values.size()); i++){
    if (elemRepts.find (values [i]) == elemRepts.end()){  // it is the first time that the element is found -> element count = 1.
      elemRepts [values[i]] = 1;
    }
    else{
      (elemRepts.find(values[i])->second)++; // it exist in the map, so the count is increased.
      }
  }

  // send commands to gnuplot
  fprintf(gnuplotPipe, "set terminal png\n");                                             // output as png
  fprintf(gnuplotPipe, "set output \"%s\"\n ",fileName);                                  // output name
  fprintf(gnuplotPipe, "set xlabel \"voltage [mv]\"\n");                                  // set x label
  fprintf(gnuplotPipe, "set ylabel \"Frequency of occurrence\"\n");                       // set y label
  fprintf(gnuplotPipe, "plot '-' using 1:2 notitle with boxes\n");                        // set scale and representation mode

  map <uint16_t,int>::iterator it;

  // set 0 counts to voltage values that are not found in the slice (to be shown in the histogram).
  for (uint16_t i = elemRepts.begin () -> first; i < (elemRepts.rbegin()) -> first; i++){  // search between the lower and higher voltage

    if (elemRepts.find (i) == elemRepts.end()){  // voltage not found.
      elemRepts [i] = 0;  // 0 assigned to the not found voltage.
    }
  }

  // send data to gnuplot
  for (it = elemRepts.begin (); it != elemRepts.end(); it++){
    fprintf(gnuplotPipe, "%d %d\n", it->first, it->second);
  }

  // metadata for "end of data"
  fprintf(gnuplotPipe, "e");

  // close gnuplot interface
  fprintf(gnuplotPipe, "\n");
  fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);

  // free memory and structures.
  fclose (gnuplotPipe);

  return 0;
}

TimeSlice8::TimeSlice8 (double voltConversion, 
			  double displacement, 
			  uint8_t* values, 
			  size_t size) : TimeSlice (voltConversion, displacement){

  this -> values.resize (size);

  for (size_t i = 0; i < size; i++){
    this -> values [i] = values [i];
  }
}
TimeSlice8::TimeSlice8(double voltConversion, 
			 double displacement, 
			 size_t size) : TimeSlice (voltConversion, displacement){
  
  values.resize (size);
}

TimeSlice8::TimeSlice8 () : TimeSlice (){}

int TimeSlice8::toDisk (FILE *fd){
  // class serialized as: voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&displacement, sizeof (displacement), 1, fd) != 1){
    return -1;
  }

  uint8_t bytesData = (uint8_t) sizeof (uint8_t);
  if (fwrite (&bytesData, sizeof (bytesData), 1, fd) != 1){
    return -1;
  }
  
  uint32_t sizeData = (uint32_t)  values.size ();
  if (fwrite (&sizeData, sizeof (sizeData), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&(values[0]), bytesData, sizeData, fd) != sizeData){
    return -1;
  }

  return 0;
}

int TimeSlice8::fromDisk (FILE *fd){
  // class serialized as:  voltConversion || displacement || bytesData || sizeData || Data...


  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint8_t)){
    fprintf (stderr, "ctrace.cpp::CTrace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("CTrace::CTrace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("CTrace::CTrace(int): error reading Data");
  }

  return 0;
}

int TimeSlice8::toPng (char *fileName, list<string> *gnuplotCmds){
  map <uint8_t,int> elemRepts;                        // structure containing the n� of repetitions of each element.
  FILE *gnuplotPipe = popen("gnuplot -persist","w");   // gnuplot pipe.


  // problem opening the gnuPlot interface.
  if (gnuplotPipe <= 0) 
    {  
      perror ("CTimeSlice::toPng(char*): error opening gnuplot pipe");
      return -1;
    }


  // loop for counting the ocurrencies of each element in the TimeSlice.
  for (uint32_t i = 0; i < (values.size()); i++){
    if (elemRepts.find (values [i]) == elemRepts.end()){  // it is the first time that the element is found -> element count = 1.
      elemRepts [values[i]] = 1;
    }
    else{
      (elemRepts.find(values[i])->second)++; // it exist in the map, so the count is increased.
      }
  }

  // send commands to gnuplot
  fprintf(gnuplotPipe, "set terminal png\n");                                             // output as png
  fprintf(gnuplotPipe, "set output \"%s\"\n ",fileName);                                  // output name
  fprintf(gnuplotPipe, "set xlabel \"voltage [mv]\"\n");                                  // set x label
  fprintf(gnuplotPipe, "set ylabel \"Frequency of occurrence\"\n");                       // set y label
  fprintf(gnuplotPipe, "plot '-' using 1:2 notitle with boxes\n");                        // set scale and representation mode

  map <uint8_t,int>::iterator it;

  // set 0 counts to voltage values that are not found in the slice (to be shown in the histogram).
  for (uint8_t i = elemRepts.begin () -> first; i < (elemRepts.rbegin()) -> first; i++){  // search between the lower and higher voltage

    if (elemRepts.find (i) == elemRepts.end()){  // voltage not found.
      elemRepts [i] = 0;  // 0 assigned to the not found voltage.
    }
  }

  // send data to gnuplot
  for (it = elemRepts.begin (); it != elemRepts.end(); it++){
    fprintf(gnuplotPipe, "%d %d\n", it->first, it->second);
  }

  // metadata for "end of data"
  fprintf(gnuplotPipe, "e");

  // close gnuplot interface
  fprintf(gnuplotPipe, "\n");
  fprintf(gnuplotPipe,"exit \n");  
  fflush(gnuplotPipe);

  // free memory and structures.
  fclose (gnuplotPipe);

  return 0;
}

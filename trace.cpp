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


#include "trace.h"
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

Trace::Trace (uint64_t samplingRate, double voltConversion, double displacement){
  this -> samplingRate = samplingRate;
  this -> voltConversion = voltConversion;
  this -> displacement = displacement;
}

Trace::Trace (){
  
}


Trace32::Trace32 (uint64_t samplingRate, 
		    double voltConversion, 
		    double displacement, 
		    uint32_t* values, 
		    size_t size) : Trace (samplingRate, voltConversion, displacement){

  this -> values.resize (size);
  
  for (size_t i = 0; i < size; i++)
    this -> values [i] = values [i];
  
}
Trace32::Trace32 (uint64_t samplingRate, 
		    double voltConversion, 
		    double displacement, 
		    size_t size) : Trace (samplingRate, voltConversion, displacement){

  this -> values.resize (size);
}

Trace32::Trace32 () : Trace (){}

int Trace32::toDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    return -1;
  }

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

int Trace32::fromDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...

  if (fread (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading samplingRate");
  }

  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint32_t)){
    fprintf (stderr, "trace.cpp::Trace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("Trace::Trace(int): error reading Data");
  }

  return 0;
}

int Trace32::toPng (char *fileName, list<string> *gnuplotCmds){
  FILE *gnuplotPipe = popen("gnuplot -persist","w");

  if (gnuplotPipe <= 0) 
    {  
      return -1;
    }

  // find the correct x-axis scale (ns, us, ms, sec)
  char* unit = NULL;
  unsigned int magnitude = log10 ((double) values.size () * samplingRate) / 3; // axis values shall be less than 1000. 
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

  //send added commands to gnuplot
  if (gnuplotCmds)
    for (list<string>::iterator it = gnuplotCmds->begin() ; it != gnuplotCmds->end(); it++)
      fprintf(gnuplotPipe, "%s\n", it->data());     // print nth command.


  fprintf(gnuplotPipe, "plot '-' using ($1 / %lld.):2 notitle with lines\n", divisor);     // set scale and representation mode


  // send data to gnuplot
  size_t sizeData = values.size ();
  for (size_t i = 0; i < sizeData; i++){
    fprintf(gnuplotPipe, "%lld %f\n", i * samplingRate, getValue (i));
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

Trace16::Trace16 (uint64_t samplingRate, 
		    double voltConversion, 
		    double displacement, 
		    uint16_t* values, 
		    size_t size) : Trace (samplingRate, voltConversion, displacement){

this -> values.resize (size);  

 for (size_t i = 0; i < size; i++)
   this -> values [i] = values [i];

}
Trace16::Trace16 (uint64_t samplingRate, 
		    double voltConversion, 
		    double displacement, 
		    size_t size) : Trace (samplingRate, voltConversion, displacement){

  values.resize (size);
}

Trace16::Trace16 () : Trace (){}



int Trace16::toDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    return -1;
  }

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

int Trace16::fromDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...
  
  if (fread (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading samplingRate");
  }
  
  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint16_t)){
    fprintf (stderr, "trace.cpp::Trace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("Trace::Trace(int): error reading Data");
  }

  return 0;
}

int Trace16::toPng (char *fileName, list<string> *gnuplotCmds){
  FILE *gnuplotPipe = popen("gnuplot -persist","w");

  if (gnuplotPipe <= 0) 
    {  
      return -1;
    }

  // find the correct x-axis scale (ns, us, ms, sec)
  char* unit = NULL;
  unsigned int magnitude = log10 ((double) values.size () * samplingRate) / 3; // axis values shall be less than 1000. 
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

  //send added commands to gnuplot
  if (gnuplotCmds)
    for (list<string>::iterator it = gnuplotCmds->begin() ; it != gnuplotCmds->end(); it++)
      fprintf(gnuplotPipe, "%s\n", it->data());     // print nth command.


  fprintf(gnuplotPipe, "plot '-' using ($1 / %lld.):2 notitle with lines\n", divisor);     // set scale and representation mode


  // send data to gnuplot
  size_t sizeData = values.size ();
  for (size_t i = 0; i < sizeData; i++){
    fprintf(gnuplotPipe, "%lld %f\n", i * samplingRate, getValue (i));
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

Trace8::Trace8 (uint64_t samplingRate, 
		  double voltConversion, 
		  double displacement, 
		  uint8_t* values, 
		  size_t size) : Trace (samplingRate, voltConversion, displacement){

this -> values.resize (size);  

 for (size_t i = 0; i < size; i++)
   this -> values [i] = values [i];
  
}

Trace8::Trace8(uint64_t samplingRate, 
		 double voltConversion, 
		 double displacement, 
		 size_t size) : Trace (samplingRate, voltConversion, displacement){
  
  values.resize (size);
}

Trace8::Trace8 () : Trace (){}

int Trace8::toDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...

  if (fwrite (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    return -1;
  }

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

int Trace8::fromDisk (FILE *fd){
  // class serialized as: samplingRate || voltConversion || displacement || bytesData || sizeData || Data...
  
  if (fread (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading samplingRate");
  }
  
  if (fread (&voltConversion, sizeof (voltConversion), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading voltConversion");
  }

  if (fread (&displacement, sizeof (displacement), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading displacement");
  }

  uint8_t bytesData;
  if (fread (&bytesData, sizeof (bytesData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading bytesData");
  }
  
  // The type instantiation of the object created must be equal to the serialized object in file
  if (bytesData != (uint8_t) sizeof (uint8_t)){
    fprintf (stderr, "trace.cpp::Trace (FILE *fd) : Data stored with a resolution not compatible with the CTrace type instatiation\n");
  }
  
  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), bytesData, sizeData, fd) != sizeData){
    perror ("Trace::Trace(int): error reading Data");
  }

  return 0;
}

int Trace8::toPng (char *fileName, list<string> *gnuplotCmds){
  FILE *gnuplotPipe = popen("gnuplot -persist","w");

  if (gnuplotPipe <= 0) 
    {  
      return -1;
    }

  // find the correct x-axis scale (ns, us, ms, sec)
  char* unit = NULL;
  unsigned int magnitude = log10 ((double) values.size () * samplingRate) / 3; // axis values shall be less than 1000. 
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

  //send added commands to gnuplot
  if (gnuplotCmds)
    for (list<string>::iterator it = gnuplotCmds->begin() ; it != gnuplotCmds->end(); it++)
      fprintf(gnuplotPipe, "%s\n", it->data());     // print nth command.


  fprintf(gnuplotPipe, "plot '-' using ($1 / %lld.):2 notitle with lines\n", divisor);     // set scale and representation mode


  // send data to gnuplot
  size_t sizeData = values.size ();
  for (size_t i = 0; i < sizeData; i++){
    fprintf(gnuplotPipe, "%lld %f\n", i * samplingRate, getValue (i));
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

 // Contructor initializating elements
StatTrace::StatTrace (uint64_t samplingRate, size_t size){
  this -> samplingRate = samplingRate;
  values.resize (size);
}

int StatTrace::toDisk (FILE *fd){   // initializes the object stored in the file descriptor.
  // class serialized as: samplingRate || sizeData || Data...

  if (fwrite (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    return -1;
  }
  
  uint32_t sizeData = (uint32_t)  values.size ();
  if (fwrite (&sizeData, sizeof (sizeData), 1, fd) != 1){
    return -1;
  }

  if (fwrite (&(values[0]), sizeof (values [0]), sizeData, fd) != sizeData){
    return -1;
  }
  
  return 0;
}

int StatTrace::fromDisk (FILE *fd){ // stores the object in the file descriptor.
  // class serialized as: samplingRate || sizeData || Data...

  if (fread (&samplingRate, sizeof (samplingRate), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading samplingRate");
  }

  uint32_t sizeData;
  if (fread (&sizeData, sizeof (sizeData), 1, fd) != 1){
    perror ("Trace::Trace(int): error reading sizeData");
  }
  
  // resize the valarray superclass to store the data.
  values.resize (sizeData);

  // store the data into the superclass.
  if (fread (&(values [0]), sizeof (values [0]), sizeData, fd) != sizeData){
    perror ("Trace::Trace(int): error reading Data");
  }

  return 0;
}

int StatTrace::toPng (char *fileName, list<string> *gnuplotCmds){  // graphical representation in file.
  FILE *gnuplotPipe = popen("gnuplot -persist","w");

  if (gnuplotPipe <= 0) 
    {  
      return -1;
    }

  // find the correct x-axis scale (ns, us, ms, sec)
  char* unit = NULL;
  unsigned int magnitude = log10 ((double) values.size () * samplingRate) / 3; // axis values shall be less than 1000. 
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

  //send added commands to gnuplot
  if (gnuplotCmds)
    for (list<string>::iterator it = gnuplotCmds->begin() ; it != gnuplotCmds->end(); it++)
      fprintf(gnuplotPipe, "%s\n", it->data());     // print nth command.


  fprintf(gnuplotPipe, "plot '-' using ($1 / %lld.):2 notitle with lines\n", divisor);     // set scale and representation mode


  // send data to gnuplot
  size_t sizeData = values.size ();
  for (size_t i = 0; i < sizeData; i++){
    fprintf(gnuplotPipe, "%lld %f\n", i * samplingRate, getValue (i));
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


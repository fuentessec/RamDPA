/**
 * @file   cinterfaces.h
 * @author Alberto Fuentes <fuentes@fuentes-desktop>
 * @date   Thu Nov 29 19:25:44 2012
 * 
 * @brief  This file contains several interfaces used by the toolbox classes.
 * 
 * 
 */
#ifndef INTERFACES_H
#define INTERFACES_H
#include <list>
#include <string>
#include <stdio.h>

#define CINTERFACES

using namespace std;

/**
 * @brief An Interface class that specifies that its subclasses can be printed out if gnuplot is installed.
 * 
 */

class Graphicable {
 public:

  /** 
   * Produces a png file with the graphical interpretation of the object.
   * 
   * @param fileName path of the output file (i.e. "graph.png"). If the file does not exist It will be created. If exist it will be rewrited.
   * @param gnuplotCmds list of extra commands passed to gnuplot before plotting.
   * 
   * @return 0 on success, -1 I.O.C
   */
  virtual int toPng (char *fileName, list<string> *gnuplotCmds = NULL) = 0;  // graphical representation in file.
};


/**
 * @brief An Interface class that specifies that the subclasses can be stored in a file.
 * 
 */
class FileStorage {
 public:

  /** 
   * Stores the object to into the file descriptor.
   * 
   * @param fd the specified file opened as writable binary.
   * 
   * @return 0 on success, -1 I.O.C
   */
  virtual int toDisk (FILE *fd) = 0;   // initializes the object stored in the file descriptor.

  /** 
   * Recovers the object stored in file. Previously the object shall be stored in the file pointed by
   * the file descriptor with toDisc function.
   * 
   * @param fd the specified file opened as readeable binary
   * 
   * @return 0 on success, -1 I.O.C
   */
  virtual int fromDisk (FILE *fd) = 0; // stores the object in the file descriptor.
};
#endif
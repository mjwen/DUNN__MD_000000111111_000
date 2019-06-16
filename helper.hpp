//
// CDDL HEADER START
//
// The contents of this file are subject to the terms of the Common Development
// and Distribution License Version 1.0 (the "License").
//
// You can obtain a copy of the license at
// http://www.opensource.org/licenses/CDDL-1.0.  See the License for the
// specific language governing permissions and limitations under the License.
//
// When distributing Covered Code, include this CDDL HEADER in each file and
// include the License file in a prominent location with the name LICENSE.CDDL.
// If applicable, add the following below this CDDL HEADER, with the fields
// enclosed by brackets "[]" replaced with your own identifying information:
//
// Portions Copyright (c) [yyyy] [name of copyright owner]. All rights reserved.
//
// CDDL HEADER END
//

//
// Copyright (c) 2019, Regents of the University of Minnesota.
// All rights reserved.
//
// Contributors:
//    Mingjian Wen
//

#ifndef HELPER_H_
#define HELPER_H_

#include <cmath>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <cstring>


#define MAXLINE 20480
typedef double VectorOfSizeDIM[3];
typedef double VectorOfSizeSix[6];


//******************************************************************************
// Allocating memory
//******************************************************************************

//********************
// 1D Array
//********************
template<class T>
void AllocateAndInitialize1DArray(T *& arrayPtr, int const extent)
{
  arrayPtr = new T[extent];
  for (int i = 0; i < extent; ++i) { arrayPtr[i] = 0.0; }
}


// deallocate memory
template<class T>
void Deallocate1DArray(T *& arrayPtr)
{
  delete[] arrayPtr;
  // nullify pointer
  arrayPtr = NULL;
}


//********************
// 2D Array
//********************
template<class T>
void AllocateAndInitialize2DArray(T **& arrayPtr,
                                  int const extentZero,
                                  int const extentOne)
{
  arrayPtr = new T *[extentZero];
  arrayPtr[0] = new T[extentZero * extentOne];
  for (int i = 1; i < extentZero; ++i)
  { arrayPtr[i] = arrayPtr[i - 1] + extentOne; }

  // initialize
  for (int i = 0; i < extentZero; ++i)
  {
    for (int j = 0; j < extentOne; ++j) { arrayPtr[i][j] = 0.0; }
  }
}


// deallocate memory
template<class T>
void Deallocate2DArray(T **& arrayPtr)
{
  if (arrayPtr != NULL) { delete[] arrayPtr[0]; }
  delete[] arrayPtr;

  // nullify pointer
  arrayPtr = NULL;
}


//********************
// 3D Array
//********************
template<class T>
void AllocateAndInitialize3DArray(T ***& arrayPtr,
                                  int const extentZero,
                                  int const extentOne,
                                  int const extentTwo)
{
  arrayPtr = new T **[extentZero];
  arrayPtr[0] = new T *[extentZero * extentOne];
  arrayPtr[0][0] = new T[extentZero * extentOne * extentTwo];

  for (int i = 1; i < extentZero; ++i)
  {
    arrayPtr[i] = arrayPtr[i - 1] + extentOne;
    arrayPtr[i][0] = arrayPtr[i - 1][0] + extentOne * extentTwo;
  }

  for (int i = 0; i < extentZero; ++i)
  {
    for (int j = 1; j < extentOne; ++j)
    { arrayPtr[i][j] = arrayPtr[i][j - 1] + extentTwo; }
  }

  // initialize
  for (int i = 0; i < extentZero; ++i)
  {
    for (int j = 0; j < extentOne; ++j)
    {
      for (int k = 0; k < extentTwo; ++k) { arrayPtr[i][j][k] = 0.0; }
    }
  }
}


// deallocate memory
template<class T>
void Deallocate3DArray(T ***& arrayPtr)
{
  if (arrayPtr != NULL)
  {
    if (arrayPtr[0] != NULL) { delete[] arrayPtr[0][0]; }
    delete[] arrayPtr[0];
  }
  delete[] arrayPtr;

  // nullify pointer
  arrayPtr = NULL;
}


//******************************************************************************
// process virial
//******************************************************************************
void ProcessVirialTerm(double const dEidr,
                       double const rij,
                       double const * const r_ij,
                       VectorOfSizeSix virial);

void ProcessParticleVirialTerm(double const dEidr,
                               double const rij,
                               double const * const r_ij,
                               int const i,
                               int const j,
                               VectorOfSizeSix * const particleVirial);

void ComputeMeanAndStdev(std::vector<double> const & data,
                         double & mean,
                         double & stdev);

#endif



//******************************************************************************
// process parameter file
//******************************************************************************
void getNextDataLine(FILE * const filePtr, char * const nextLine,
    int const maxSize, int * endOfFileFlag);

int getXdouble(char * linePtr, const int N, double * list);
int getXint(char * linePtr, const int N, int * list);
void lowerCase(char * linePtr);


//******************************************************************************
// others
//******************************************************************************

// compute the mean and standard deviation of vector
void ComputeMeanAndStdev(std::vector<double> const & v, double & mean, double & stdev);

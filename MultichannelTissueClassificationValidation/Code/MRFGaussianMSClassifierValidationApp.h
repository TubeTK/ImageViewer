/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    MRFGaussianMSClassifierValidationApp.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MRFGaussianMSClassifierValidationApp_h
#define _MRFGaussianMSClassifierValidationApp_h

#include <string>
#include "MSClassifierApplicationBase.h"
#include "MSClassifierValidationInputParser.h"
#include "MRFGaussianImageMSClassifierApp.h"
#include "MSClassifierValidationOutput.h"
#include "itkArray.h"

namespace itk
{

/** \class MRFGaussianMSClassifierValidationApp
 * 
 * This class is an application that 
 * [1] reads in user specified images from the MS data directory 
 * (use readme for the data format), 
 * [2] performs gaussian classifier based labelling of two brain volumes 
 * [3] calculate the lesion load and compare with the true volume
 * this data set is a phantom with simulated lesion of known volume, and
 * [5] write the final lesion volume to file.
 *
 * This class is activatived by method Execute().
 *
 * Inputs:
 * - path to MS data directory (filename syntax: patientID + extension)
 * - extensions for the 1st channel 
 * - extension for the 2nd channel
 * - output result file
 * - the patient ID
 * - the number of slices in the patient image/segmentation
 * - the algorithm parameter filename (see syntax for the parameter file)
 *
 */

template < typename TImage,
           typename TMaskImage >
class MRFGaussianMSClassifierValidationApp : 
public MSClassifierApplicationBase<
  MSClassifierValidationInputParser <TImage,TMaskImage>,
  MRFGaussianImageMSClassifierApp<TImage,TMaskImage>,
  MSClassifierValidationOutput<TMaskImage> >
{
public:

  /** Standard class typedefs. */
  typedef MRFGaussianMSClassifierValidationApp Self;

  typedef MSClassifierApplicationBase <
    MSClassifierValidationInputParser<TImage,TMaskImage>,
    MRFGaussianImageMSClassifierApp<TImage,TMaskImage>,
    MSClassifierValidationOutput<TMaskImage> >   Superclass;

  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(MRFGaussianMSClassifierValidationApp, MSClassifierApplicationBase);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Image dimension. */
  enum{  ImageDimension = TImage::ImageDimension };

  /** Image types. */
  typedef TImage               ImageType;
  typedef TMaskImage           MaskImageType;
  typedef TMaskImage           TruthImageType;
  typedef Array<unsigned int>  IntegerArrayType;
  typedef typename std::string                   StringType; 
  typedef typename std::vector< StringType >     StringVectorType; 

  /** Set the input image directory path. */
  itkSetStringMacro( ImageDirectoryName );

  /** Set the IBSR "20Nomrals_T1_brain" directory path. */
  itkSetStringMacro( BrainSegmentationDirectoryName );

  /** Set the patient ID. */
  itkSetStringMacro( PatientID );
  itkGetStringMacro( PatientID );

  /** Set the starting slice number in the input image. */
  itkSetMacro( StartSliceNumber, signed long );
  itkGetMacro( StartSliceNumber, signed long );

  /** Set the number of slices in the input image. */
  itkSetMacro( NumberOfSlices, unsigned long );
  itkGetMacro( NumberOfSlices, unsigned long );

  /** Set the starting slice number of the segmentation file. */
  itkSetMacro( StartSegSliceNumber, signed long );
  itkGetMacro( StartSegSliceNumber, signed long );

  /** Set the number of slices in the segmentation image. */
  itkSetMacro( NumberOfSegSlices, unsigned long );
  itkGetMacro( NumberOfSegSlices, unsigned long );

  /** Set the number of channels in the input image. */
  itkSetMacro( NumberOfChannels, unsigned long );
  itkGetMacro( NumberOfChannels, unsigned long );

  /** Set the number of classes in the input image. */
  itkSetMacro( NumberOfClasses, unsigned long );
  itkGetMacro( NumberOfClasses, unsigned long );

  /** Set/Get the number of iteration of the Iterated Conditional Mode
   * (ICM) algorithm. A default value is set at 50 iterations. */
  itkSetMacro(MaximumNumberOfIterations, unsigned int);
  itkGetMacro(MaximumNumberOfIterations, unsigned int);

  /** Set/Get the error tollerance level which is used as a threshold
   * to quit the iterations */
  itkSetMacro(ErrorTolerance, double);
  itkGetMacro(ErrorTolerance, double);

  /** Set/Get the degree of smoothing desired 
   * */
  itkSetMacro(SmoothingFactor, double);
  itkGetMacro(SmoothingFactor, double);

  /** Sets the radius for the neighborhood, for the MRF filter */
  itkSetMacro( NeighborhoodRadius, unsigned long );
  itkGetMacro( NeighborhoodRadius, unsigned long );

  /** Set input parameter file */
  itkSetStringMacro( ParameterFileName );

  /** Set output transformation filename. */
  itkSetStringMacro( OutputFileName );

  /** Set/Get the tissue labels in the truth data set */
  itkSetMacro( TruthLabels, IntegerArrayType );
  itkGetConstReferenceMacro( TruthLabels, IntegerArrayType );

  /** Set append output file boolean. */
  itkSetMacro( AppendOutputFile, bool );
  itkGetMacro( AppendOutputFile, bool );
  itkBooleanMacro( AppendOutputFile );

  /** Get the file extension vector */
  StringVectorType GetFileExtensions()
    {
    return m_FileExtensions;
    }

  /** Add the file extensions */
  void AddFileExtension(const char* buffer)
    {
    m_FileExtensions.push_back( buffer );
    }   


protected:
  MRFGaussianMSClassifierValidationApp();
  virtual ~MRFGaussianMSClassifierValidationApp(){};

  /** Initialize the input parser. */
  virtual void InitializeParser();

  /*** Initialize the preprocessor */
  virtual void InitializeMSClassifier();

  /*** Initialize the output generator. */
  virtual void InitializeOutputGenerator();

private:

  StringType                    m_ImageDirectoryName;
  StringType                    m_BrainSegmentationDirectoryName;
  StringType                    m_PatientID;
  signed long                   m_StartSliceNumber;
  unsigned long                 m_NumberOfSlices;
  signed long                   m_StartSegSliceNumber;
  unsigned long                 m_NumberOfSegSlices;
  unsigned long                 m_NumberOfChannels;
  unsigned long                 m_NumberOfClasses;
  IntegerArrayType              m_TruthLabels;

  StringType                    m_ParameterFileName;
  StringType                    m_OutputFileName;
  bool                          m_AppendOutputFile;

  StringVectorType              m_FileExtensions;
  StringType                    m_tempstring;

  unsigned int                  m_MaximumNumberOfIterations;
  unsigned int                  m_NeighborhoodRadius;
  double                        m_ErrorTolerance;   
  double                        m_SmoothingFactor; 

};


} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "MRFGaussianMSClassifierValidationApp.txx"
#endif

#endif


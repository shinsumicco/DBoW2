/**
 * File: FORB.h
 * Date: June 2012
 * Author: Dorian Galvez-Lopez
 * Description: functions for ORB descriptors
 * License: see the LICENSE.txt file
 */

#ifndef __D_T_FORB__
#define __D_T_FORB__

#include <vector>
#include <string>

#include <opencv2/core.hpp>

#include "DBoW2/FClass.h"

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace DBoW2 {

/**
 * Functions to manipulate BRIEF descriptors
 */
class DLL_EXPORT FORB : protected FClass {
public:
  //! Descriptor length (in bytes)
  static constexpr int L = 32;

  //! Descriptor type
  using TDescriptor = cv::Mat;
  //! Pointer to a single descriptor
  using pDescriptor = const TDescriptor*;

  /**
   * Calculates the mean value of a set of descriptors
   * @param descriptors
   * @param mean mean descriptor
   */
  static void meanValue(const std::vector<pDescriptor>& descriptors, TDescriptor& mean);

  /**
   * Calculates the distance between two descriptors
   * @param a
   * @param b
   * @return distance
   */
  static double distance(const TDescriptor& a, const TDescriptor& b);

  /**
   * Returns a string version of the descriptor
   * @param a descriptor
   * @return string version
   */
  static std::string toString(const TDescriptor& a);

  /**
   * Returns a descriptor from a string
   * @param a descriptor
   * @param s string version
   */
  static void fromString(TDescriptor& a, const std::string& s);

  /**
   * Returns a mat with the descriptors in float format
   * @param descriptors
   * @param mat (out) NxL 32F matrix
   */
  static void toMat32F(const std::vector<TDescriptor>& descriptors, cv::Mat& mat);

  /**
   * Returns a mat with the descriptors in float format
   * @param descriptors NxL CV_8U matrix
   * @param mat (out) NxL 32F matrix
   */
  static void toMat32F(const cv::Mat& descriptors, cv::Mat& mat);

  /**
   * Returns a matrix with the descriptor in OpenCV format
   * @param descriptors vector of N row descriptors
   * @param mat (out) NxL CV_8U matrix
   */
  static void toMat8U(const std::vector<TDescriptor>& descriptors, cv::Mat& mat);
};

} // namespace DBoW2

#endif

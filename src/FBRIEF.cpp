/**
 * File: FBRIEF.cpp
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: functions for BRIEF descriptors
 * License: see the LICENSE.txt file
 */

#include <vector>
#include <string>
#include <sstream>

#include "DBoW2/FBRIEF.h"

using namespace std;

namespace DBoW2 {

// --------------------------------------------------------------------------

void FBRIEF::meanValue(const std::vector<FBRIEF::pDescriptor>& descriptors, FBRIEF::TDescriptor& mean) {
  mean.reset();

  if (descriptors.empty())
    return;

  const int N2 = descriptors.size() / 2;

  vector<int> counters(FBRIEF::L, 0);

  vector<FBRIEF::pDescriptor>::const_iterator it;
  for (it = descriptors.begin(); it != descriptors.end(); ++it) {
    const FBRIEF::TDescriptor& desc = **it;
    for (int i = 0; i < FBRIEF::L; ++i) {
      if (desc[i])
        counters[i]++;
    }
  }

  for (int i = 0; i < FBRIEF::L; ++i) {
    if (counters[i] > N2)
      mean.set(i);
  }
}

// --------------------------------------------------------------------------

double FBRIEF::distance(const FBRIEF::TDescriptor& a, const FBRIEF::TDescriptor& b) {
  return (double)(a ^ b).count();
}

// --------------------------------------------------------------------------

std::string FBRIEF::toString(const FBRIEF::TDescriptor& a) {
  return a.to_string();
}

// --------------------------------------------------------------------------

void FBRIEF::fromString(FBRIEF::TDescriptor& a, const std::string& s) {
  stringstream ss(s);
  ss >> a;
}

// --------------------------------------------------------------------------

void FBRIEF::toMat32F(const std::vector<TDescriptor>& descriptors, cv::Mat& mat) {
  if (descriptors.empty()) {
    mat.release();
    return;
  }

  const int N = descriptors.size();

  mat.create(N, FBRIEF::L, CV_32F);

  for (int i = 0; i < N; ++i) {
    const TDescriptor& desc = descriptors[i];
    float* p = mat.ptr<float>(i);
    for (int j = 0; j < FBRIEF::L; ++j, ++p) {
      *p = (desc[j] ? 1 : 0);
    }
  }
}

// --------------------------------------------------------------------------

} // namespace DBoW2

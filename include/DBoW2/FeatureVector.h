/**
 * File: FeatureVector.h
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: feature vector
 * License: see the LICENSE.txt file
 */

#ifndef __D_T_FEATURE_VECTOR__
#define __D_T_FEATURE_VECTOR__

#include <map>
#include <vector>
#include <iostream>

#include "DBoW2/BowVector.h"

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace DBoW2 {

/**
 * Vector of nodes with indexes of local features
 */
class DLL_EXPORT FeatureVector : public std::map<NodeId, std::vector<unsigned int>> {
public:
  /**
   * Constructor
   */
  FeatureVector();

  /**
   * Destructor
   */
  ~FeatureVector();

  /**
   * Adds a feature to an existing node, or adds a new node with an initial
   * feature
   * @param id node id to add or to modify
   * @param i_feature index of feature to add to the given node
   */
  void addFeature(const NodeId id, const unsigned int i_feature);

  /**
   * Sends a string versions of the feature vector through the stream
   * @param out stream
   * @param v feature vector
   */
  friend std::ostream& operator<<(std::ostream& out, const FeatureVector& v);
};

} // namespace DBoW2

#endif

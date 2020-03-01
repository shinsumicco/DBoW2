/**
 * File: BowVector.h
 * Date: March 2011
 * Author: Dorian Galvez-Lopez
 * Description: bag of words vector
 * License: see the LICENSE.txt file
 */

#ifndef __D_T_BOW_VECTOR__
#define __D_T_BOW_VECTOR__

#include <iostream>
#include <map>
#include <vector>

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace DBoW2 {

//! ID of words
using WordId = unsigned int;

//! Value of a word
using WordValue = double;

//! ID of nodes in the vocabulary treee
using NodeId = unsigned int;

//! L-norms for normalization
enum LNorm {
  L1,
  L2
};

//! Weighting type
enum WeightingType {
  TF_IDF,
  TF,
  IDF,
  BINARY
};

//! Scoring type
enum ScoringType {
  L1_NORM,
  L2_NORM,
  CHI_SQUARE,
  KL,
  BHATTACHARYYA,
  DOT_PRODUCT
};

/**
 * Vector of words to represent images
 */
class DLL_EXPORT BowVector : public std::map<WordId, WordValue> {
public:
  /**
   * Constructor
   */
  BowVector();

  /**
   * Destructor
   */
  ~BowVector();

  /**
   * Adds a value to a word value existing in the vector, or creates a new word with the given value
   * @param id word id to look for
   * @param v value to create the word with, or to add to existing word
   */
  void addWeight(const WordId id, const WordValue v);

  /**
   * Adds a word with a value to the vector only if this does not exist yet
   * @param id word id to look for
   * @param v value to give to the word if this does not exist
   */
  void addIfNotExist(const WordId id, const WordValue v);

  /**
   * L1-Normalizes the values in the vector 
   * @param norm_type norm used
   */
  void normalize(const LNorm norm_type);

  /**
   * Prints the content of the bow vector
   * @param out stream
   * @param v
   */
  friend std::ostream& operator<<(std::ostream& out, const BowVector& v);

  /**
   * Saves the bow vector as a vector in a matlab file
   * @param filename
   * @param W number of words in the vocabulary
   */
  void saveM(const std::string& filename, const size_t W) const;
};

} // namespace DBoW2

#endif

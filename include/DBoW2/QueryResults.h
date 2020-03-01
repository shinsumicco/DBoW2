/**
 * File: QueryResults.h
 * Date: March, November 2011
 * Author: Dorian Galvez-Lopez
 * Description: structure to store results of database queries
 * License: see the LICENSE.txt file
 */

#ifndef __D_T_QUERY_RESULTS__
#define __D_T_QUERY_RESULTS__

#include <vector>

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace DBoW2 {

//! ID of entries of the database
using EntryId = unsigned int;

/**
 * Single result of a query
 */
class DLL_EXPORT Result {
public:
  //! Entry ID
  EntryId Id;

  //! Score obtained
  double Score;

  //! words in common (for debug)
  int nWords;

  //! scores (for debug)
  double bhatScore;
  double chiScore;
  double sumCommonVi;
  double sumCommonWi;
  double expectedChiScore;

  /**
   * Empty constructors
   */
  inline Result() {}

  /**
   * Creates a result with the given data
   * @param _id entry id
   * @param _score score
   */
  inline Result(const EntryId _id, const double _score)
      : Id(_id), Score(_score) {}

  /**
   * Compares the scores of two results
   * @return true iff this.score < r.score
   */
  inline bool operator<(const Result& r) const {
    return this->Score < r.Score;
  }

  /**
   * Compares the scores of two results
   * @return true iff this.score > r.score
   */
  inline bool operator>(const Result& r) const {
    return this->Score > r.Score;
  }

  /**
   * Compares the entry id of the result
   * @return true iff this.id == id
   */
  inline bool operator==(const EntryId id) const {
    return this->Id == id;
  }

  /**
   * Compares the score of this entry with a given one
   * @param s score to compare with
   * @return true iff this score < s
   */
  inline bool operator<(const double s) const {
    return this->Score < s;
  }

  /**
   * Compares the score of this entry with a given one
   * @param s score to compare with
   * @return true iff this score > s
   */
  inline bool operator>(const double s) const {
    return this->Score > s;
  }

  /**
   * Compares the score of two results
   * @param a
   * @param b
   * @return true iff a.Score > b.Score
   */
  static inline bool gt(const Result& a, const Result& b) {
    return a.Score > b.Score;
  }

  /**
   * Compares the scores of two results
   * @return true iff a.Score > b.Score
   */
  inline static bool ge(const Result& a, const Result& b) {
    return a.Score > b.Score;
  }

  /**
   * Returns true iff a.Score >= b.Score
   * @param a
   * @param b
   * @return true iff a.Score >= b.Score
   */
  static inline bool geq(const Result& a, const Result& b) {
    return a.Score >= b.Score;
  }

  /**
   * Returns true iff a.Score >= s
   * @param a
   * @param s
   * @return true iff a.Score >= s
   */
  static inline bool geqv(const Result& a, const double s) {
    return a.Score >= s;
  }

  /**
   * Returns true iff a.Id < b.Id
   * @param a
   * @param b
   * @return true iff a.Id < b.Id
   */
  static inline bool ltId(const Result& a, const Result& b) {
    return a.Id < b.Id;
  }

  /**
   * Prints a string version of the result
   * @param os ostream
   * @param ret Result to print
   */
  friend std::ostream& operator<<(std::ostream& os, const Result& ret);
};

/**
 * Multiple results from a query
 */
class DLL_EXPORT QueryResults : public std::vector<Result> {
public:
  /** 
   * Multiplies all the scores in the vector by factor
   * @param factor
   */
  inline void scaleScores(double factor);

  /**
   * Prints a string version of the results
   * @param os ostream
   * @param ret QueryResults to print
   */
  friend std::ostream& operator<<(std::ostream& os, const QueryResults& ret);

  /**
   * Saves a matlab file with the results 
   * @param filename 
   */
  void saveM(const std::string& filename) const;
};

// --------------------------------------------------------------------------

inline void QueryResults::scaleScores(double factor) {
  for (QueryResults::iterator qit = begin(); qit != end(); ++qit)
    qit->Score *= factor;
}

// --------------------------------------------------------------------------

} // namespace DBoW2

#endif

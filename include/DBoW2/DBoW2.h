/*
 * File: DBoW2.h
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: Generic include file for the DBoW2 classes and the specialized vocabularies and databases
 * License: see the LICENSE.txt file
 */

#ifndef __D_T_DBOW2__
#define __D_T_DBOW2__

#include "DBoW2/TemplatedVocabulary.h"
#include "DBoW2/TemplatedDatabase.h"
#include "DBoW2/BowVector.h"
#include "DBoW2/FeatureVector.h"
#include "DBoW2/QueryResults.h"
#include "DBoW2/FBRIEF.h"
#include "DBoW2/FORB.h"

//! ORB Vocabulary
using OrbVocabulary = DBoW2::TemplatedVocabulary<DBoW2::FORB::TDescriptor, DBoW2::FORB>;

//! ORB Database
using OrbDatabase = DBoW2::TemplatedDatabase<DBoW2::FORB::TDescriptor, DBoW2::FORB>;

//! BRIEF Vocabulary
using BriefVocabulary = DBoW2::TemplatedVocabulary<DBoW2::FBRIEF::TDescriptor, DBoW2::FBRIEF>;

//! BRIEF Database
using BriefDatabase = DBoW2::TemplatedDatabase<DBoW2::FBRIEF::TDescriptor, DBoW2::FBRIEF>;

#endif

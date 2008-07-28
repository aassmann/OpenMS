// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2007 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Mathias Walzer $
// --------------------------------------------------------------------------
//
#ifndef OPENMS_COMPARISON_CLUSTERING_AVERAGELINKAGE_H
#define OPENMS_COMPARISON_CLUSTERING_AVERAGELINKAGE_H

#include <vector>
#include <cfloat>
#include <fstream>

#include <OpenMS/DATASTRUCTURES/DistanceMatrix.h>
#include <OpenMS/COMPARISON/CLUSTERING/ClusterFunctor.h>
#include <OpenMS/KERNEL/StandardTypes.h>
#include <OpenMS/DATASTRUCTURES/String.h>
#include <OpenMS/CONCEPT/TimeStamp.h>

namespace OpenMS
{
	/**
		@brief AverageLinkage ClusterMethod

		The details of the score can be found in:
		LU, S. Y. AND FU, K. S. 1978. A sentence-to-sentence clustering procedure for pattern analysis. IEEE Trans. Syst. Man Cybern. 8,381-389.
		@see ClusterFunctor() base class.

		@ingroup SpectraClustering
	*/
	class AverageLinkage : public ClusterFunctor
	{
		public:

		/// default constructor
		AverageLinkage();

		/// copy constructor
		AverageLinkage(const AverageLinkage& source);

		/// destructor
		virtual ~AverageLinkage();

		/// assignment operator
		AverageLinkage& operator = (const AverageLinkage& source);


		/**
			@brief clusters the indices according to their respective element distances

			@param original_distance DistanceMatrix<double> containing the distances of the elements to be clustered
			@param actual_distance DistanceMatrix<double> containing the distances of the clusters at current stage
			@param clusters vector< vector<UInt> >, each vector<UInt> represents a cluster, its elements being the indices according to original_dist. @see ClusterFunctor() Base class.
			@param filepath String&, by default empty, when given, a dendrogram will be written in a file created in that path
			@param threshold double value, the minimal distance from which on cluster merging is considered unrealistic. By default set to 1, i.e. complete clustering until only one cluster remains
			@throw UnableToCreateFile thrown if for the given filepath no file can be created
			@throw ClusterFunctor::InsufficientInput thrown if input is <2

			The clustering method is average linkage, where the updated distances after merging two clusters
			are each the average distances between the elements of their clusters. @see @p getAveDist_
		*/
		void cluster(const DistanceMatrix<double>& original_distance, DistanceMatrix<double>& actual_distance, std::vector< std::vector<UInt> >& clusters, const String filepath="", const double threshold=1) const;

		/// creates a new instance of a CompleteLinkage object
		static ClusterFunctor* create()
		{
			return new AverageLinkage();
		}

		/// get the identifier for this object
		static const String getProductName()
		{
			return "AverageLinkage";
		}

		private:

		/**
			@brief gets the average distance between all elements of one cluster and all elements of another cluster.

			@param o first UInt index pointing to a cluster
			@param x second UInt index pointing to a cluster
			@param clusters the clusters
			@param original_dist matrix containing the distances between all clustered elements of @p clusters

			The indices shall point to clusters in the given clustering vector< vector<UInt> > for which the
			average distance between elements from @p o and @p x is to be calculated from the given @p original_dist.

			@see ClusterFunctor() Base class.
		*/
		double getAveDist_(UInt& o, UInt x, std::vector< std::vector<UInt> >& clusters, const DistanceMatrix<double>& original_dist) const;

	};

}
#endif //OPENMS_COMPARISON_CLUSTERING_AVERAGELINKAGE_H

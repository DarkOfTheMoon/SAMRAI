//
// File:	$URL: file:///usr/casc/samrai/repository/SAMRAI/tags/v-2-2-0/source/geometry/cartesian/operators/cell/CartesianCellDoubleWeightedAverage.h $
// Package:	SAMRAI geometry
// Copyright:   (c) 1997-2007 Lawrence Livermore National Security, LLC
// Revision:	$LastChangedRevision: 1704 $
// Modified:	$LastChangedDate: 2007-11-13 16:32:40 -0800 (Tue, 13 Nov 2007) $
// Description: Weighted averaging operator for cell-centered double data on 
//              a Cartesian mesh.
//

#ifndef included_geom_CartesianCellDoubleWeightedAverage
#define included_geom_CartesianCellDoubleWeightedAverage

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_hier_Patch
#include "Patch.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_String
#include <string>
#define included_String
#endif
#ifndef included_xfer_CoarsenOperator
#include "CoarsenOperator.h"
#endif

namespace SAMRAI {
    namespace geom {

/**
 * Class CartesianCellDoubleWeightedAverage implements conservative
 * cell-weighted averaging for cell-centered double patch data defined over a 
 * Cartesian mesh.  It is derived from the xfer::CoarsenOperator<DIM> base class.
 * The numerical operations for the averaging use FORTRAN numerical routines.
 *
 * The findCoarsenOperator() operator function returns true if the input 
 * variable is cell-centered double, and the string is "CONSERVATIVE_COARSEN".
 * 
 * @see xfer::CoarsenOperator
 */

template<int DIM> class CartesianCellDoubleWeightedAverage 
: public xfer::CoarsenOperator<DIM>
{
public:
   /**
    * Uninteresting default constructor.
    */
   CartesianCellDoubleWeightedAverage();

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~CartesianCellDoubleWeightedAverage<DIM>();

   /**
    * Return true if the variable and name string match cell-centered 
    * double weighted averaging; otherwise, return false.
    */
   bool findCoarsenOperator(const tbox::Pointer< hier::Variable<DIM> >& var,
                            const std::string &op_name) const; 

   /**
    * Return name string identifier of this coarsening operation.
    */
   const std::string& getOperatorName() const;

   /**
    * The priority of cell-centered double weighted averaging is 0.
    * It will be performed before any user-defined coarsen operations. 
    */
   int getOperatorPriority() const;

   /**
    * The stencil width of the weighted averaging operator is the vector of 
    * zeros.  That is, its stencil does not extend outside the fine box.
    */
   hier::IntVector<DIM> getStencilWidth() const;

   /**
    * Coarsen the source component on the fine patch to the destination
    * component on the coarse patch using the cell-centered double weighted 
    * averaging operator.  Coarsening is performed on the intersection of 
    * the destination patch and the coarse box.  It is assumed that the 
    * fine patch contains sufficient data for the stencil width of the 
    * coarsening operator.
    */
   void coarsen(hier::Patch<DIM>& coarse,
                const hier::Patch<DIM>& fine,
                const int dst_component,
                const int src_component,
                const hier::Box<DIM>& coarse_box,
                const hier::IntVector<DIM>& ratio) const;

private:
   std::string d_name_id;

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "CartesianCellDoubleWeightedAverage.C"
#endif
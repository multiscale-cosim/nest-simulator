/*
 *  topology.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TOPOLOGY_H
#define TOPOLOGY_H

// C++ includes:
#include <vector>

// Includes from nestkernel:
#include "gid_collection.h"
#include "nest_types.h"

// Includes from sli:
#include "arraydatum.h"
#include "booldatum.h"
#include "dictdatum.h"
#include "iostreamdatum.h"
#include "token.h"

// Includes from topology:
#include "layer.h"
#include "mask.h"
#include "topology_parameter.h"


namespace nest
{

/**
 * Class representing metadata for topology layer.
 */
class LayerMetadata : public GIDCollectionMetadata
{
public:
  LayerMetadata( AbstractLayerPTR );
  ~LayerMetadata()
  {
  }

  //TODO481 SetStatus, GetStatus, SetStatus must have flag
  void set_status( const DictionaryDatum&, bool ){};

  void get_status( DictionaryDatum& d ) const
  {
    layer_->get_status( d );
  }

  //! Returns pointer to object with layer representation
  const AbstractLayerPTR
  get_layer() const
  {
    return layer_;
  }

  void set_first_gid( index gid ) { first_gid_ = gid; }
  const index get_first_gid() const { return first_gid_; }

private:
  const AbstractLayerPTR layer_; //!< layer object
  index first_gid_;
};

AbstractLayerPTR get_layer( GIDCollectionPTR layer_gc );
GIDCollectionPTR create_layer( const DictionaryDatum& layer_dict );
ArrayDatum get_position( GIDCollectionPTR layer_gc );
ArrayDatum displacement( GIDCollectionPTR layer_to_gc,
  GIDCollectionPTR layer_from_gc);
ArrayDatum displacement( GIDCollectionPTR layer_gc, const ArrayDatum point );
std::vector< double > distance( GIDCollectionPTR layer_to_gc,
  GIDCollectionPTR layer_from_gc );
std::vector< double > distance( GIDCollectionPTR layer_gc, const ArrayDatum point );
MaskDatum create_mask( const DictionaryDatum& mask_dict );
BoolDatum inside( const std::vector< double >& point, const MaskDatum& mask );
MaskDatum intersect_mask( const MaskDatum& mask1, const MaskDatum& mask2 );
MaskDatum union_mask( const MaskDatum& mask1, const MaskDatum& mask2 );
MaskDatum minus_mask( const MaskDatum& mask1, const MaskDatum& mask2 );
ParameterDatum multiply_parameter( const ParameterDatum& param1,
  const ParameterDatum& param2 );
ParameterDatum divide_parameter( const ParameterDatum& param1,
  const ParameterDatum& param2 );
ParameterDatum add_parameter( const ParameterDatum& param1,
  const ParameterDatum& param2 );
ParameterDatum subtract_parameter( const ParameterDatum& param1,
  const ParameterDatum& param2 );
void connect_layers( GIDCollectionPTR source_gc,
  GIDCollectionPTR target_gc,
  const DictionaryDatum& dict );
ParameterDatum create_parameter( const DictionaryDatum& param_dict );
double get_value( const std::vector< double >& point,
  const ParameterDatum& param );
void dump_layer_nodes( GIDCollectionPTR layer_gc, OstreamDatum& out );
void dump_layer_connections( const Token& syn_model,
  GIDCollectionPTR source_layer_gc,
  GIDCollectionPTR target_layer_gc,
  OstreamDatum& out_file );
DictionaryDatum get_layer_status( GIDCollectionPTR layer_gc );
}

#endif /* TOPOLOGY_H */

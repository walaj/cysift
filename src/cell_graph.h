#ifndef CELL_GRAPH_H
#define CELL_GRAPH_H

#include "umappp/Umap.hpp"
#include "umappp/NeighborList.hpp"
#include "umappp/combine_neighbor_sets.hpp"
#include "umappp/find_ab.hpp"
#include "umappp/neighbor_similarities.hpp"
#include "umappp/optimize_layout.hpp"
#include "umappp/spectral_init.hpp"
#include "knncolle/knncolle.hpp"
#include "cysift.h"

//using Neighbors = std::vector<umappp::Neighbor<float>>;
using Neighbors    = std::vector<umappp::Neighbor<float>>;
using NeighborsInt = std::vector<std::pair<int, int>>;

class CellNode {
 public:
  CellNode() = default;

  CellNode(const std::vector<uint32_t>& ids,
	   const std::vector<uint32_t>& dist);

  CellNode(const std::vector<uint32_t>& ids,
	   const std::vector<uint32_t>& dist,
	   const std::vector<cy_uint>& flags);

  explicit CellNode(const Neighbors& neighbors) {};

  explicit CellNode(const Neighbors& neighbors,
		    const std::vector<cy_uint>& flags);
  
  void OffsetNodes(size_t offset);
  
  const Neighbors& get_neighbors() const { return neighbors_; }
  
  void set_neighbors(const Neighbors& neighbors) { neighbors_ = neighbors; }

  std::string toString() const;

  size_t size() const { return neighbors_.size(); }
  
  friend std::ostream& operator<<(std::ostream& os, const CellNode& cn);

  template<class T>
  void FillSparseFormat(std::vector<T>& ids, std::vector<T>& dist) const {
    
    ids.reserve(neighbors_.size());
    dist.reserve(neighbors_.size());
    for (const auto& n : neighbors_) {
      ids.push_back(static_cast<T>(n.first));
      dist.push_back(static_cast<T>(n.second));
    }
  }

  void FillSparseFormat(std::vector<cy_uint>& ids, std::vector<cy_uint>& dist,
			std::vector<cy_uint>& flag) const {
    
    ids.reserve(neighbors_.size());
    dist.reserve(neighbors_.size());
    flag.reserve(neighbors_.size());

    size_t i = 0;
    for (const auto& n : neighbors_) {
      ids.push_back(n.first);
      dist.push_back(n.second);
      dist.push_back(m_flags.at(i));
      i++;
    }
  }

  void sort_ascending_distance();
  
  //private:
  Neighbors neighbors_;

  // vector of flags of neighbors. Must be length 0
  // or same length as neighbors
  std::vector<cy_uint> m_flags;

  void parse_neighbors(const std::string& input_str);

};

/*
class CellGraph {
  
 public:
  CellGraph() = default;
  explicit CellGraph(const std::vector<CellNode>& nodes) : nodes_(nodes) {}
  
  const std::vector<CellNode>& get_nodes() const { return nodes_; }
  void set_nodes(const std::vector<CellNode>& nodes) { nodes_ = nodes; }
  
  void write_to_file(const std::string& filename) const;
  static CellGraph read_from_file(const std::string& filename);

  void AddNode(const CellNode& node) { nodes_.emplace_back(node); }

  using const_iterator = std::vector<CellNode>::const_iterator;
  const_iterator begin() const { return nodes_.begin(); }
  const_iterator end() const { return nodes_.end(); }

  //std::shared_ptr<StringColumn> toStringColumn() const;
  
 private:
  std::vector<CellNode> nodes_;
  
};
*/

#endif

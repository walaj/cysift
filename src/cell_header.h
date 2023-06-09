#pragma once
#include <vector>
#include <string>
#include <unordered_set>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp> 

class Tag {

 public:
  
  static const uint8_t ANY = 0;
  static const uint8_t MA_TAG = 1; // marker tag
  static const uint8_t CA_TAG = 2; // meta tag
  static const uint8_t GA_TAG = 3; // graph tag
  static const uint8_t PG_TAG = 4; // program tag  
  
  uint8_t type;
  std::string id;
  std::string data;  
  int i = -1;
  
  Tag() = default;
  
 Tag(uint8_t type, const std::string& mid, const std::string& mdata) :
   type(type), id(mid), data(mdata), i(-1) {}

  Tag(uint8_t type, const std::string& mid, const std::string& mdata, int mi) :
    type(type), id(mid), data(mdata), i(mi) {}
  
  Tag(const std::string& line);

  friend std::ostream& operator<<(std::ostream& os, const Tag& tag);

  template <class Archive>
  void serialize(Archive & ar)
  {
    ar(type, id, i, data);
  }
  
};

class CellHeader {

 public:
  
  CellHeader() = default;

  std::vector<Tag> GetDataTags() const;

  std::vector<Tag> GetInfoTags() const;
  
  std::vector<Tag> GetMarkerTags() const;

  std::vector<Tag> GetMetaTags() const;

  std::vector<Tag> GetAllTags() const { return tags; }

  size_t size() const { return tags.size(); }
  
  void SortTags();
  
  // Function to add a Tag to the header
  void addTag(const Tag& tag);

  void Print() const;

  bool validate() const;

  size_t WhichColumn(const std::string& str, uint8_t tag_type) const;

  void Cut(const std::unordered_set<size_t> to_remove);

  // overload [] operator
  Tag& operator[](std::size_t index) {
    return tags[index];
  }
  
  // overload [] operator for const objects
  const Tag& operator[](std::size_t index) const {
    return tags[index];
  }
  
  // overload at() function for const objects
  const Tag& at(std::size_t index) const {
    return tags.at(index);
  }
  
  // iterators
  std::vector<Tag>::iterator begin() {
    return tags.begin();
  }
  
  std::vector<Tag>::iterator end() {
    return tags.end();
  }
  
  // const iterators
  std::vector<Tag>::const_iterator begin() const {
    return tags.begin();
  }
  
  std::vector<Tag>::const_iterator end() const {
      return tags.end();
  }
  
  std::vector<Tag>::const_iterator cbegin() const {
    return tags.cbegin();
  }
  
  std::vector<Tag>::const_iterator cend() const {
    return tags.cend();
  }
  
  template <class Archive>
    void serialize(Archive & ar)
    {
      ar(tags);
    }
  
  std::vector<Tag> tags;
  
};


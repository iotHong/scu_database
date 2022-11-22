/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once
#include <map>
#include <memory>
#include <mutex>

#include "hash/hash_table.h"

#include <cstdlib>
#include <vector>
#include <string>



namespace scudb {

template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> {
    struct sBucket {
        sBucket(int depth) : localDepth(depth) {};
        int localDepth;
        std::map<K, V> dataMap;
        std::mutex latch;
    };

public:
  // constructor
  ExtendibleHash(size_t size);
  // helper function to generate hash addressing
  size_t HashKey(const K &key);
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key, const V &value) override;

private:
  /************************/
  std::vector<std::shared_ptr<sBucket>> mBuckets;  //buckets vector
    mutable std::mutex Latch;    //latch membership
    int GlobalDepth;       //global depth
    size_t BucketSize;     //bucket size
    int BucketNum;
};
} // namespace scudb

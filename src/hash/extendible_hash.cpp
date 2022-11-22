#include "hash/extendible_hash.h"
#include "page/page.h"
#include <list>
#include <memory>

namespace scudb {

/*
 * constructor
 * array_size: fixed array size for each bucket
 */
template <typename K, typename V>
ExtendibleHash<K, V>::ExtendibleHash(size_t size) {
        globalDepth(0);
        bucketNum(1);
        bucketMaxSize(size);
        shared_ptr<Bucket> sp1(new Bucket(0));
        this->buckets.push_back(sp1);
}

/*
 * helper function to calculate the hashing address of input key
 */
template <typename K, typename V>
size_t ExtendibleHash<K, V>::HashKey(const K &key) const{
        return std::hash<K>()(key);}
/*
 * helper function to return global depth of hash table
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>int ExtendibleHash<K, V>::GetGlobalDepth() const {
        std::lock_guard<std::mutex> lock(latch);
        return this->globalDepth;
}

/*
 * helper function to return local depth of one specific bucket
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>int ExtendibleHash<K, V>::GetLocalDepth(int bucket_id) const {
        if (size_t(bucket_id) < buckets.size()) {
            std::lock_guard<std::mutex> lck(buckets[bucket_id]->latch);
            return buckets[bucket_id]->localDepth;
        }
        return -1;
}
/*
 * helper function to return current number of bucket in hash table
 */
template <typename K, typename V>int ExtendibleHash<K, V>::GetNumBuckets() const {
        std::lock_guard<std::mutex> lock(latch);
        return this->bucketNum;
}
/*
 * lookup function to find value associate with input key
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Find(const K &key, V &value) {
        int idx = getBucketIndex(key);
        lock_guard<mutex> lck(buckets[idx]->latch);
        auto it = buckets[idx]->keyMap.find(key);
        if (it != buckets[idx]->keyMap.end()) {
            value = it->second;
            return true;
        }
        return false;
}
template <typename K, typename V>
int ExtendibleHash<K, V>::getBucketIndex(const K &key) const{
        std::lock_guard<std::mutex> lck(this->latch);
        size_t hashValue = HashKey(key);
        size_t mask = (1 << globalDepth) - 1;
        return hashValue & mask;
    }
/*
 * delete <key,value> entry in hash table
 * Shrink & Combination is not required for this project
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Remove(const K &key) {
        int idx = getBucketIndex(key);
        lock_guard<mutex> lck(buckets[idx]->latch);
        shared_ptr<Bucket> cur = buckets[idx];
        if (cur->keyMap.count(key)) {
            cur->keyMap.erase(key);
            return true;
        }
        return false;
}

/*
 * insert <key,value> entry in hash table
 * Split & Redistribute bucket when there is overflow and if necessary increase
 * global depth
 */
template <typename K, typename V>void ExtendibleHash<K, V>::Insert(const K &key, const V &value) {
        int idx = getBucketIndex(key);
        shared_ptr<Bucket> cur = buckets[idx];
        while (true) {
            stf::lock_guard<std::mutex> lck(cur->latch);
            auto it1 = cur->keyMap.find(key);
            if (it1 != cur->keyMap.end()) // key exists
            {
                it1->second = value;
                break;
            } else if (cur->keyMap.size() < bucketMaxSize) //not full
            {
                cur->keyMap[key] = value;
                break;
            } else {
                int mask = (1 << (cur->localDepth));
                cur->localDepth++;
                {
                    lock_guard<mutex> lck2(latch);
                    if (cur->localDepth > globalDepth) {
                        size_t length = buckets.size();
                        for (size_t i = 0; i < length; i++) {
                            buckets.push_back(buckets[i]);
                        }
                        globalDepth++;
                    }
                    //create a new empty bucket
                    auto newBuc = make_shared<Bucket>(cur->localDepth);
                    bucketNum++;
                    //split the full bucket
                    for (auto it = cur->keyMap.begin(); it != cur->keyMap.end(); it++) {
                        auto tmpKey = it->first;
                        auto tmpValue = it->second;
                        if (HashKey(tmpKey) & mask) {
                            newBuc->keyMap[tmpKey] = tmpValue;
                        }
                    }
                    for (auto it = cur->keyMap.begin(); it != cur->keyMap.end(); it++) {
                        auto tmpKey = it->first;
                        if (HashKey(tmpKey) & mask) {
                            it = cur->keyMap.erase(it);
                        }
                    }
                    for (size_t bucket_id = 0; bucket_id < buckets.size(); bucket_id++) {
                        if (buckets[bucket_id] == cur && (bucket_id & mask)) {
                            buckets[bucket_id] = newBuc;
                        }
                    }
                }
                idx = getBucketIndex(key);
                cur = buckets[idx];
            }
        }

    }

template class ExtendibleHash<page_id_t, Page *>;
template class ExtendibleHash<Page *, std::list<Page *>::iterator>;
// test purpose
template class ExtendibleHash<int, std::string>;
template class ExtendibleHash<int, std::list<int>::iterator>;
template class ExtendibleHash<int, int>;
} // namespace scudb

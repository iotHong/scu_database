/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace scudb {

template <typename T> LRUReplacer<T>::LRUReplacer() {
   //创建 shared ptr
   //--------------
    this->head = make_shared<Node>();//head node
    this->tail = make_shared<Node>();//tail node
    this->head->next = tail;
    this->tail->prev = head;
    //---------------
}

template <typename T> LRUReplacer<T>::~LRUReplacer() {

}

/*
 * Insert value into LRU
 */
template <typename T> void LRUReplacer<T>::Insert(const T &value) {
    //---------------------

        std::lock_guard<mutex> lck(latch);

        std::shared_ptr<Node> curPtr;//添加指针 指向value
        //页面在hash map中?
        if (hash_map.find(value) != hash_map.end()){

            curPtr = hash_map[value];
            std::shared_ptr<Node> prevPtr = curPtr->prev;
            std::shared_ptr<Node> succPtr = curPtr->next;
            // 取出map[value]，其前后节点相连
            prevPtr->next = succPtr;
            succPtr->prev = prevPtr;

        } else {
            curPtr = std::make_shared<Node>(value);
        }
        //insert
        std::shared_ptr<Node> secPtr = head->next;
        curPtr->next = secPtr;
        secPtr->prev = curPtr;
        head->next = curPtr;
        curPtr->prev = head;
        hash_map[value] = curPtr;
        return;
        //---------------------
}
/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
template <typename T> bool LRUReplacer<T>::Victim(T &value) {
    //---------------------
        std::lock_guard<mutex> lck (latch);
        if (head->next == tail){
            return false;//empty
        }
        std::shared_ptr<Node> last = tail->prev;//remove the last node
        tail->prev = last->prev;
        last->prev->next = tail;
        value = last->val;
        hash_map.erase(last->val);
        return true;
        //---------------------
}

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
    //----------------------------
        std::lock_guard<mutex> lck(latch);
        if (hash_map.find(value) != hash_map.end()){
            std::shared_ptr<Node> cur = hash_map[value];
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        bool result = hash_map.erase(value);
        return result;
        //---------------------------
}

template <typename T> size_t LRUReplacer<T>::Size() {
    //------------------------
    size_t LRUReplacer<T>::Size() {
        std::lock_guard<mutex> lck (latch);
        return hash_map.size();
    }
    //------------------------
}


template class LRUReplacer<Page *>;
// test only
template class LRUReplacer<int>;

} // namespace scudb

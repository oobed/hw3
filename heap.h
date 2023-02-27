#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T>items_;
  int m_;
  PComparator c_;
  void heapify(int idx);



};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), c_(c){
}
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){

}
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  //push back on the vector
  //trickle up
  items_.push_back(item);
  int loc = items_.size()-1;
  int parent = (loc-1)/m_;
  while(parent <= loc - 1 && c_(items_[loc], items_[parent])){
    std::swap(items_[loc], items_[parent]);
    loc = parent;
    parent = (loc-1)/m_;
  }

  
}
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return items_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return items_.size();
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("the heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap is empty");
  }
  items_[0]= items_.back();
  items_.pop_back();
  heapify(0);
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int idx){
  int smallerChild;
  int fChild = m_*idx+1;
  if(fChild < items_.size()){
    smallerChild = fChild;
    for(int i = 2; i <= m_; i++){
      int o_child = m_*idx + i;
      if(o_child < items_.size()){
        if(c_(items_[o_child], items_[smallerChild])){
        smallerChild = o_child;
      }
    }
   }
    if(c_(items_[smallerChild], items_[idx])){
      std::swap(items_[smallerChild], items_[idx]);
      heapify(smallerChild);
    }
  } 
}

#endif


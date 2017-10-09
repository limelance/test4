/* 
 * Recombines forward linked list
 * Complexity: O(n), linear
 * All operations (including cycle condition check) in cycles is O(1)
 */

#include <forward_list>
#include <iostream>


template <typename T>
class ListRecombiner 
{
private:
    std::forward_list<T> list;
public:
    ListRecombiner(std::forward_list<T> list) : list(list) {};
    ListRecombiner(int N);
    void const print_list();
    void recombine();
};

template<>
ListRecombiner<int>::ListRecombiner(int N){
    for (int i=N; i>0; i--){
        list.push_front(i);
    }
}


int main(int argc, char** argv) {
    int n;
    std::cout << "enter n <int> = ";
    std::cin >>  n;
    ListRecombiner <int> recombiner(n);
    recombiner.print_list();
    recombiner.recombine();
    recombiner.print_list();
    return 0;
}


template<typename T>
void const ListRecombiner<T>::print_list() {
    if (list.empty()) std::cout << "List is empty" << std::endl;
    else {
        typename std::forward_list<T> :: iterator it;
        for(it = list.begin(); it!= list.end(); ++it){
          std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}


template<typename T>
void ListRecombiner<T>::recombine(){
    int length = std::distance(list.begin(), list.end());
    if (length < 3) return;
    
    typename std::forward_list<T>::iterator it1, it2, itSaveP;
    itSaveP = it1 = list.begin();
    std::advance(it1, length/2);
    it2 = it1;
    
    //place second "half" part of list in front in reverse order
    for(it2++; it2!=list.end(); it2++){
        list.erase_after(it1);
        list.emplace_front(*it2);
        it2=it1;
    }
    
    //merge parts
    it2 = itSaveP;
    for(it1=list.begin(); it1!=itSaveP; it1++){
        list.emplace_after(it2, *it1);
        std::advance(it2, 2);
        list.pop_front();
    }
}

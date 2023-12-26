#pragma once
#include "document.h"
#include <algorithm>
#include <string>
#include <vector>
using std::vector, std::string;

template <typename Iterator>
class IteratorRange{
    Iterator iter_begin_;
    Iterator iter_end_;
  public:
    IteratorRange(Iterator It1,Iterator it2):iter_begin_(It1),iter_end_(it2){};
    Iterator begin() const{
    return iter_begin_;
    };
    Iterator end() const{
    return iter_end_;
    };
    int size() const{
    return static_cast<int>(iter_begin_-iter_end_);
    };
    
};

template <typename Iterator>
class Paginator {
    vector<IteratorRange<Iterator>> iterat_;
public:
    Paginator (Iterator it_start,Iterator it_end,size_t page_size){
        int num=static_cast<int>(distance(it_start, it_end));
        Iterator it_intermediate=it_start;
        advance( it_intermediate, page_size);
        for(int i=1;i<=num/static_cast<int>(page_size);i++){
                iterat_.push_back(IteratorRange(it_start,it_intermediate));
                it_start=it_intermediate;
                advance( it_intermediate, page_size );/////////////////////////
            }        
        if(num%page_size!=0){
            iterat_.push_back(IteratorRange(it_start,it_end));
        }          
    }
    
    auto begin() const{
    return iterat_.begin();
    }
    
    auto end()const{
    return iterat_.end();
    }
}; 

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}


std::ostream& operator<<(std::ostream& os,const Document& Doc){
    os<<"{ document_id = "<<Doc.id<<", relevance = "<<Doc.relevance<<", rating = "<<Doc.rating<<" }";   
    return os;
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& os,const IteratorRange<Iterator>& ItRange){
    for (auto iter=ItRange.begin();iter!=ItRange.end();iter++){
        os<<*iter;
    }   
    return os;
}
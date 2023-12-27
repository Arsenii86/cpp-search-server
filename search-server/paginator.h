#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>


template <typename Iterator>
class IteratorRange{
    Iterator iter_begin_;
    Iterator iter_end_;
  public:
    IteratorRange( Iterator it1,Iterator it2 ):iter_begin_( it1 ),iter_end_( it2 ){};
    Iterator Begin() const{
    	return iter_begin_;
    };
    Iterator End() const{
    	return iter_end_;
    };
    int Size() const{
    	return static_cast<int>( iter_begin_-iter_end_ );
    };
    
};

template <typename Iterator>
class Paginator {
    std::vector<IteratorRange<Iterator>> iterat_;
public:
    Paginator ( Iterator it_start,Iterator it_end,size_t page_size ){
        int num=static_cast<int>( distance( it_start, it_end ));
        Iterator it_intermediate=it_start;
        advance( it_intermediate, page_size );
        for(int i=1;i<=num/static_cast<int>( page_size );i++){
                iterat_.push_back( IteratorRange( it_start,it_intermediate ));
                it_start=it_intermediate;
                advance( it_intermediate, page_size );
            }        
        if( num%page_size!=0 ){
            iterat_.push_back( IteratorRange( it_start,it_end ));
        }          
    }
    
    auto Begin() const{
    	return iterat_.begin();
    }
    
    auto End()const{
    	return iterat_.end();
    }
}; 

template <typename Container>
auto Paginate( const Container& c, size_t page_size ) {
    return Paginator( begin(c), end(c), page_size);
}


template <typename Iterator>
std::ostream& operator<<( std::ostream& os, const IteratorRange<Iterator>& ItRange ){
    for (auto iter=ItRange.begin(); iter!=ItRange.end(); iter++){
        os<<*iter;
    }   
    return os;
}
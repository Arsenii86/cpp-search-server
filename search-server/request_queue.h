#pragma once
#include "search_server.h"
#include <algorithm>
#include <string>
#include <deque>
#include <vector>
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest( const std::string& raw_query, DocumentPredicate document_predicate );
    
    std::vector<Document> AddFindRequest( const std::string& raw_query, DocumentStatus status );

    std::vector<Document> AddFindRequest( const std::string& raw_query ); 

    int GetNoResultRequests() const ;

private:

    const SearchServer& search_server_;
    struct QueryResult {
        std::string Query;
        int num_result; 
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int curent_minutes_=0;
}; 

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest( const std::string& raw_query, DocumentPredicate document_predicate ) {
        // напишите реализацию
        ++curent_minutes_;
        if (curent_minutes_>min_in_day_){
            requests_.erase(requests_.begin());
            --curent_minutes_;            
        }        
        const auto matched_documents = search_server_.FindTopDocuments( raw_query, document_predicate );
        requests_.push_back({ raw_query, static_cast<int>(matched_documents.size()) });
        return matched_documents;
    }



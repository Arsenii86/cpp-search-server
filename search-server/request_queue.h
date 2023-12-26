#pragma once
#include "search_server.h"
#include <algorithm>
#include <string>
#include <deque>
#include <vector>
#include "document.h"
using std::vector, std::string,std::deque;

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        ++curent_minutes_;
        if (curent_minutes_>min_in_day_){
            requests_.erase(requests_.begin());
            --curent_minutes_;            
        }        
        vector<Document> matched_documents = search_server_.FindTopDocuments(raw_query,document_predicate);
        requests_.push_back(QueryResult (raw_query,matched_documents));
        return matched_documents;
    }

    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status);

    vector<Document> AddFindRequest(const string& raw_query); 

    int GetNoResultRequests() const ;

private:

    const SearchServer& search_server_;
    struct QueryResult {
        string Query;
        vector<Document> matched_documents; 
        QueryResult (const string& query,const vector<Document>& search_result);
    };
    deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int curent_minutes_=0;
}; 

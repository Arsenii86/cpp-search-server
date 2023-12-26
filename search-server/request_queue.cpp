#include "request_queue.h"
using namespace std;
    RequestQueue::RequestQueue(const SearchServer& search_server):search_server_(search_server) {}
    
   

    vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
        return AddFindRequest(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
                return document_status == status;
            });
    }

    vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
        return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
    }


    int RequestQueue::GetNoResultRequests() const {
        int NoResult=0;
        for (const auto& request:requests_){
            if (request.matched_documents.empty()){
            ++NoResult;
            }
        }
     return NoResult;   
    }

 RequestQueue::QueryResult::QueryResult (const string& query,const vector<Document>& search_result): Query(query),matched_documents(search_result){}
   

#include "document.h"
using namespace std;
    Document::Document( int id, double relevance, int rating )
        : id(id)
        , relevance(relevance)
        , rating(rating) {
    }

ostream& operator<<( ostream& os, const Document& doc ){
    os<<"{ document_id = "<<doc.id<<", relevance = "
	<<doc.relevance<<", rating = "<<doc.rating<<" }";   
    return os;
}
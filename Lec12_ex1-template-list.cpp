#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// template <class T> class TList;

template <class T>
class TNode {
  friend class TList<T>;
  private:
    T value; // data stored in node
    TNode * next; // points to the next node
  public:
    TNode() : next(NULL) {} // next point is NULL
    TNode( const T & val ){
      value = val;
      next = NULL;
    }
    TNode<T> * getNext() const{
      return next;
    }
    template <class X> friend ostream & operator <<(ostream &, const TNode<X> & node){
      os << node.value << "->";
      return os;
    }
};




template <class T> class TList {
    TNode<T> * head; // dummy head node
    TNode<T> * tail; // dummy tail node
    TNode<T> * current; // current position
  public:
    TList(){  
      head = new TNode<T>;
      tail = new TNode<T>;
      head->next = tail;
      tail->next = head;
      current = head;
    }

    ~TList(){  
      clear();
      delete head;
      delete tail;
    }

    int advance();  // Return 0 if current is already at the end of the list; 
    //otherwise, current will point to the next node and return 1.
    void append( const T & nodeVal );  // Add a new node to the end of the list
    void clear() // Remove all nodes.
    {
      current = head;
      while(current->next != tail){
        head -> next = current -> next;
        delete current;
        curren = head -> next
      }

    }
    T get() const;  // Get the data at the current position.
    void goLast();  // Set current to the last node in the list.
    void goTop();	  // Set current to the head node.
    void insertAfter( const T & nodeVal ); // Insert new node after current one.

    int isEmpty() const{
      return head->next == tail; 
      // Return 1 if the list is empty; otherwise,return 0.
    } 

    void prepend( const T & nodeVal );
    // Insert a node at the beginning of the list.
    void replace( const T & newVal );
    // Replace the data in the current node.
    template <class X> friend ostream & operator <<(ostream & os, const TList<X> & list);
};
 

template <class T> void TList<T>::clear() {  
  current = head->next;
  while( current != tail ) {	 
    head->next = current->next;
    delete current;
    current = head->next;
  }
  current = head;
  head->next = tail;
}

template <class T> int TList<T>::advance() {
  if( !current ) abort();
  if( current->next != tail ) { 
    current = current->next;
     return 1;  
  }
  return 0;
}

template <class T> void TList<T>::goLast() {  
  if (!current) abort();
  while (current->next != tail)
	current = current->next;
}

template <class T> void TList<T>::goTop() {  
  current = head;
}

template <class T> T TList<T>::get() const {  
  if (!current) abort();
  return current->value;
}

template <class T> void TList<T>::replace (const T & newVal) {  
  if( !current ) abort();
  current->value = newVal;
}

template <class T> void TList<T>::insertAfter (const T & nodeVal) {  
  if (!current) abort();
  TNode<T> * p = new TNode<T>( nodeVal );
  p->next = current->next;
  current->next = p;
  current = p;
}

template <class T> void TList<T>::append (const T & nodeVal) { 
  goLast();
  insertAfter( nodeVal );
}

template <class T> void TList<T>::prepend (const T & nodeVal) {  
  goTop();
  insertAfter( nodeVal );
}

template <class T> 
ostream & operator <<( ostream & os, const TList<T> & list) {  
  if (list.isEmpty()) return os;
  TNode<T> * p = list.head->getNext();
  while( p != list.tail ) {	
    os << *p;
    p = p->getNext();  
  }
  os << endl;
  return os;
}

void createRandomScores() {
  TList<int> scores;
  cout << "Creating a random list of scores: \n";
  for (int i = 0; i < 10; i++) {
    int n = rand() % 100;
    scores.append(n);
  }
  
  cout << scores << endl;
  
  scores.goLast();
  cout << "Last item: " << scores.get() << endl;
  scores.goTop();
  scores.advance();
  cout << "First item: " << scores.get() << endl;
  cout << "\nReplacing first node with value 101...\n";
  scores.replace( 101 );
  cout << scores;
  cout << "\nClearing the list..." ;
  scores.clear();
  if (scores.isEmpty())
  cout << "the list is now empty.\n\n";
  
}

void createNameList() {
  TList<string> names;
  names.append( "Nam" );
  names.append( "Huy" );
  names.append( "Kh�nh" );
  names.append( "Ngoc" );
  names.append( "Son" );
  names.append( "Hung" );
  names.append( "Thao" );
  names.append( "Thuy" );
  names.append( "Bao Tran" );
  names.append( "Mai Trinh" );
  names.append( "Nhat Nam" );
  names.append( "Tuan" );
  names.append( "Nga" );

  cout << "current: " << names.get() << endl;
  cout << names;
  names.goTop();
  names.advance();
  names.replace( "To Nguyen Minh Nhat" );
  names.goLast();
  names.insertAfter( "Cong" );
  names.prepend( "Cao Minh Tuan" );
  cout << names << endl;
  cout << "Clearing the list...";
  names.clear();
  if (names.isEmpty())
    cout << "the list is now empty\n\n";
			    
}


int main() {
  createRandomScores();
  createNameList();
  return 0;
} // Lec12_ex1-template-list.cpp

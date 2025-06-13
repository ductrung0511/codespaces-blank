#include <iostream>
using namespace std;


template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& value): data(value), next(nullptr) {}
};

template <typename T>
class LinkList {
    private:
        Node<T> *head;
    public:
        LinkList() : head(nullptr) {

            // Constructor implementation
        }

        ~LinkList() {
            // Destructor implementation
            Node<T>* current = head;
            while (current) {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }

        // Insert at the end
        void Insert(T value) {
            Node<T>* newNode = new Node<T>(value);
            if (!head) {
                head = newNode;
            } else {
                Node<T>* current = head;
                while (current->next)
                    current = current->next;
                current->next = newNode;
            }
        }
        void Prepend(T value){
            if (!head){
                head = new Node<T>(value);
            } else {
                Node<T>* newNode = new Node<T>(value);
                newNode->next = head;
                head = newNode;
            }
        }
        // void Prepend(T value) {
        //     Node<T>* newNode = new Node<T>(value);
        //     newNode->next = head;  // works even if head is nullptr
        //     head = newNode;
        // }
        void RemoveHead(){
            if (!head) return; // List is empty
            Node<T>* temp = head;
            head  = head -> next;
            delete temp;
        }
    //    void RemoveTail(){
    //         if (!head) return; // List is empty
    //         Node<T>* current = head;
    //         while(current->next){
    //             if (!current->next->next) { // If next is the last node
    //                 delete current->next; // Delete the last node
    //                 current->next = nullptr; // Set the second last node's next to nullptr
    //                 return;
    //             }
    //             current = current->next; // Move to the next node
    //         }
    //         delete head; // If there's only one node, delete it
    //     }
        void RemoveTail() {
            if (!head) return; // List is empty

            if (!head->next) { // Only one node
                delete head;
                head = nullptr;
                return;
            }

            Node<T>* current = head;
            while (current->next && current->next->next) {
                current = current->next;
            }

            delete current->next;        // Delete the last node
            current->next = nullptr;     // Update second last node's next to null
        }


        // Delete a value
        void Delete(T value) {
            if (!head) return;

            if (head->data == value) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                return;
            }

            Node<T>* current = head;
            while (current->next && current->next->data != value)
                current = current->next;

            if (current->next) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
        }

        // Search for a value
        bool Search(T value) {
            Node<T>* current = head;
            while (current) {
                if (current->data == value)
                    return true;
                current = current->next;
            }
            return false;
        }


        void Print() const {
            Node<T>* current = head;
            while(current){
                cout << current->data << " ";
                current = current->next;
            }
            cout << "|end" << endl;
            // Display the contents of the linked list
        }

};

int main() {
    LinkList<string> list;
    list.Insert("Hello");
    list.Insert("World");
    list.Insert("!");
    list.Print(); // Output: Hello World ! |end
    list.Delete("World");
    cout << "Searching for 'World': " << (list.Search("World") ? "Found" : "Not Found") << endl; // Output: Found
    
    return 0;
}
//
//  Node.h
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//

#ifndef Node_h
#define Node_h

template<typename T>
class Node
{
    private:
        T* data;
        Node* left;
        Node* right;
    public:
        Node();
        Node(const Node<T>& obj);
        Node(T term);
        Node* GetLeft() {return left;}
        Node* GetRight() {return right;}
        T* GetData() {return data;}
        void SetData(const T& obj);
        void SetRight(Node<T>* ptr) {this->left = ptr;}
        void SetLeft(Node<T>* ptr) {this->right = ptr;}

        //------Overloaded Operators-----//
        Node& operator=(const Node& obj);
};

template <typename T>
Node<T>::Node(const Node<T>& obj)
{
    delete data;
    data = new T();
    data = *(obj.data);
}

template <typename T>
Node<T>::Node(T term)
{
    this->data = &term;
}

template <typename T>
void Node<T>::SetData(const T& obj)
{
    *data = obj;
}

//-------Overloaded Operators---------//
template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& obj)
{
    if(this != obj)
    {
        delete data;
        data = new T();
        data = *(obj.data);
    }
    return *this;
}

#endif /* Node_h */


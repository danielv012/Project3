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
        Node(const Node<T>& obj)
        {
            delete data;
            data = new T();
            *T = *(obj.data);
        }
        Node* GetLeft() {return left;}
        Node* GetRight() {return right;}
        T* GetData() {return data;}
        void SetData(const T& obj)
        {
            *data = obj;
        }

        //------Overloaded Operators-----//
        Node& operator=(const Node& obj)
        {
            if(this != obj)
            {
                delete data;
                data = new T();
                *T = *(obj.data);
            }
            return *this;
        }
};

#endif /* Node_h */

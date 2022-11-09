//
//  BinTree.h
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//

#ifndef BinTree_h
#define BinTree_h
#include "Node.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

template<typename T>
class BinTree
{
    private:
        Node<T>* root;

        //Recursive helpers
        void InsertRecursive(Node<T>* parent, Node<T>* key);
        Node<T>* SearchRecursive(Node<T>* node, T &key);
        Node<T>* RemoveRecursive(Node<T>* root, Node<T>* parent, Node<T>* node);
        Node<T>* GetParentRecursive(Node<T>* child);

        Node<T>* LeftmostNode(Node<T>* node);
        Node<T>* GetParent(Node<T>* child)
        {
            return GetParentRecursive(root, child);
        }
        
    public:
        //----------Constructors------//
        BinTree()
        {
            root = nullptr;
        }

        //----------Manipulators-------//
        void Insert(Node<T>* node)
        {
            if(root == nullptr) root = node;
            else InsertRecursive(root, node);
        }
        Node<T>* Search(T &key)
        {
            return SearchRecursive(root, key);
        }
        bool Remove(T &key) 
        { 
            Node<T>* node = Search(key);
            Node<T>* parent = GetParent(node);
            return RemoveRecursive(root, parent, node); 
        }

        //-----------Miscellaneous-------//
        Node<T>* GetLeftmost()
        {
            return LeftmostNode(this->root);
        }

        //-----------Output--------//
        void Print()
        {
            PrintRecursive(this->root);
        }
        void PrintRecursive(Node<T>* node);

        double Evaluate(int num)
        {
            return EvaluateRecursive(this->root, num);
        }
        double EvaluateRecursive(Node<T>* node, int num);
};

template<typename T>
Node<T>* BinTree<T>::SearchRecursive(Node<T>* node, T &key)
{
    if(node != nullptr)
    {
        if(key == node->key) return node;
        else if (key < node->key) return SearchRecursive(node->GetLeft, key);
        else return SearchRecursive(node->GetRight, key);
    }
    return nullptr;
}

template<typename T>
void BinTree<T>::InsertRecursive(Node<T>* parent, Node<T>* key)
{
    if(*(key->GetData()) > *(parent->GetData()))
    {
        if(parent->GetLeft() == nullptr) parent->SetLeft(key);
        else InsertRecursive(parent->GetLeft(), key);
    }
    else if(*(key->GetData()) == *(parent->GetData()))
    {
        double oldCoeff = parent->GetData()->GetCoeff();
        parent->GetData()->SetCoeff(parent->GetData()->GetCoeff() + key->GetData()->GetCoeff());
        double multiplier = parent->GetData()->GetCoeff() / oldCoeff;
        string oldNumerator = parent->GetData()->GetCoeffStr().substr(1,  parent->GetData()->GetCoeffStr().find('/') - 1);
        int oldNum = stoi(oldNumerator);
        parent->GetData()->SetCoeffStr(parent->GetData()->GetCoeffStr().replace(((parent->GetData()->GetCoeffStr()).find(oldNumerator)),  oldNumerator.length(), to_string((int)(oldNum*multiplier))));
    }
    else
    {
        if(parent->GetRight() == nullptr) parent->SetRight(key);
        else InsertRecursive(parent->GetRight(), key);
    }
}

template<typename T>
Node<T>* BinTree<T>::LeftmostNode(Node<T>* node)
{
    Node<T>* curr = node;
    while(curr && curr->GetLeft() != NULL) curr = curr->GetLeft();
    return curr;
}
template<typename T>
Node<T>* GetParentRecursive(Node<T>* root, Node<T>* node)
{
    if(root == nullptr) return nullptr;

    if(root->GetLeft() == node || root->GetRight() == node) return root;

    if(node->GetData() < root->GetData()) return GetParentRecursive(root->GetLeft(), node);

    return GetParentRecursive(node->GetRight(), node);
}

template<typename T>
Node<T>* BinTree<T>::RemoveRecursive(Node<T>* root, Node<T>* parent, Node<T>* node)
{
    //base
    if(root == NULL) return false;

    //internal node with 2 children
    if(node->left != nullptr && node->right != nullptr)
    {
        Node<T>* succNode, succParent;
        succNode = node->right;
        succParent = node;
        while(succNode->left != nullptr)
        {
            succParent = succNode;
            succNode = succNode->left;
        }

        // Copy the value from the successor node
        *node = *succNode;

        //Recurisvely remove successor
        RemoveRecursive(root, succParent, succNode);
    }

    //root node (with 1 or 0 children)
    else if(node == root)
    {
        if(node->left != nullptr) root = node->left;
        else root = node->right;
    }
    
    //internal node with left child
    else if(node->left != nullptr)
    {
        //replace node with left child of node
        if(parent->left == node) parent->left = node->left;
        else parent->right = node->left;
    }

    //internal with right child only or leaf
    else
    {
        //rplace node with node's right child
        if(parent->left == node) parent->left = node->right;
        else parent->right = node->right;
    }

    return true;
}

template <typename T>
void BinTree<T>::PrintRecursive(Node<T>* node) 
{
  if (node == nullptr) return;          

  PrintRecursive(node->GetLeft());

  //------Printing------//
  T term = *(node->GetData()); 
  if(term.IsFirst())
  {
    if(term.GetCoeff() < 0)
    {
        if(fmod(term.GetCoeff(),1) != 0)
        {
            cout << term.GetCoeffStr()[0] << "-" << term.GetCoeffStr().substr(1);
        }
        else 
        {
            cout << "-";
            cout << ((term.GetCoeffStr() == "1" || term.GetCoeffStr() == "0") ? "" : term.GetCoeffStr());
        }
    }
    else
    {
        cout << ((term.GetCoeffStr() == "1" || term.GetCoeffStr() == "0") ? "" : term.GetCoeffStr());
    }
    
    cout << (term.GetCoeffStr() == "0" ? "" : "x");
    cout << (term.GetExpon() > 1 || term.GetExpon() < 0 ? "^" : "") << term.GetExponStr();
  }
  else
  {
    cout << " ";
    if(term.GetCoeff() < 0)
    {
        cout << "- ";
        term.SetCoeffStr(term.GetCoeffStr());
    }
    else cout << "+ ";
    cout << ((term.GetCoeffStr()== "1" || term.GetCoeffStr() == "0") ? "" : term.GetCoeffStr())
     << (term.GetCoeffStr() == "0" ? "" : "x") << (term.GetExpon() > 1 || term.GetExpon() < 0 ? "^" : "") << (term.GetExpon() > 1 || term.GetExpon() < 0 ? term.GetExponStr() : "");
  }
  //---------------------//

  PrintRecursive(node->GetRight()); 
}

template <typename T>
double BinTree<T>::EvaluateRecursive(Node<T>* node, int num) 
{
    double sum = 0;
  if (node == nullptr) return 0;       

  sum += EvaluateRecursive(node->GetLeft(), num);

  //------Adding------//
    T term = *(node->GetData());
    sum += (pow(num, term.GetExpon()) * term.GetCoeff());
  //------------------//

  sum += EvaluateRecursive(node->GetRight(), num); 

  return sum;
}

#endif /* BinTree_h */


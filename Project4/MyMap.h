//
//  MyMap.cpp
//  Project 4
//
//  Created by Akshara Sundararajan on 3/9/17.
//  Copyright © 2017 Akshara Sundararajan. All rights reserved.
//


#ifndef MyMap_h
#define MyMap_h
//fix the architecture issue
// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap() //constructor
    {
        root = nullptr; //root->left =nullptr; root->right = nullptr;
        m_size = 0;
    }
    ~MyMap() //destructor
    {
        clear();
    }
    void clear() //deletes all nodes
    {
        clearFromNode(root);
    }
    int size() const //returns size
    {
        return m_size;
    }
    //	The	associate	method	associates	one	item	(key)	with	another	(value).
    //	If	no	association	currently	exists	with	that	key,	this	method	inserts
    //	a	new	association	into	the	tree	with	that	key/value	pair.		If	there	is
    //	already	an	association	with	that	key	in	the	tree,	then	the	item
    //	associated	with	that	key	is	replaced	by	the	second	parameter	(value).
    //	Thus,	the	tree	contains	no	duplicate	keys.
    void associate(const KeyType& key, const ValueType& value)
    {
        if(root==nullptr)
        {
            root= new Node;
            root->m_key = key; root->m_value = value;
            root->right=nullptr;
            root->left=nullptr;
            m_size++;
        }
        else{
            Node *ptr = root;
            for(;;)
            {
                if(ptr->m_key==key)
                {
                    ptr->m_value = value;
                    return;
                }
                else if(key<ptr->m_key)
                {
                    if(ptr->left!=nullptr)
                        ptr=ptr->left;
                    else{
                        ptr->left = new Node;
                        ptr->left->m_value = value;
                        ptr->left->m_key = key;
                        ptr->left->right=nullptr;
                        ptr->left->left = nullptr;
                        m_size++;
                        return;
                    }
                }
                else{
                    if(ptr->right!=nullptr)
                        ptr=ptr->right;
                    else{
                        ptr->right = new Node;
                        ptr->right->m_value = value;
                        ptr->right->m_key = key;
                        ptr->right->right=nullptr;
                        ptr->right->left = nullptr;
                        m_size++;
                        return;
                    }
                }
            }
        }
    }
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const
    {
        if(root != nullptr)
        {
            Node *ptr = root;
            while(ptr!=nullptr)
                  {
                      if(ptr->m_key == key)
                          return &ptr->m_value;
                      else if(key<ptr->m_key)
                          ptr=ptr->left;
                      else
                          ptr=ptr->right;
                  }
        }
        return nullptr;
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node{
        KeyType m_key;
        ValueType m_value;
       /* bool operator<(const Node &n)
        {
            if(m_value!=n.m_value)
            return m_value<n.m_value;
            else
                return m_key<n.m_key;
            
        }
        bool operator>(const Node &n)
        {
            if(m_value!=n.m_value)
                return m_value>n.m_value;
            else
                return m_key>n.m_key;
            
        }
        bool operator==(const Node &n)
        {
            
            return m_value==n.m_value;
            
        }*/
        Node *left, *right;
    };
    Node *root;
    int m_size;
    void clearFromNode(Node *ptr) //recursive function to delete all nodes of binary tree
    {
        if(ptr == nullptr)return;
        else{
            clearFromNode(ptr->left);
            clearFromNode(ptr->right);
            delete ptr;
            m_size--;
        }
    }
};
#endif /* MyMap_h */

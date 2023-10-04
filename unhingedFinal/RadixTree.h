#ifndef RadixTree_h
#define RadixTree_h
#include <vector>
#include <iostream>
#include <algorithm>
template <typename ValueType>
class RadixTree {
private:
struct RadixT{
    bool isEnd=false;
    RadixT* arr[128];
    std::string child_s[128];
    ValueType* m_val;
    RadixT(){
        for(int i=0; i<128; i++){
           arr[i]=nullptr;
        }
        m_val=nullptr;
    }
};
RadixT* root=new RadixT;
void cleanup(RadixT* root2);
void partialRadixInsert(RadixT* root, std::string s, const ValueType& v);
ValueType* lookUp(RadixT* root, std::string key) const;
    
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
};
 
template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
}

template <typename ValueType>
void RadixTree<ValueType>::cleanup(RadixT* root2){
    for(int i=0; i<128; i++){
        //iterate through all pointers and delete them if they are not null
        if(root2->arr[i]!=nullptr){
            cleanup(root2->arr[i]);
            delete root2->arr[i];
        }
    }
    //delete the root at the end 
    if(root2==root){
        delete root2;
    }
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
    cleanup(root);
}
 
template <typename ValueType>
void RadixTree<ValueType>::partialRadixInsert(RadixT* root, std::string s, const ValueType& value){
    //if s is empty set the indicationg bool marker to true and add a new a new value
    if(s.empty()){
        root->isEnd=true;
        delete root->m_val;
        root->m_val=new ValueType(value);
        return;
    }
    //creates a new RadixT at the provided index
    int cur_char=s[0]-1;
    if(root->arr[cur_char]==nullptr){
        root->arr[cur_char]=new RadixT;
        root->child_s[cur_char]=s;
        partialRadixInsert(root->arr[cur_char], "", value);
        return;
    }
    
    std::string transition=root->child_s[cur_char];
    int match_len=0;
    while(match_len < std::min(transition.length(), s.length()) && transition[match_len]==s[match_len]){
        ++match_len;
    }
    //recursively insert the substrings from the array if the lengths match
        if(match_len==transition.length()){
            partialRadixInsert(root->arr[cur_char], s.substr(match_len), value);
        }
    //create a new RadixT taking in regards to match_len
        else if(match_len==s.length()){
            RadixT* newnode=new RadixT;
            newnode->arr[transition[match_len]-1]=root->arr[cur_char];
            newnode->child_s[transition[match_len]-1]=transition.substr(match_len);
            root->arr[cur_char]=newnode;
            root->child_s[cur_char]=s;
            partialRadixInsert(root->arr[cur_char], "", value);
        }
    //if none of the match_len does not match up with s's or transition's length  then create a new radix tree 
        else{
            RadixT* newnode=new RadixT;
            newnode->arr[transition[match_len]-1]=root->arr[cur_char];
            newnode->child_s[transition[match_len]-1]=transition.substr(match_len);
            root->arr[cur_char]=newnode;
            root->child_s[cur_char]=s.substr(0, match_len);
            partialRadixInsert(root->arr[cur_char], s.substr(match_len), value);
        }
    
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::lookUp(RadixT* root, std::string key) const{
    if(key.empty()){
        return (root->isEnd) ? root->m_val : nullptr;
    }
    //if the the address at the cur_char leads to nullptr, it means that there is nothing stored there
    int cur_char=key[0]-1;
    if(root->arr[cur_char]==nullptr){
        return nullptr;
    }
    std::string transition=root->child_s[cur_char];
    int len=std::min(transition.length(), key.length());
    if(transition.substr(0,len)!=key.substr(0,len)){
        return nullptr;
    }
    //since the lengths are equal, recusrsively search for the key 
    if(transition.length()==len){
        return lookUp(root->arr[cur_char], key.substr(transition.length()));
    }
    else{
            return nullptr;
    }
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
    partialRadixInsert(root, key, value);
}
 
template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const{
    ValueType* res=lookUp(root, key);
    return res;
}
 
#endif /* RadixTree_h */
 

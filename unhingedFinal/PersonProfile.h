#ifndef PersonProfile_h
#define PersonProfile_h
#include <iostream>
#include "provided.h"
#include <unordered_set> 
#include <vector>
#include <algorithm>
#include <string>
#include "RadixTree.h"

class PersonProfile{
private:
    std::string m_name;
    std::string m_email;
    std::vector<AttValPair> m_av_vect;
    RadixTree<std::unordered_set<std::string>>m_radTree;
    
public:
PersonProfile(std::string name, std::string email);
~PersonProfile();
std::string GetName() const;
std::string GetEmail() const;
void AddAttValPair(const AttValPair& attval);
int GetNumAttValPairs() const;
bool GetAttVal(int attribute_num, AttValPair& attval) const;
};
#endif /* PersonProfile_h */

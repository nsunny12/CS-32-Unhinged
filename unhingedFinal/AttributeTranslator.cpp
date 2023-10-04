#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
AttributeTranslator::AttributeTranslator(){
    
}
AttributeTranslator::~AttributeTranslator(){
    
}

bool AttributeTranslator::Load(std::string filename){
    std::ifstream infile(filename);
    if(!infile){
        return false;
    }
    std::string line;
    while(std::getline(infile,line)){
        std::istringstream iss(line);
        std::string attribute;
        std::string value;
        std::string compatible_attribute;
        std::string compatible_value;
        
        if(!getline(iss, attribute, ',')){
            return false;
        }
        if(!getline(iss, value, ',')){
            return false;
        }
        if(!getline(iss, compatible_attribute, ',')){
            return false;
        }
        if(!getline(iss, compatible_value, ',')){
            return false;
        }
        std::string pair=attribute + "," + value;
        AttValPair a1(compatible_attribute,compatible_value);
        //checks if the string pair is already in the radix tree or not 
        if(m_radTree.search(pair)!=nullptr){
            long int match=std::count((*m_radTree.search(pair)).begin(), (*m_radTree.search(pair)).end(), a1);
            if(match==0){
                (*m_radTree.search(pair)).push_back(a1);
            }
        }
        else{
            std::vector<AttValPair> unique_values;
            unique_values.push_back(a1);
            m_radTree.insert(pair, unique_values);
            m_vect.push_back(a1);
        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    std::string pair=source.attribute + "," + source.value;
    if((m_radTree.search(pair))!=nullptr){
        return (*m_radTree.search(pair));
    }
    std::vector<AttValPair> empty;
    return empty;
}

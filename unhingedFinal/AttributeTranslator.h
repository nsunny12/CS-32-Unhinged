#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include <iostream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator{
    public:
        AttributeTranslator();
        ~AttributeTranslator();
        bool Load(std::string filename);
        std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    private:
        std::vector<AttValPair>m_vect;
        RadixTree <std::vector<AttValPair>> m_radTree;
};
#endif /* AttributeTranslator_h */

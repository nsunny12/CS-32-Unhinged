#ifndef MatchMaker_hpp
#define MatchMaker_hpp
#include <iostream>
#include <algorithm>
#include <vector>
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include <unordered_map>
#include <unordered_set>

class AttributeTranslator;
class MemberDatabase;

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
    
private:
    const MemberDatabase* m_mdb;
    const AttributeTranslator* m_at;
};
#endif /* MatchMaker_h */

bool operator<(const AttValPair& rhs, const AttValPair& lhs);
bool operator<(const EmailCount& rhs, const EmailCount& lhs);

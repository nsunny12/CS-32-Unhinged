#ifndef MemberDatabase_h
#define MemberDatabase_h
#include <stdio.h>
#include <iostream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

class MemberDatabase{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree <std::vector<std::string>> m_radTree_avp_t_email;
    RadixTree <PersonProfile> m_radTree_email_t_pp;
};
#endif /* MemberDatabase_h */


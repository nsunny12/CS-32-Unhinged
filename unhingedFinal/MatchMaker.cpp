#include "MatchMaker.h"
#include <set>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at){
    m_mdb=&mdb;
    m_at=&at;
}

MatchMaker::~MatchMaker(){
    
}

bool operator<(const AttValPair& rhs, const AttValPair& lhs){
return lhs.value < rhs.value;
}

bool operator<(const EmailCount& rhs, const EmailCount& lhs){
    if(lhs.count==rhs.count){
        return lhs.email > rhs.email;
    }
    return lhs.count < rhs.count;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    std::vector<EmailCount> m_email_vect;
    std::vector<AttValPair> m_s;
    std::vector<std::vector<AttValPair>> bigSetAV;
    std::unordered_map<std::string, int> m_map;
    const PersonProfile* p=&(*m_mdb->GetMemberByEmail(email));
    AttValPair av;
    
    //for the total number of attribute-pairs
    int x=0;
    while(x< p->GetNumAttValPairs()){
        p->GetAttVal(x,av);
        //m_s gets all of the compatible attval pairs associated with av
        m_s=m_at->FindCompatibleAttValPairs(av);
        //bigSetAv contains all the vectors of compatible attval pairs
        bigSetAV.push_back(m_s);
        x++;
    }
    
    std::vector<AttValPair> temp;
    for(std::vector<std::vector<AttValPair>>::iterator ittt=bigSetAV.begin(); ittt!=bigSetAV.end(); ittt++){
        //unpacking all of the vectors in bigSetAv and inputting the contents into temp
        temp.insert(temp.end(), (*ittt).begin(), (*ittt).end());
    }
    
    //insert all of the compatible attvalpairs into a set to eliminate duplicates
    std::set<AttValPair> avp_set;
    for(int i=0; i<temp.size(); i++){
        avp_set.insert(temp[i]);
    }

    std::vector<std::string> m_set_email;
    std::vector<std::string> t;
    for(std::set<AttValPair>::iterator it=avp_set.begin(); it!=avp_set.end(); it++){
        AttValPair a=(*it);
        t=m_mdb->FindMatchingMembers(a);
        //unpacking all of the vectors of emails and inputting the contents into m_set_email
        m_set_email.insert(m_set_email.end(), t.begin(), t.end());
    }

    //iterates through the large vector of emails, and for each duplicate email increase the associated count by one
    std::unordered_map<std::string,int>::iterator it2= m_map.begin();
    for(int i=0; i<m_set_email.size(); i++){
        std::string temail=m_set_email[i];
        if(temail!=p->GetEmail()){
            it2=m_map.find(temail);
            if(it2!=m_map.end()){
                it2->second=(it2->second)+1;
            }
            else{
                m_map.insert({temail,1});
            }

        }
    }
    
    //converts the contents ot the map into a vector of EmailCount objects
    std::string temp_email;
    for(std::unordered_map<std::string,int>::iterator it = m_map.begin() ; it != m_map.end(); it++){
        if((it->second)>=threshold){
            EmailCount e(it->first, it->second);
            m_email_vect.push_back(e);
        }
    }
    
    //sort the final vector by email and total number of matches 
    sort(m_email_vect.begin(), m_email_vect.end());
    return m_email_vect;
}

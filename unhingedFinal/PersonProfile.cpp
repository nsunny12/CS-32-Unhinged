#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email){
    m_name=name;
    m_email=email;
}
PersonProfile::~PersonProfile(){}
std::string PersonProfile::GetName() const{
    return m_name;
}
std::string PersonProfile::GetEmail() const{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval){
    //check's if the attribute has alreday been inserted or not
    if(m_radTree.search(attval.attribute)!=nullptr){
        //checks if the attvalpair is in the vector or not
        std::vector<AttValPair>::iterator it;
        it = std::find(m_av_vect.begin(), m_av_vect.end(), attval);
        if(it != m_av_vect.end()){
                return;
        }
        //insert into the radixtree if it's not in the vector
    (*m_radTree.search(attval.attribute)).insert(attval.value);
    m_av_vect.push_back(attval);
    }
    else{
        //create a unique set of attval values
        std::unordered_set<std::string> unique_values;
        unique_values.insert(attval.value);
        //map them with corresponding attribute
        m_radTree.insert(attval.attribute, unique_values);
        //push back attval into vector
        m_av_vect.push_back(attval);
   }
}

int PersonProfile::GetNumAttValPairs() const{
    return static_cast<int>(m_av_vect.size());
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if(0 <= attribute_num && attribute_num < GetNumAttValPairs()){
        attval=m_av_vect[attribute_num];
            return true;
        }
    return false;
}

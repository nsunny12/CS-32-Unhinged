#include "MemberDatabase.h"
#include "provided.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

MemberDatabase::MemberDatabase(){
}

MemberDatabase::~MemberDatabase(){
    
}

bool MemberDatabase::LoadDatabase(std::string filename){
    std::ifstream infile(filename);
    if(!infile)
    {
      return false;
    }
    std::string name;

    while (getline(infile, name)){
        
        std::string email;
        
        if(!getline(infile, email)){
            return false;
        }
        PersonProfile p(name, email);
        
        std::string numAttValPairsString;
        if(!getline(infile,numAttValPairsString)){
            return false;
        }
        //converts the string version of the number from the txt into an int
        int numAttValPairs = std::stoi(numAttValPairsString);
        
        for(int i = 0; i< numAttValPairs; i++){
            std::string attribute_value;
            if(!getline(infile, attribute_value)){
                return false;
            }
            std::string attribute;
            std::string value;
            std::istringstream iss(attribute_value);

        
            if(!getline(iss, attribute, ',')){
                return false;
            }
            if(!getline(iss, value, ',')){
                return false;
            }
            
            std::string pair = attribute + "," + value;
            AttValPair a2(attribute, value);
            p.AddAttValPair(a2);
            
            //pairSearch holds the vector searched by m_radTree_avp_t_email's association with pair
            std::vector<std::string>* pairSearch = m_radTree_avp_t_email.search(pair);
            
            if(pairSearch == nullptr){
                std::vector<std::string> temp;
                temp.push_back(email);
                //inserts pair along with the associated vector of emails
                m_radTree_avp_t_email.insert(pair, temp);
            }
            
            else{
                //checks if the email is in the vector or not
                long int match = std::count(pairSearch->begin(), pairSearch->end(), email);
                if(match==0){
                    pairSearch->push_back(email);
                }
            }
        }
        
        //inserts email associated with a person profile if the email is new
        if(m_radTree_email_t_pp.search(email) == nullptr){
            m_radTree_email_t_pp.insert(email, p);
        }
        else{
            //if the email is a duplicate return false
            return false;
        }
        
        //checks for empty string/line between each person
        std::string empty;
        getline(infile,empty);
        if(empty!=""){
            return false;
        }
    }
    return true;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    PersonProfile* find = m_radTree_email_t_pp.search(email);
    return find;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    std::string pair = input.attribute + "," + input.value;
    if(m_radTree_avp_t_email.search(pair) != nullptr){
        return(*m_radTree_avp_t_email.search(pair));
    }
    std::vector<std::string> empty;
    return empty;
}

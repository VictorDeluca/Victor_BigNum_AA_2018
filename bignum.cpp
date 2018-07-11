//Formula: http://www.cburch.com/csbsju/cs/160/notes/31/1.html
//References: https://github.com/abhishekarya286/practice-code/blob/master/katatsuba.cpp
//A few extra comments explaining multiplication, and I added exponentiation just to have the complete BigNum set.

#include <bits/stdc++.h>
using namespace std;

//Strings can store numbers in decimal form.
string add(string lhs, string rhs) {
    int length = max(lhs.size(), rhs.size());
    int carry = 0;
    int sum_col;
    string result;

    //Pad the shorter string with zeros
    while (lhs.size() < length) 
      lhs.insert(0,"0");
            
    while (rhs.size() < length) 
      rhs.insert(0,"0");

    for (int i = length-1; i >= 0; i--) {
      sum_col = (lhs[i]-'0') + (rhs[i]-'0') + carry;
      carry = sum_col/10;
      result.insert(0,to_string(sum_col % 10));
    }
    
    if (carry)
      result.insert(0,to_string(carry));
    
    //Remove leading zeros
    return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
}

string subtract(string lhs, string rhs) {
    int length = max(lhs.size(), rhs.size());
    int diff;
    string result;

    while (lhs.size() < length) 
      lhs.insert(0,"0");
            
    while (rhs.size() < length) 
      rhs.insert(0,"0");

    for (int i = length-1; i >= 0; i--) {
        diff = (lhs[i]-'0') - (rhs[i]-'0');
        if (diff >= 0)
            result.insert(0, to_string(diff));
        else {
            //Borrow from the previous column
            int j = i - 1;
            while (j >= 0) {
                lhs[j] = ((lhs[j]-'0') - 1) % 10 + '0';
                if (lhs[j] != '9') 
                    break;
                else 
                    j--;
            }
            result.insert(0, to_string(diff+10));
        }
      
    }

    return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
}

string multiply(string lhs, string rhs) {
    int length = max(lhs.size(), rhs.size());
    
    while (lhs.size() < length) 
      lhs.insert(0,"0");

    while (rhs.size() < length) 
      rhs.insert(0,"0");

    if (length == 1)
        return to_string((lhs[0]-'0')*(rhs[0]-'0'));

    string lhs0 = lhs.substr(0,length/2); //aL
    string lhs1 = lhs.substr(length/2,length-length/2); //aR
    string rhs0 = rhs.substr(0,length/2); //bL
    string rhs1 = rhs.substr(length/2,length-length/2); //bR
    
		//a*b = (aL * 10^n/2 + aR)*(bL * 10^n/2 + bR) = 
		//aL*bL*10^n + (aL*bR + aR*bL)*10^n/2 + aR*bR
    string p0 = multiply(lhs0,rhs0); 
    string p1 = multiply(lhs1,rhs1);
    string p2 = multiply(add(lhs0,lhs1),add(rhs0,rhs1));
    string p3 = subtract(p2,add(p0,p1));

		//Handling multiplication by powers of 10;
    for (int i = 0; i < 2*(length-length/2); i++)
        p0.append("0");
    for (int i = 0; i < length-length/2; i++)
        p3.append("0");
        
    string result = add(add(p0,p1),p3);

		//Remove leading 0s
    return result.erase(0, min(result.find_first_not_of('0'), result.size()-1));
}

string fastexp(string s, int e){
	if(e==0) return "1";
	string ans = fastexp(s,e/2);
	ans = multiply(ans,ans);
	if(e&1) ans = multiply(ans,s);
	return ans;
}


int main(){
	cout << multiply("10000001000","999000000888000");
	
	return 0;
}
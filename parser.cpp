#include <bits/stdc++.h>
#define pb push_back
#define null NULL

using namespace std;

vector <string> operators;
set <string> directives, keywords, datatypes, operato;

int find_oper(string s, int idx){
	for(int i=0; i<operators.size(); i++){
		bool fl=true;
		int k=0;
		for(int j=idx; j<s.size() && k<operators[i].size(); j++,k++){
			if(operators[i][k]!=s[j]){
				fl=false;
				break;
			}
		}
		if(k!=operators[i].size()){
			fl=false;
		}
		if(fl){
			return operators[i].size();
		}
	}
	return 0;
}

string parse(string s){
	string ret="";
	for(int i=0; i<s.size(); i++){
		if(s[i]=='{' || s[i]=='}' || s[i]==';'){
			continue;
		}
		if(s[i]==' '){
			ret+=s[i];
			continue;
		}
		int len=find_oper(s, i);
		if(len==0){
			ret+=s[i];
		}
		else{
			ret+=' ';
			ret+=s.substr(i, len);
			ret+=' ';
			i+=len-1;
		}
	}
	return ret;
}

bool isnum(string s){
	for(int i=0; i<s.size(); i++){
		if(s[i]<'0' || s[i]>'9'){
			return false;
		}
	}
	return true;
}

bool cmp(string s1, string s2){
	return (s1.size()>s2.size());
}

void init(){
	string s;
	fstream kfile("keywords.txt");
	if(kfile.is_open()){
		while(getline(kfile, s)){
			//cout<<s<<endl;
			keywords.insert(s);
		}
		kfile.close();
	}
	fstream dfile("directives.txt");
	if(dfile.is_open()){
		while(getline(dfile, s)){
			directives.insert(s);
		}
		dfile.close();
	}
	fstream ofile("operators.txt");
	if(ofile.is_open()){
		while(getline(ofile, s)){
			operators.pb(s);
			operato.insert(s);
		}
		ofile.close();
	}
	sort(operators.begin(), operators.end(), cmp);
}

int main(){

	init();

	string s="";
	getline(cin, s);
	while(s!=""){
		s=parse(s);
		istringstream iss(s);
		string str;
		while(iss>>str){
			//cout<<str<<endl;
			if(operato.find(str)!=operato.end()){
				cout<<"Operator: "<<str<<endl;
			}
			else if(datatypes.find(str)!=datatypes.end()){
				cout<<"Datatype: "<<str<<endl;
			}
			else if(keywords.find(str)!=keywords.end()){
				cout<<"Keyword: "<<str<<endl;
			}
			else if(directives.find(str)!=directives.end()){
				cout<<"Directive "<<str<<endl;
			}
			else if(isnum(str)){
				cout<<"Number :"<<str<<endl;
			}
			else cout<<"Identifier: "<<str<<endl;
		}
		getline(cin, s);
	}
	return 0;
}
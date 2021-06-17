#include<bits/stdc++.h>
using namespace std;

struct HuffmanNode{
     char alphabet;
     int freq;
     struct HuffmanNode* left;
     struct HuffmanNode* right;
};
struct HuffmanNode* init(int freq,char a){
     struct HuffmanNode* newNode = new struct HuffmanNode;
     if(newNode){
          newNode->alphabet = a;
          newNode->freq = freq;
          newNode->left = NULL;
          newNode->right = NULL;
          return newNode;
     }
     return NULL;
}

bool compareFreq(struct HuffmanNode* n1,struct HuffmanNode*n2){
     return(n1->freq<n2->freq);
}

void preorder(struct HuffmanNode *root){
     if(root){
          cout<<root->alphabet<<" "<<root->freq<<endl;
          preorder(root->left);
          preorder(root->right);
     }
}
void codeProducer(struct HuffmanNode *root,string s,std::map<char,string>&m){
     if(root){
          if(root->left == NULL && root->right == NULL){
               m.insert(make_pair(root->alphabet,s));
          }
          else{
               codeProducer(root->left,s+'0',m);
               codeProducer(root->right,s+'1',m);
          }
     }
}

void decoder (string str,ofstream &file,int i,struct HuffmanNode*root,struct HuffmanNode *org){
     if(root-> left == NULL && root->right == NULL){
          cout<<root->alphabet;
          file<<root->alphabet;
          if(i!=str.size()-1)
          decoder(str,file,i,org,org);
     }
     else if(str.size()>=i){
          if(str[i] == '0'){
               // cout<<"going left "<<str[i]<<endl;
               decoder(str,file,i+1,root->left,org);
          }
          else if(str[i] == '1'){
               // cout<<"going right "<<str[i]<<endl;
               decoder(str,file,i+1,root->right,org);
          }
     }
     else{
          cout<<"The file has been corrupted!"<<endl;
     }
}

int main(){
     int n,i;
     char a ;
     struct HuffmanNode *temp;
     fstream file;
     vector<int>alpha (53,0);
     file.open("input.txt",ios::in);
     if(file.is_open()){
          string str;
          while(getline(file,str)){
               for(int i = 0;i< str.size();i++){
                    if(str[i]>='A' && str[i]<='Z'){
                         alpha[(int)(str[i]-'A')+1]++;
                    }
                    else{
                         alpha[(int)(str[i]-'a')+27]++;
                    }
               }

          }
     }
     else{
          cout<<"Error in opening the file!"<<endl;
     }
     vector<struct HuffmanNode*> arr;
     for(i=1;i<=52;i++){
          if(i<27){
               a = (char)(i + 64);
               
          }
          else{
               a = (char)( i + 70);
          }
          if(alpha[i]>0)
          {
               temp = init(alpha[i],a);
               if(temp){
                    arr.push_back(temp);
               }
               else{
                    i=52;
                    cout<<"Insufficient Space to convert the following"<<endl;
               }
          }
     }
     struct HuffmanNode* left;
     struct HuffmanNode* right;
     while(arr.size()!=1){
          sort(arr.begin(),arr.end(),compareFreq);
          left = arr[0];
          right = arr[1];
          struct HuffmanNode *newNode = init(left->freq+right->freq,'X');
          newNode->left = left;
          newNode->right = right;
          arr.erase(arr.begin());
          arr.erase(arr.begin());
          arr.push_back(newNode);
     }
     struct HuffmanNode *root = arr[0];
     //preorder(root);
     map<char,string>m;
     string s = "";
     codeProducer(root,s,m);
     cout<<"came here"<<endl;
     ofstream output;
     output.open("output.txt");
     fstream input;
     input.open("input.txt",ios::in);
     if(input.is_open()){
          string str;
          while(getline(input,str)){
               for(int i = 0;i< str.size();i++){
                    output<<m[str[i]];
               }
               output<<endl;
          }
          input.close();
          output.close();
     }
     else{
          cout<<"Error in opening the file!"<<endl;
     }
     fstream decoding;
     decoding.open("output.txt");
     ofstream write;
     write.open("decoded.txt");
     if(decoding.is_open()){
          string str;
          while(getline(decoding,str)){
               cout<<str.size()<<endl;
               decoder(str,write,0,root,root);
               write<<endl;
          }
     }


}
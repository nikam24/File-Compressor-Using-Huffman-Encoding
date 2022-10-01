#include<bits/stdc++.h>
using namespace std;
map<string,char> lookup;
map<char,string> lookup2;

struct MinHeapNode{
    char data;
    unsigned freq;

    struct MinHeapNode* right;
    struct MinHeapNode* left;

    MinHeapNode(char d,int f){
        data = d;
        freq = f;
        left = right = NULL;
    }
};

struct compare{
    bool operator()(MinHeapNode* h1,MinHeapNode* h2){
        return (h1->freq > h2->freq);
    }
};

void printCodes(MinHeapNode* root,string str){
    if(!root) return;

    if(root->data != '$'){
        lookup[str] = root->data;
        lookup2[root->data] = str;
        cout << root->data << " : " << str << endl;
    }

    printCodes(root->left,str+"0");
    printCodes(root->right,str+"1");
}

void writeBit(int b,FILE *f)
{//My Logic: Maintain static buffer, if it is full, write into file 
	static char byte;
	static int cnt;
	char temp;
	//printf("\nSetting %dth bit = %d of %d ",cnt,b,byte);
	if(b==1)
	{	temp=1;
		temp=temp<<(7-cnt);		//right shift bits
		byte=byte | temp;
	}
	cnt++;
	
	if(cnt==8)	//buffer full
	{
//		printf("[%s]",bitsInChar(byte));
		fwrite(&byte,sizeof(char),1,f);
		cnt=0; byte=0;	//reset buffer
		return;// buffer written to file
	}
	return;
}

void writeCode(char fname[])
{
    char ch;
    FILE *f = fopen("Compressed.bin","wb");
    fstream f2;
    f2.open(fname,ios::in);

    while(f2 >> noskipws >> ch){
        for(int i=0;i<lookup2[ch].size();i++){
            if(lookup2[ch][i] == '0') writeBit(0,f);
            else writeBit(1,f);
        }
    }

    fclose(f);
    f2.close();
	return;
}

void HuffmanCodes(map<char,int>& mp,int size)
{
    struct MinHeapNode* left,* right,* top;

    priority_queue<MinHeapNode*,vector<MinHeapNode*>,compare> minHeap;

    for(auto it:mp){
        minHeap.push(new MinHeapNode(it.first,it.second));
    }

    while(minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$',left->freq+right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodes(minHeap.top(),"");
}

void calculate_frequency(map<char,int>& mp,char fname[]){
    char ch;
    fstream f;
    f.open(fname,ios::in);

    while(f >> noskipws >> ch){
        mp[ch]++;
    }
}

int main(int argc,char **argv)
{
    map<char,int> mp;
    calculate_frequency(mp,argv[1]);
    
    fstream f;
    f.open("Compressed.bin",ios::out | ios::trunc);
    f.close();

    HuffmanCodes(mp,mp.size());
    cout << "--------------------------------" << endl;
    int usualbits = 0,totbitsinhuffman = 0;
    for(auto it:mp){
        totbitsinhuffman += lookup2[it.first].size()*it.second;
        usualbits += 8*it.second;
    }
    cout << "Usual bits required to send : " << usualbits << endl;
    cout << "Total bits required to Encode in Huffman : " << totbitsinhuffman << endl;
    
    writeCode(argv[1]);

    fstream f2;
    f.open("Compressed.bin",ios::in | ios::binary);
    f2.open("Decompressed_file.txt",ios::out | ios::trunc);

    cout << "-----------------------------------" << endl;

    unsigned char buffer = 0;
    string temp = "";
    int cnt = 0;
    while(f){
        f >> buffer;
        for(int i=7;i>=0;i--){
            if((buffer >> i)&1 == 1) temp += '1';
             else temp += '0';

            if(lookup.find(temp) != lookup.end()){
                f2 << lookup[temp];
                temp = "";
            }
        }
        buffer = 0;
    }

    f.close();
    f2.close();

    return 0;
}
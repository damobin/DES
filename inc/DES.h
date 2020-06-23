#ifndef DES_H
#define DES_H
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <deque>
#include <iterator>

#define ROUNDLENTH  		16
#define KEYLENTH  			8
#define KEYEXCBOOKLENTH  	(8*7)
#define INPUTEXCBOOKLENTH  	(8*8)
#define SUBKEYEXCBOOKLENTH  (6*8)
using namespace std;
class DES{
	friend ostream  &operator  <<(ostream &,const DES &);
	friend ofstream & operator <<(ofstream &os,const DES &D);
	friend istream  &operator  >>(istream &,DES &);
	friend ifstream &operator  >>(ifstream &,DES &);
public:
	DES()=default;
	static istream &exchangeKeys(istream &);
	static ifstream &exchangeKeys(ifstream &);
	void caculate();

	static array<int,ROUNDLENTH> 		arDESround;			//DES的轮常数
	static array<int,KEYLENTH> 			arDESkey;			//DES的秘钥
	static array<int,KEYEXCBOOKLENTH>   arDESkeyExcBook;	//DES的秘钥置换表格
	static array<int,INPUTEXCBOOKLENTH> arDESkeyInputBook;	//DES的输入置换表格
	static array<int,SUBKEYEXCBOOKLENTH> arDESsubkeyExcBook;//DES
private:
	array<array<int,8>,17> subDESkey={};			//DESsubKey
	vector<int>  			inputDESdata;			//DES输入数据
	vector<int>  			outputDESdata;			//DES输出数据
	int decLens;									//加密数据长度	
	int encLens;									//解密数据长度
};

//funs declear
unsigned char bitGetByte(deque<unsigned char>::iterator &it,unsigned int u32lens);
void shiftLeftMove(deque<unsigned char> &deq,int shiftNum);
template<typename inarMax,typename inarKeyMax>
void excBytetoBitBox(
	inarMax &inputMaxtrix,
	inarKeyMax &keyMaxtrix,
	int level);
#endif

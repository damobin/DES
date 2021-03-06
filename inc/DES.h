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
#define INPUTSUBBOOKLENTH   (7*8)
#define SUBKEYEXCBOOKLENTH  (6*8)
#define DESS_BOXLENTH  		(4*16)
#define S_BOX_NUM			8
#define P_BOX_NUM			(4*8)
#define IP_BOX_NUM			(8*8)


#define COMBINA_HEX(LowHex,HightHex)	(LowHex | (HightHex<<4))
enum	DESDEC_ENC{
	Encry,
	Decode,
};
enum	DIRECT{
	LEFT_DIR,
	RIGHT_DIR,
};


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
	void creatDESsubKey(DESDEC_ENC DEC_ENV);
	void DESCaculate(DESDEC_ENC	DEC_ENC);
	void desF_funs(array<int,8> &arObj,array<int,8> &subkey);

	static array<int,ROUNDLENTH> 		 				arDESround;		 	//DES的轮常数
	static array<int,ROUNDLENTH> 		 				arDESDecround;		//DES Dec的轮常数
	static array<int,KEYLENTH> 			 				arDESkey;			//DES的秘钥
	static array<int,KEYEXCBOOKLENTH>    				arDESkeyExcBook;	//DES的秘钥置换表格
	static array<int,INPUTEXCBOOKLENTH>  				arDESInputBook;	 	//DES的输入置换表格
	static array<int,INPUTSUBBOOKLENTH>  				arDESSubdataExcBook;//DES In data Exc Book
	static array<int,SUBKEYEXCBOOKLENTH> 				arDESsubkeyExcBook; //DES
	static array<array<int,DESS_BOXLENTH>,S_BOX_NUM> 	arDESSBOX;			//DES S-BOX
	static array<int,P_BOX_NUM> 						arDESPBOX;			//DES p-BOX
	static array<int,IP_BOX_NUM> 						arDESENDIPBOX;		//DES IP-BOX
private:
	array<array<int,8>,17> subDESInData={};			//DESsubdata
	array<array<int,8>,17> subDESkey={};			//DESsubKey
	vector<int>  			inputDESdata;			//DES输入数据
	vector<int>  			outputDESdata;			//DES输出数据
	int decLens;									//加密数据长度	
	int encLens;									//解密数据长度
};

//funs declear
unsigned char bitGetByte(deque<unsigned char>::iterator &it,unsigned int u32lens);
void shiftMove(deque<unsigned char> &deq,int shiftNum);
void shiftMove(deque<unsigned char> &deq,int shiftNum,DIRECT Dirt);
template<typename inarMax,typename inarKeyMax>
void excBytetoBitBox(
	inarMax &inputMaxtrix,
	inarKeyMax &keyMaxtrix,
	int level,
	int bitnum);							//box exc funs
	
template<typename srcMax,typename desMax>
bool XORmaxtrix(
	srcMax &inputMaxtrix,
	desMax &outputMaxtrix
	);										//contain xor funs
template<typename srcMax,typename desMax>
bool XORmaxtrix(
	srcMax &inputMaxtrix,
	desMax &outputMaxtrix,
	int    lens
	);
	
int excDataByS_Box(array<int,DESS_BOXLENTH> subS_BOX,int inputData);




#endif

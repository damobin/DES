#include <DES.h>
#include <iomanip>
#include <public.h>

array<int,ROUNDLENTH> 		 DES::arDESround	 =\
{
  1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 ,
  1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 
};
array<int,KEYLENTH> 		 DES::arDESkey	     =\
{
   1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,
   /*9 , 10 , 11 , 12 , 13 , 14 , 15 , 16 */
};
array<int,KEYEXCBOOKLENTH> 	 DES::arDESkeyExcBook=\
{ 
  57 , 49 , 41 , 33 , 25 , 17 ,  9,
   1 , 58 , 50 , 42 , 34 , 26 , 18,
  10 ,  2 , 59 , 51 , 43 , 35 , 27,
  19 , 11 ,  3 , 60 , 52 , 44 , 36,
  63 , 55 , 47 , 39 , 31 , 23 , 15,
   7 , 62 , 54 , 46 , 38 , 30 , 22,
  14 ,  6 , 61 , 53 , 45 , 37 , 29,
  21 , 13 ,  5 , 28 , 20 , 12 , 4
};
array<int,SUBKEYEXCBOOKLENTH> DES::arDESsubkeyExcBook=\
{ 
  14 , 17 , 11 , 24 ,  1 ,  5 ,
   3 , 28 , 15 ,  6 , 21 , 10 ,
  23 , 19 , 12 ,  4 , 26 ,  8 ,
  16 ,  7 , 27 , 20 , 13 ,  2 ,
  41 , 52 , 31 , 37 , 47 , 55 ,
  30 , 40 , 51 , 45 , 33 , 48 ,
  44 , 49 , 39 , 56 , 34 , 53 ,
  46 , 42 , 50 , 36 , 29 , 32 
};
array<int,INPUTEXCBOOKLENTH> DES::arDESkeyInputBook=\
{
  58 , 50 , 42 , 34 , 26 , 18 , 10 ,  2,
  60 , 52 , 44 , 36 , 28 , 20 , 12 ,  4,
  62 , 54 , 46 , 38 , 30 , 22 , 14 ,  6,
  64 , 56 , 48 , 40 , 32 , 24 , 16 ,  8,
  57 , 49 , 41 , 33 , 25 , 17 ,  9 ,  1,
  59 , 51 , 43 , 35 , 27 , 19 , 11 ,  3,
  61 , 53 , 45 , 37 , 29 , 21 , 13 ,  5,
  63 , 55 , 47 , 39 , 31 , 23 , 15 ,  7
};
//DES caculate
void DES::caculate()
{
	int index=0;
	int bytepos,bitpos;
	int temp;
	unsigned char subKeyBit[56];
	unsigned char subKey[8];
	array<int,KEYLENTH>  arsubKey(arDESkey);
	vector<int>          ivtinputtemp(inputDESdata);
	deque<unsigned char> partHead(28);
	deque<unsigned char> partTail(28);
	//sub key creat
	//EXC KEY
	cout<<"caculate!!"<<endl;
	//对秘钥进行表格1置换
	excBytetoBitBox<array<int,KEYEXCBOOKLENTH>,array<int,KEYLENTH>>\
		(arDESkeyExcBook,arsubKey,8,7);
	for(int i = 0;i<8;i++){
		uint8_t bitGetobj=0x40;
		for(int j = 0;j<7;j++){
			//秘钥二进制分为两块part A  part B
			if(i<4)
				partHead[i*7 + j]     = arsubKey[i] & bitGetobj;
			else
				partTail[(i-4)*7 + j] = arsubKey[i] & bitGetobj;
			bitGetobj >>= 1;
		}
	}
	
	//将PART A 和 PART B生成子秘钥存储到 数组中
	for(unsigned int i =0 ;i<17;i++){
		if(i==0){
			deque<unsigned char>::iterator it;
			for(unsigned int j=0 ;j<8;j++){
				if(j<4){
					it = partHead.begin() +j*7;
					subDESkey[i][j] = bitGetByte(it  ,7 );
				}else{
					it = partTail.begin()+ (j-4)*7;
					subDESkey[i][j] = bitGetByte(it  ,7 );
				}
			}
		}else{
			//round num
			uint8_t roundnum = arDESround[i-1];
			
			//shift left move partHead
			shiftLeftMove(partHead,roundnum);
			//shift left move partTail
			shiftLeftMove(partTail,roundnum);
			
			deque<unsigned char>::iterator it;
			for(unsigned int j=0 ;j<8;j++){
				if(j<4){
					it = partHead.begin() +j*7;
					subDESkey[i][j] = bitGetByte(it  ,7 );
				}else{
					it = partTail.begin()+ (j-4)*7;
					subDESkey[i][j] = bitGetByte(it  ,7 );
				}
			}
		}	
	}
	//使用PC-2 表格对子秘钥进行转置
	for(int i=0;i<17;i++)
		excBytetoBitBox< array<int,SUBKEYEXCBOOKLENTH> , array<int,8> >	\
			(arDESsubkeyExcBook,subDESkey[i],7,6);
	
	excBytetoBitBox< array<int,INPUTEXCBOOKLENTH> , vector<int> >	\
		(arDESkeyInputBook,ivtinputtemp,8,8);
	PRINTSTRDATA(ivtinputtemp,8,16);
}

//对输入数据  使用表格进行位转置
template<typename inarMax,typename inarKeyMax>
void excBytetoBitBox(
	inarMax &inputMaxtrix,
	inarKeyMax &keyMaxtrix,
	int level,
	int bitnum)
{
	uint8_t temp,index;
	uint8_t affectBit;
	int bytepos,bitpos;
	vector<uint8_t> bitBuff;
	//对秘钥进行表格置换
	for(auto i =inputMaxtrix.begin() ; i != inputMaxtrix.end() ; i++){
		bytepos = (*i) / level;
		if((*i) % level == 0 ){
			bytepos--;
			bitpos=0;
		}else{
#if     1
			//bit list little -- endian
			bitpos  = level-((*i) - bytepos*level);
#else
			//bit list big    -- endian
			bitpos  = ((*i) - bytepos*level);
#endif

		}
		temp 	= keyMaxtrix[bytepos] & 0xff;
		temp = temp & (1<<bitpos);
		bitBuff.push_back(temp);
		index++;
	}
	//after exc data exc hex list
	for(int i = 0;i<keyMaxtrix.size();i++){
		keyMaxtrix[i] = 0;
		for(int j = 0;j<bitnum;j++){
			if( bitBuff[ j + i*bitnum ] ){
				keyMaxtrix[i] <<= 1;
				keyMaxtrix[i] |=  1;
			}else{
				keyMaxtrix[i] <<= 1;
			}
		}
	}
}


unsigned char bitGetByte(deque<unsigned char>::iterator &it,unsigned int u32lens)
{
	unsigned char temp=0;
	for(int i=0;i<u32lens;i++){
		if(*it++){
			temp <<= 1;
			temp  |= 1;
		}else{
			temp <<= 1;
		}
	}
	return temp;
}

void shiftLeftMove(deque<unsigned char> &deq,int shiftNum)
{
	unsigned char temp;
	for(int i=0;i<shiftNum;i++){
		temp = deq[0];
		deq.pop_front();
		deq.push_back(temp);
	}
}

//exc DES key
istream &DES::exchangeKeys(istream &os)
{
	int temp,lable=0;
	auto pos = arDESkey.begin();
	cout<<"input key:"<<endl;
	
	while(lable < KEYLENTH && os>>hex>>temp ){
		*pos++ = temp&0xff;
		lable++;
	} 
	return os;
}
ifstream &DES::exchangeKeys(ifstream &os)
{
	int temp,lable=0;
	auto pos = arDESkey.begin();
	cout<<"input key:"<<endl;
	
	while(lable < KEYLENTH && os>>hex>>temp ){
		*pos++ = temp&0xff;
		lable++;
	} 
	return os;
}


//input DES struct
istream & operator >>(istream &os,DES &D)
{
	int temp,lable=0;
	cout<<"input intdata: "<<endl;
	while(temp != 0xffff && lable<8 && os>>hex>>temp ){
		D.inputDESdata.push_back(temp&0xff);
		lable++;
		D.decLens = lable;
	}
	return os;
}
ifstream &operator >>(ifstream &ifs,DES &D)
{
	int temp,lable=0;
	while(temp != 0xffff && lable<8 && ifs>>hex>>temp){
		D.inputDESdata.push_back(temp&0xff);
		lable++;
		D.decLens = lable;
	}
	return ifs;
}

//output DES struct
ostream & operator <<(ostream &os,const DES &D)
{
	os<<"dec Lens: "<<D.decLens<<endl;
	os<<"enc Lens: "<<D.encLens<<endl;

	//printf in data
	if(D.inputDESdata.empty()){
		os<<"empty input"<<endl;
	}else{
		os<<"input:"<<endl;
		for(auto i=D.inputDESdata.begin(); i != D.inputDESdata.end(); i++){	
			os<<hex<< *i<<" ";
		}
		os<<endl;
	}
	//printf out data
	if(D.outputDESdata.empty()){
		os<<"empty output"<<endl;
	}else{
		os<<"input:"<<endl;
		for(auto i=D.outputDESdata.begin(); i != D.outputDESdata.end(); i++){	
			os<<hex<< *i<<" ";
		}
		os<<endl;
	}
	//print Key
	os<<"key:"<<endl;
	for(auto i=DES::arDESkey.begin(); i != DES::arDESkey.end(); i++){	
		os<<hex<<*i<<" ";
	}
	
	//printf out subkey
	if(D.subDESkey.empty()){
		os<<"empty subkey"<<endl;
	}else{
		os<<"\nsubkey:"<<endl;
		for(auto i=D.subDESkey.begin(); i != D.subDESkey.end(); i++){
			for(auto j=(*i).begin(); j != (*i).end(); j++){
				os<<hex<<setw(2)<< *j<<" ";
			}
			os<<endl;
		}
		os<<endl;
	}
	os<<endl;
	return os;
}
ofstream & operator <<(ofstream &os,const DES &D)
{
	os<<"dec Lens: "<<D.decLens<<endl;
	os<<"enc Lens: "<<D.encLens<<endl;

	//printf in data
	if(D.inputDESdata.empty()){
		os<<"empty input"<<endl;
	}else{
		os<<"input:"<<endl;
		for(auto i=D.inputDESdata.begin(); i != D.inputDESdata.end(); i++){	
			os<<hex<< *i<<" ";
		}
		os<<endl;
	}
	//printf out data
	if(D.outputDESdata.empty()){
		os<<"empty output"<<endl;
	}else{
		os<<"input:"<<endl;
		for(auto i=D.outputDESdata.begin(); i != D.outputDESdata.end(); i++){	
			os<<hex<< *i<<" ";
		}
		os<<endl;
	}
	//print Key
	os<<"key:"<<endl;
	for(auto i=DES::arDESkey.begin(); i != DES::arDESkey.end(); i++){	
		os<<hex<<*i<<" ";
	}
	
	//printf out subkey
	if(D.subDESkey.empty()){
		os<<"empty subkey"<<endl;
	}else{
		os<<"subkey:"<<endl;
		for(auto i=D.subDESkey.begin(); i != D.subDESkey.end(); i++){
			for(auto j=(*i).begin(); j != (*i).end(); j++){
				os<<hex<<setw(2)<< *j<<" ";
			}
			os<<endl;
		}
		os<<endl;
	}
	os<<endl;
	return os;
}

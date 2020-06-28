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
array<int,INPUTSUBBOOKLENTH> 	 DES::arDESSubdataExcBook=\
{ 
  32 ,  1 ,  2 ,  3 ,  4 ,  5 ,
   4 ,  5 ,  6 ,  7 ,  8 ,  9 ,
   8 ,  9 , 10 , 11 , 12 , 13 ,
  12 , 13 , 14 , 15 , 16 , 17 ,
  16 , 17 , 18 , 19 , 20 , 21 ,
  20 , 21 , 22 , 23 , 24 , 25 ,
  24 , 25 , 26 , 27 , 28 , 29 ,
  28 , 29 , 30 , 31 , 32 ,  1 
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
array<int,INPUTEXCBOOKLENTH> DES::arDESInputBook=\
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
array< array<int,DESS_BOXLENTH>, S_BOX_NUM > DES::arDESSBOX=\
{{
	{
     14,   4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7,
      0,  15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8,
      4,   1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0,
     15,  12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13,
	},   
	{          
     15,   1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10,
      3,  13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5,
      0,  14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15,
     13,   8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9,
	},          
		   
	{          
	 10,   0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8,
     13,   7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1,
     13,   6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7,
      1,  10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12
	},          
			   
	{          
      7,  13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15,
     13,   8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9,
     10,   6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4,
      3,  15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14
	},          
			   
	{          
      2,  12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9,
     14,  11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6,
      4,   2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14,
     11,   8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3
	},          
			   
	{          
     12,   1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11,
     10,  15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8,
      9,  14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6,
      4,   3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13
	},          
			   
	{          
      4,  11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1,
     13,   0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6,
      1,   4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2,
      6,  11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12
	},          
			   
	{          
     13,   2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7,
      1,  15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2,
      7,  11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8,
      2,   1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11
	},
}};

array<int,P_BOX_NUM> 		DES::arDESPBOX=\
{
	 16  , 7  ,20  ,21,
	 29  ,12  ,28  ,17,
	  1  ,15  ,23  ,26,
	  5  ,18  ,31  ,10,
	  2  , 8  ,24  ,14,
	 32  ,27  , 3  , 9,
	 19  ,13  ,30  , 6,
	 22  ,11  , 4  ,25
};

array<int,IP_BOX_NUM> 	DES::arDESENDIPBOX = \
{
	40, 8,48,16,56,24,64,32,
	39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,
	37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,
	35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,
	33, 1,41, 9,49,17,57,25
};

//DES caculate
void DES::caculate()
{
	int index=0;
	int bytepos,bitpos;
	int temp,affectBit,level;
	unsigned char subKeyBit[56];
	unsigned char subKey[8];
	array<int,KEYLENTH>  arsubKey(arDESkey);
	vector<int>          ivtinputtemp(inputDESdata);
	deque<unsigned char> partHead(28);
	deque<unsigned char> partTail(28);
	deque<unsigned char> inDpartHead(32);
	deque<unsigned char> inDpartTail(32);
	//sub key creat
	//EXC KEY
	cout<<"caculate!!"<<endl;
	//对秘钥进行表格1置换
	affectBit = 7;
	level	  = 8;
	excBytetoBitBox<array<int,KEYEXCBOOKLENTH>,array<int,KEYLENTH>>\
		(arDESkeyExcBook,arsubKey,level,affectBit);
	for(int i = 0;i<level;i++){
		uint8_t bitGetobj= 1<<(affectBit-1);
		for(int j = 0;j<affectBit;j++){
			//秘钥二进制分为两块part A  part B
			if(i<4)
				partHead[i*affectBit + j]     = arsubKey[i] & bitGetobj;
			else
				partTail[(i-4)*affectBit + j] = arsubKey[i] & bitGetobj;
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
	affectBit = 6;
	level	  = 7;
	for(int i=0;i<17;i++)
		excBytetoBitBox< array<int,SUBKEYEXCBOOKLENTH> , array<int,8> >	\
			(arDESsubkeyExcBook,subDESkey[i],level,affectBit);
			
	//used box export Input data
	affectBit = 8;
	level	  = 8;
	excBytetoBitBox< array<int,INPUTEXCBOOKLENTH> , vector<int> >	\
		(arDESInputBook,ivtinputtemp,level,affectBit);

	for(int i = 0;i<level;i++){
		uint8_t bitGetobj= 1<<(affectBit-1);
		for(int j = 0;j<affectBit;j++){
			//秘钥二进制分为两块part A  part B
			if(i<4)
				inDpartHead[i*affectBit + j]     = ivtinputtemp[i] & bitGetobj;
			else
				inDpartTail[(i-4)*affectBit + j] = ivtinputtemp[i] & bitGetobj;
			bitGetobj >>= 1;
		}
	}
	// creat subInbyte
	for(int i=0;i<17;i++){
		if(i==0){
			deque<unsigned char>::iterator it;
			for(unsigned int j=0 ;j<8;j++){
				if(j<4){
					it = inDpartHead.begin() +j*level;
					subDESInData[i][j] = bitGetByte(it  ,level );
				}else{
					it = inDpartTail.begin()+ (j-4)*level;
					subDESInData[i][j] = bitGetByte(it  ,level );
				}
			}
		}else{
			level 		= 8;
			affectBit 	= 6;
			array<int,8> arInTempHead={subDESInData[i-1][0],subDESInData[i-1][1],\
				subDESInData[i-1][2],subDESInData[i-1][3]};
			array<int,8> arInTempTail={subDESInData[i-1][4],subDESInData[i-1][5],\
				subDESInData[i-1][6],subDESInData[i-1][7]};
				
			//last ln rn  	subDESInData[i-1][]
			excBytetoBitBox< array<int,INPUTSUBBOOKLENTH> , array<int,8> >	\
				(arDESSubdataExcBook,arInTempTail,level,affectBit);

			//exc xor funs     if lens err throw err
			try{
				XORmaxtrix< array<int,8>,array<int,8> >(subDESkey[i],arInTempTail);
			}catch(const char *msg){
				cout <<"ERR :"<<msg<<endl;
				exit(0);
			}
			//used s-box exc data
			for(int j=0;j<8;j++){
				arInTempTail[j] = excDataByS_Box(DES::arDESSBOX[j],arInTempTail[j]);
			}

			//P_BOX EXC DATA  
			level 		= 4;
			affectBit 	= 4;
			excBytetoBitBox< array<int,P_BOX_NUM> , array<int,8> >	\
				(arDESPBOX,arInTempTail,level,affectBit);
			
			for(int j=0;j<8;j+=2){
				arInTempTail[j/2]=COMBINA_HEX(arInTempTail[j+1],arInTempTail[j]);
			}
			//exc xor funs     if lens err throw err
			try{
				XORmaxtrix< array<int,8>,array<int,8> >(arInTempHead,arInTempTail);
			}catch(const char *msg){
				cout <<"ERR :"<<msg<<endl;
				exit(0);
			}
			for(int j=0;j<8;j++){
				if(j<4)
					subDESInData[i-1+1][j] = subDESInData[i-1][j+4];
				else
					subDESInData[i-1+1][j] = arInTempTail[j-4];
			}
		}                     
	}
	//exc head tail pos
	for(int temp,i =0;i<4;i++){
		temp 				= subDESInData[16][i];
		subDESInData[16][i] 	= subDESInData[16][i+4];
		subDESInData[16][i+4] 	= temp;
	}
	
	PRINTSTRDATA(subDESInData[16],8,16);
	//P_BOX EXC DATA  
	level 		= 8;
	affectBit 	= 8;
	excBytetoBitBox< array<int,IP_BOX_NUM> , array<int,8> >	\
		(arDESENDIPBOX,subDESInData[16],level,affectBit);
	
	PRINTSTRDATA(subDESInData[16],8,16);
}

int excDataByS_Box(array<int,DESS_BOXLENTH> subS_BOX,int inputData)
{
	uint8_t index;
	uint8_t line_num,col_num,temp = inputData & 0x3f;  //6 bit affect
	line_num = (( temp & 0x20 )>>4) | (temp & 0x01);
	col_num  = ((temp & 0x1e) >>1);
	index    = line_num * 0x10 + col_num;
	return   subS_BOX[index];
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


template<typename srcMax,typename desMax>
bool XORmaxtrix(
	srcMax &inputMaxtrix,
	desMax &outputMaxtrix
	)
{
	if(inputMaxtrix.size()!=outputMaxtrix.size()){
		throw "XOR LEN DIFF";
		return false;
	}
	for(auto i=inputMaxtrix.begin(),j=outputMaxtrix.begin();i!=inputMaxtrix.end();i++,j++){
		(*j) = (*i)^(*j);
	}
	return true;
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

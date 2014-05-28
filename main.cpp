//------------------------------------------------------------ -------------------------------
// Задание:Игрушечный менеджер памяти
// Автор:<Карпено Денис Константинович, Группа 172>
// Среда разработки:Xcode Version 4.5.2 (4G2008a)
// Дата последнего изменения 25.02.2013
// Особенности: Присутсвуют глобальные переменные из-за запрета изменения прототипов функции //------------------------------------------------------------ -------------------------------
#include <iostream>
#include <string>
#include "locale"
#include "vector"
#include "cmath"
using namespace std;
void ToyMp_initilizate(size_t MemSize);//функция для иницилизации памяти
int HowManyMem();//функция для подсчета запрашиваемой памяти void DeinitializeMemoryManager();//функция освобождение динамически выделяемой памяти
void HowManyBytes(string a,int &typebyte);//функция для подсчета памяти занимаемой типом
void myadress(int y);//функция для вывода внутреннего адреса void Mycin(string &type);//функция для считывания строки с пробелом
int HowManyemptyslots();//функция нахождение свободного участка максимальной длины
void* ToyMp_AllocateBlock(size_t SizeBlock);//функция для выделения участка памяти
void toymp_FreeBlock(void *OldMem);//функция освобождение блока памяти
void coutBlocks();//функция вывод информации о блоке
void* realloc ( void * ptr, size_t size );//функция для изменения памяти блока
int NumberBlock;//номер введеного блока
double *Mymem;//переменная для хранения массива
size_t MemSize;//переменная для хранения запрашиваемой памяти int howmanyblocks=0;
int size;
struct BlockInf{
void* adress; int start; size_t blockmem;
int sizecell; };
vector<BlockInf>Blocks; int main()
{
setlocale(LC_ALL, "Russian");// подключение русского языка bool goodmem=1;
int menu=10;
cout<<"Добро пожаловать в игрушечный менеджер памяти!\n"; while (goodmem) {
cout<<"Введите количество выделяемой памяти\n>"; cin>>MemSize;
if((MemSize%8==0)&&(MemSize>0))
goodmem=0; else
cout<<"Память должна быть кратна 8 и больше 0!\n";
} ToyMp_initilizate(MemSize); while(!(menu==6)){
cout<<"\n Меню\n1)Выделение памяти\n2)Удаление блока памяти\n3)Вывести информацию о блоках памяти\n4)Вывести все ячейки памяти\n5)Изменить размер блока\n6)Конец программы\n>";
cin>>menu; if(menu==6)
DeinitializeMemoryManager(); if(menu==1)
ToyMp_AllocateBlock(HowManyMem()); if(menu==2){
coutBlocks();
cout<<"\nВведите номер удаляемого блока\n>"; cin>>NumberBlock;
NumberBlock--;
if((NumberBlock<Blocks.size())&&(NumberBlock>=0))//проверка ввода!на существование блока
toymp_FreeBlock(Blocks[NumberBlock].adress); else
cout<<"Такого блока не существует\n";
} if(menu==3){
coutBlocks(); }
if(menu==4){
cout<<"Память мeнeджера:\n"; for(int i=0;i<MemSize/8;i++)
cout<<"|"<<Mymem[i]<<"|";
} if(menu==5){
coutBlocks();
cout<<"\nВведите номер изменяемого блока\n>"; cin>>NumberBlock;
NumberBlock--;
if((NumberBlock<Blocks.size())&&(NumberBlock>=0)){//проверка ввода!на существование блока
cout<<"Введите на сколько надо изменить память(можно отрицательную)?";
cin>>size;
realloc (Blocks[NumberBlock].adress, size ); }
else
} }
}
cout<<"Такого блока не существует\n";
void ToyMp_initilizate(size_t MemSize){//функция для иницилизации памяти
int i;
Mymem=new(nothrow) double[MemSize/8];//Создание динамического массива
if(Mymem==0){
cout<<"Проблема с выделением памяти";
}
for(i=0;i<MemSize/8;i++)//заполнения массива нулями (свободным пространством)
Mymem[i]=0;
}
void* ToyMp_AllocateBlock(size_t SizeBlock){//функция для выделения блока памяти
int i=0,j=0,cell=0,start=0;
double stack=0;
if(SizeBlock%8==0)//округление в большую сторону
cell=SizeBlock/8; else
cell=SizeBlock/8+1;// stack=HowManyemptyslots();//присвоение свободного участка
самого большого размера
for(i=0;i<MemSize/8;i++){ if(Mymem[i]==0)
j++; else{
if((j<=stack)&&(j>=cell)){//проверка меньше ли этот участок памяти и входит ли в него блок
stack=j;
start=i-stack;//найдено начало и кол-во элементов для помещения
}
j=0; }
}
if((j<=stack)&&(j>=cell)){//конечная проверка, так как память может заканчиваться на 0
stack=j;
j=0;
start=i-stack;//найдено начало и кол-во элементов для
помещения
}
cout<<"Требуется памяти:"<<SizeBlock<<"\n"; cout<<"Требуется ячеек памяти:"<<cell<<"\n"; BlockInf dummy; if(SizeBlock/8.<=stack){//достаточно ли памяти?
for(i=start;i<cell+start;i++)//если да то заполняются свободные ячейки
Mymem[i]=1;
cout<<"Машинный адрес выделенного
участка:"<<Mymem+start<<"\n";
cout<<"Внутренний адрес выделенного участка:"; myadress(start);
Blocks.push_back(dummy); Blocks[howmanyblocks].start=start; Blocks[howmanyblocks].adress=Mymem+start; Blocks[howmanyblocks].sizecell=cell; Blocks[howmanyblocks].blockmem=SizeBlock; howmanyblocks++;
return (Mymem+start);
} else{
cout<<"Недостаточно памяти!\n";
return 0; }
}
int HowManyMem(){//функция для подсчета памяти
string Specific,type;
bool cinStruct=1;
char mas[10];//массив для считывание остатков потока int typebyte=0,quantity=0;
size_t bytes=0;
while (bytes==0) {//цикл для корректности ввода спецификации данных
cout<<"Введите спецификацию данных(fixedsize/struct/array):";
cin>>Specific;
cin.getline(mas,5);//считывание предыдущих введений(Для очистки буфера)
if(Specific=="fixedsize"){ cout<<"Введите кол-во байт:"; cin>>bytes;
} if(Specific=="struct"){
while(cinStruct){
cout<<"Введите параметр(char,short
int,double,int,long int,float,end-для конца):";
Mycin(type); if(type=="end"){
cinStruct=0;
break; }
HowManyBytes(type,typebyte); if(typebyte==0)
cout<<"Вы неверно ввели тип!\n"; bytes+=typebyte;//суммирование памяти
занимаемой типами
}
} if(Specific=="array"){
while (cinStruct) {//цикл проверки корректности
ввода
cout<<"Введите тип массива(char,short int,double,int,long int,float):";//сделать проверку ввода !!!!
cin.sync();
Mycin(type); HowManyBytes(type,typebyte); if(!typebyte==0)
cinStruct=0; else
cout<<"Вы неверно ввели тип!\n";
}
cout<<"Введите количество элементов массива:";//проверку ввода
cin>>quantity; bytes=quantity*typebyte;//умножение кол-ва
элементов на тип
} if(bytes==0)
cout<<"Блок занимает 0 байт ,повторите ввод\n"; return bytes;
void HowManyBytes(string a,int &typebyte){//для подсчета памяти занимаемой типом
typebyte=0; if(a=="char")
typebyte=sizeof(char); if(a=="short int")
typebyte=sizeof(short int); if(a=="double")
typebyte=sizeof(double); if(a=="int")
} }
typebyte=sizeof(int); if(a=="long int")
typebyte=sizeof(long int); if(a=="float")
typebyte=sizeof(float);
}
void Mycin(string &type){//функция для считывание строки с пробелом
char mass[10]; cin.getline(mass,10);//считывание строки char type=mass;//преобразование char в string
}
int HowManyemptyslots(){ //нахождение свободного участка максимальной длины
int emptyslots=0,k=0;
for(int i=0;i<MemSize/8;i++){
if(Mymem[i]==0){ emptyslots++;
} else{
if(k<emptyslots){ k=emptyslots;
}
emptyslots=0; }
} if(k<emptyslots)
k=emptyslots; return k;
}
void toymp_FreeBlock(void *OldMem){ //освобождение блока памяти
int i=0;
for(i=0;i<howmanyblocks;i++){//поиск блока с таким же адресом
if(Blocks[i].adress==OldMem) break;
}
for(int a=Blocks[i].start;a<Blocks[i].start+Blocks[i].sizecell;a++)
Mymem[a]=0; Blocks.erase(Blocks.begin()+i);// howmanyblocks--;
}
void coutBlocks(){//вывод информации о блоке int i;
for(i=0;i<howmanyblocks;i++){
cout<<"\n"<<i+1<<"-ый блок:\n";
cout<<"Занимает ячеек:"<<Blocks[i].sizecell<<"\n";
cout<<"Занимает памяти:"<<Blocks[i].blockmem<<"\n"; cout<<"Машинный адрес:"<<Blocks[i].adress<<"\n"; cout<<"Внутренний адрес:"; myadress(Blocks[i].start);
} }
void DeinitializeMemoryManager(){//освобождение динамически выделяемой памяти
delete []Mymem;
Blocks.erase(Blocks.begin(),Blocks.begin()+Blocks.size()); }
void* realloc ( void * ptr, size_t size ){ int i=0,newMem;
for(i=0;i<howmanyblocks;i++){//поиск блока с таким же адресом
if(Blocks[i].adress==ptr) break;
}
newMem=Blocks[i].blockmem+size; toymp_FreeBlock(ptr);//удаляет старый блок if(ToyMp_AllocateBlock(newMem)){ //ищет блок с новой
памятью
return Blocks[howmanyblocks].adress; }
else{
ToyMp_AllocateBlock(newMem-size);//выделяет память для
старого блока
cout<<"Не удалось изменить память";
return 0; }
}
void myadress(int y){//функция которая считает внутренний адрес
if(y<16) cout<<"0x000"<<hex<<y<<dec;
else if(y<256) cout<<"0x00"<<hex<<y<<dec;
}

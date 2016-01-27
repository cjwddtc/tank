#include "control.h"
#include <stdlib.h>
#include <memory.h>
namespace control{/*
template <typename T>
void data::push_data(T a)
{
	pos+=sizeof(T);
	while(pos>size){
		size<<=1;
		ptr=(char*)realloc(ptr,size);
	}
	*(T *)(ptr+pos)=a;
}

template <typename T>
T data::pop_data()
{
	pos-=sizeof(T);
	return *(T *)(ptr+pos);
}

data::data():ptr((char *)malloc(sizeof(int))),pos(0),size(sizeof(int)){}

data::data(const data&other):ptr((char *)malloc(other.pos)),pos(other.pos),size(other.pos){
	memcpy(ptr,other.ptr,other.pos);
}
data::data(data&&other):ptr(other.ptr),pos(other.pos),size(other.size){
	other.ptr=0;
}

data::~data()
{
	if(ptr!=0) free(ptr);
}
*/
}

#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>

class Object
{
public:
    Object()//默认构造函数
    {
        objName = "objName";
        dataLength = 10;
        data  = new int[dataLength];
    }

    Object(const std::string& name)//参数化构造函数
    {
        data  = new int[10];
        objName = name;
    }

    Object(const std::string& name,unsigned count):Object(name)//带参构造函数,委托构造函数
    {
        //这个函数是错误的
        dataLength = count;
    }

    Object(const Object& other)//拷贝构造函数
    {
        this->objName = other.objName;
        this->dataLength = other.dataLength;
        this->data = new int[other.dataLength];
        memcpy(this->data,other.data,sizeof (int) * other.dataLength);
    }

    Object(Object&& other)//移动构造函数
    {
        this->objName = other.objName;
        this->dataLength = other.dataLength;
        this->data = other.data;
        other.data = nullptr;
    }
    ~Object()
    {
        if(data != nullptr)
        {
            delete [] data;
            data = nullptr;
        }
    }


    //运算符重载：RT operator op (Args...)，其中op为具体的运算符
    std::size_t operator ()()// ()重载，又叫可调用对象
    {
        return dataLength;
    }

    std::size_t operator ()(int num)
    {
        return dataLength + num;
    }

    Object operator + (const Object& other)
    {
        Object obj = *this;
        obj.dataLength += other.dataLength;
        return obj;
    }

    bool operator == (const Object& other)// == 运算符重载
    {
        return this->objName == other.objName &&
            this->dataLength == other.dataLength;
    }

    Object& operator = (const Object& other)// 赋值运算符
    {
        this->objName = other.objName;
        this->dataLength = other.dataLength;
        this->data = new int[other.dataLength];
        memcpy(this->data,other.data,sizeof (int) * other.dataLength);
        return *this;
    }
    Object& operator = (Object&& other)// 移动赋值运算符
    {
        this->objName = other.objName;
        this->dataLength = other.dataLength;
        this->data = other.data;
        other.data = nullptr;
        return *this;
    }

private:
    int* data;
    std::string objName;
    unsigned dataLength;
};

#endif // OBSERVER_H

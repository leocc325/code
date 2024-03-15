#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
Q_OBJECT

public:
explicit Widget(QWidget *parent = nullptr);
~Widget();

private:
Ui::Widget *ui;
};

class Object
{
public:
    Object()//默认构造函数
    {
        objName = "objName";
        dataLength = 10;
        data  = new int[dataLength];

        for(unsigned i = 0; i < dataLength ; i++)
        {
            data[i] = i + 10;
        }
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

    //多数运算符既可以作为成员函数重载，也可以作为非成员函数（通常是全局函数或友元函数）重载。
    //必须作为成员函数重载的运算符有 1.赋值运算符 =  2.下标运算符 [] 3.函数调用运算符 () 4.成员访问箭头运算符 ->

    /*
     * 重载运算符一个重点在于左操作数和右操作数的匹配
     * 当运算符重载为成员函数时,参数列表会自动隐藏包含一个*this参数(第一个参数),即调用对象自动成为左操作数,成员函数的参数成为右操作数。
     *
     * 但是在重载<<或者>>时,通常应该将ostream或者istream作为左操作数,特别是对于<<运算符,它通常需要流对象作为左操作数
     * 此时如果将其重载为成员函数，那么左操作数就默认变成了*this，从而导致类型匹配失败，函数无法调用
     *
     * 当运算符重载为非成员函数时,参数列表没有隐藏参数,但是可以保证参数的对称性,此时函数的第一个参数是左操作数，第二个参数是右操作数。
    */


    std::size_t operator ()()// ()重载，包含()重载的类又叫可调用对象
    {
        return dataLength;
    }

    std::size_t operator ()(int num)
    {
        return dataLength + num;
    }

    //作为成员函数重载+运算符
    Object operator + (const Object& other)
    {
        Object obj = *this;
        obj.dataLength += other.dataLength;
        return obj;
    }

    //作为全局函数重载+运算符
    /*
    friend Object operator + (const Object& lObj,const Object& rObj)
    {
        Object obj;
        obj.dataLength = lObj.dataLength + rObj.dataLength;
        return obj;
    }
    */

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

    friend std::ostream& operator << (std::ostream& os,const Object& obj)
    {
        std::string arrayString ;
        for(unsigned i = 0; i < obj.dataLength; i++)
        {
            arrayString += std::to_string(obj.data[i]);
            if(i < (obj.dataLength - 1) )
            {
                arrayString += "[SP]";
            }
        }
        os << arrayString<<" "<< obj.objName <<" "<< obj.dataLength;
        return os;
    }


    friend std::istream& operator >> (std::istream& is,Object& obj)
    {
        std::string arrayString ;

        is >> arrayString;
        is >> obj.objName >> obj.dataLength;

        return is;
    }

    void test()
    {
        // 定义一个指向成员函数的指针类型
        void (Object::*funcPtr)() = &Object::test;
        // 打印成员函数地址
        std::cout << "Address of myMemberFunction: " << (void*&)funcPtr <<"          "<<this<< std::endl;
    }

private:
    int* data;
    std::string objName;
    unsigned dataLength;
};

#endif // WIDGET_H

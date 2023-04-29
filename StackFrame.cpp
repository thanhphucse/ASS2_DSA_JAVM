#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::run(string filename)
{
    int line = 0;
    string s = "";
    fstream input(filename, ios::in);
    while (!input.eof())
    {
        getline(input, s);
        ++line;
        if ((int)s.find(" ") != -1)
        { // cau lenh co chua tham so
            string Temp1 = s.substr(0, s.find(" "));
            string Temp2 = s.substr(s.find(" ") + 1, s.length() - s.find(" ") - 1);
            if (Temp1 == "iconst")
            {
                this->iconst(stoi(Temp2), line);
            }
            else if (Temp1 == "fconst")
            {
                this->fconst(stof(Temp2), line);
            }
            else if (Temp1 == "iload")
            {
                this->iload(Temp2, line);
            }
            else if (Temp1 == "fload")
            {
                this->fload(Temp2, line);
            }
            else if (Temp1 == "istore")
            {
                this->istore(Temp2, line);
            }
            else if (Temp1 == "fstore")
            {
                this->fstore(Temp2, line);
            }
            else if(Temp1 == "val")
            {
                this->val(Temp2, line);
            } else this->par(Temp2, line);
            // else if(Temp1 == "par")
            // {
            //     this->par(Temp2, line);
            // }
        }
        else
        { // cau lenh khong chua tham so
            if (s == "iadd")
            {
                this->iadd(line);
            }
            else if (s == "fadd")
            {
                this->fadd(line);
            }
            else if (s == "isub")
            {
                this->isub(line);
            }
            else if (s == "fsub")
            {
                this->fsub(line);
            }
            else if (s == "imul")
            {
                
                this->imul(line);
            }
            else if (s == "fmul")
            {
                this->fmul(line);
            }
            else if (s == "idiv")
            {
                this->idiv(line);
            }
            else if (s == "fdiv")
            {
                this->fdiv(line);
            }
            else if (s == "irem")
            {
                this->irem(line);
            }
            else if (s == "ineg")
            {
                this->ineg(line);
            }
            else if (s == "fneg")
            {
                this->fneg(line);
            }
            else if (s == "iand")
            {
                this->iand(line);
            }
            else if (s == "ior")
            {
                this->ior(line);
            }
            else if (s == "ieq")
            {
                this->ieq(line);
            }
            else if (s == "feq")
            {
                this->feq(line);
            }
            else if (s == "ineq")
            {
                this->ineq(line);
            }
            else if (s == "fneq")
            {
                this->fneq(line);
            }
            else if (s == "ilt")
            {
                this->ilt(line);
            }
            else if (s == "flt")
            {
                this->flt(line);
            }
            else if (s == "igt")
            {
                this->igt(line);
            }
            else if (s == "fgt")
            {
                this->fgt(line);
            }
            else if (s == "ibnot")
            {
                this->ibnot(line);
            }
            else if (s == "i2f")
            {
                this->i2f(line);
            }
            else if (s == "f2i")
            {
                this->f2i(line);
            }
            else this->_top(line);
            // else if (s == "top")
            // {
            //     // cout <<"hello";
            //     this->_top(line);
            // }
        }
    }
    input.close();
}
void StackFrame::_top(int line)
{
    if(this->opstack.size() != 0)
    {
        if (this->opstack.top().type == 0)
        {
            cout << (int)this->opstack.top().val;
        }
        else
        {
            cout << this->opstack.top().val;
        }
        cout << '\n';
    }
    else throw(StackEmpty(line));
}
void StackFrame::iadd(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = (int)temp1.val + (int)temp2.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fadd(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = (float)temp1.val + (float)temp2.val;
        temp1.type = 1;
        this->opstack.push(temp1);
    }
}

void StackFrame::isub(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = (int)temp2.val - (int)temp1.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fsub(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = (float)temp2.val - (float)temp1.val;
        temp1.type = 1;
        this->opstack.push(temp1);
    }
}

void StackFrame::imul(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = (int)temp1.val * (int)temp2.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fmul(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = (float)temp2.val * (float)temp1.val;
        temp1.type = 1;
        this->opstack.push(temp1);
    }
}
void StackFrame::idiv(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            if (temp1.val == 0)
                throw(DivideByZero(line));
            temp1.val = (int)temp2.val / (int)temp1.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fdiv(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        if (temp1.val == 0.0)
            throw(DivideByZero(line));
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = (float)temp2.val / (float)temp1.val;
        temp1.type = 1;
        this->opstack.push(temp1);
    }
}

void StackFrame::irem(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            if (temp1.val == 0)
                throw(DivideByZero(line));
            temp1.val = (int)temp2.val - (int)(temp2.val/temp1.val)*temp1.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}

void StackFrame::ineg(int line)
{
    if (this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0)
        {
            temp1.val = -((int)temp1.val);
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fneg(int line)
{
    if (this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        temp1.val = -((float)temp1.val);
        temp1.type = 1;
        this->opstack.push(temp1);
    }
}

void StackFrame::iand(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = (int)temp1.val & (int)temp2.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::ior(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = (int)temp1.val | (int)temp2.val;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}

void StackFrame::ieq(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = ((int)temp2.val == (int)temp1.val) ? 1 : 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::feq(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = ((float)temp2.val == (float)temp1.val) ? 1 : 0;
        temp1.type = 0;
        this->opstack.push(temp1);
    }
}

void StackFrame::ineq(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = ((int)temp2.val != (int)temp1.val) ? 1 : 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fneq(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = ((float)temp2.val != (float)temp1.val) ? 1 : 0;
        temp1.type = 0;
        this->opstack.push(temp1);
    }
}
void StackFrame::ilt(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = ((int)temp2.val < (int)temp1.val) ? 1 : 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::flt(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = ((float)temp2.val < (float)temp1.val) ? 1 : 0;
        temp1.type = 0;
        this->opstack.push(temp1);
    }
}

void StackFrame::igt(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0 && temp2.type == 0)
        {
            temp1.val = ((int)temp2.val > (int)temp1.val) ? 1 : 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::fgt(int line)
{
    if (this->opstack.size() < 2)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        DATA temp2 = this->opstack.top();
        this->opstack.pop();
        temp1.val = ((float)temp2.val > (float)temp1.val) ? 1 : 0;
        temp1.type = 0;
        this->opstack.push(temp1);
    }
}
void StackFrame::ibnot(int line)
{
    if (this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0)
        {
            temp1.val = ((int)temp1.val == 0) ? 1 : 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::i2f(int line)
{
    if (this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 0)
        {
            temp1.val = (float)temp1.val;
            temp1.type = 1;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}
void StackFrame::f2i(int line)
{
    if (this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp1 = this->opstack.top();
        this->opstack.pop();
        if (temp1.type == 1)
        {
            temp1.val = (int)temp1.val;
            temp1.type = 0;
            this->opstack.push(temp1);
        }
        else
        {
            throw(TypeMisMatch(line));
        }
    }
}

void StackFrame::iconst(int val, int line)
{
    if ((int)this->opstack.size() == opStackMaxSize / 2)
        throw(StackFull(line));
    else
    {
        DATA temp;
        temp.val = val;
        temp.type = 0;
        this->opstack.push(temp);
    }
}
void StackFrame::fconst(float val, int line)
{
    if ((int)this->opstack.size() == opStackMaxSize / 2)
        throw(StackFull(line));
    else
    {
        DATA temp;
        temp.val = val;
        temp.type = 1;
        this->opstack.push(temp);
    }
}

void StackFrame::istore(string key, int line)
{

    if(this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp = this->opstack.top();
        this->opstack.pop();
        if(temp.type == 0)
        {
            if(!this->LV->replace(temp, key))
            {
                if(this->LV->getCount() == localVarSpaceSize/2)
                    throw(LocalSpaceFull(line));
                else
                {
                    this->LV->insert(temp, key);
                }
            }
        }
        else throw(TypeMisMatch(line));
    }
}
void StackFrame::fstore(string key, int line)
{
    if(this->opstack.size() < 1)
        throw(StackEmpty(line));
    else
    {
        DATA temp = this->opstack.top();
        this->opstack.pop();
        if(temp.type == 1)
        {
            if(!this->LV->replace(temp, key))
            {
                if(this->LV->getCount() == localVarSpaceSize/2)
                    throw(LocalSpaceFull(line));
                else
                {
                    this->LV->insert(temp, key);
                }
            }
        }
        else throw(TypeMisMatch(line));
    }
}

void StackFrame::iload(string key, int line){
    DATA get;
    if(this->LV->findKey(key, get))
    {
        if(get.type == 0)
        {
            if((int)this->opstack.size() == opStackMaxSize/2) throw(StackFull(line));
            else
            {
                this->opstack.push(get);
            }
        }
        else throw(TypeMisMatch(line));
    }
    else throw(UndefinedVariable(line));
}
void StackFrame::fload(string key, int line)
{
    DATA get;
    if(this->LV->findKey(key, get))
    {
        if(get.type == 1)
        {
            if((int)this->opstack.size() == opStackMaxSize/2) throw(StackFull(line));
            else
            {
                this->opstack.push(get);
            }
        }
        else throw(TypeMisMatch(line));
    }
    else throw(UndefinedVariable(line));
}

void StackFrame::val(string key, int line)
{
    DATA get;
    if(this->LV->findKey(key, get))
    {
        if(get.type == 0)
        {
            cout << (int)get.val << "\n";
        }
        else cout << get.val << "\n";
    }
    else throw(UndefinedVariable(line));
}
void StackFrame::par(string key1, int line)
{
    if(this->LV->checkRoot(key1)) cout << "null" <<'\n';
    else
    {
        string get = "";
        if(this->LV->findPar(key1, get))
        {
            cout << get << '\n';
        }
        else throw(UndefinedVariable(line));
    }
}


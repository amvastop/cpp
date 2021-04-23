#include <iostream>

using namespace std;
template <typename T>
class Turn
{
    private:
        struct Element
        {
            Element* nextelemet;
            T* value;
        };
        int length = 0; 
        Element* lastelemetofturn;
        Element* firstelementofturn;
    public:
      
        Turn(const int N = 0) : length(N)
        {
            if(length > 0) 
            {
                lastelemetofturn = new Element;
                firstelementofturn = lastelemetofturn;
                
                for (int i = 1; i < length; i++)
                {
                    lastelemetofturn->nextelemet = new Element;
                    lastelemetofturn = lastelemetofturn->nextelemet;
                }
                
            }
        } 


        class Iterator
        {
            private:
                Element* element;
            
            public:
        
                void setElement(Element* el)
                {
                    element = el;
                }
                bool operator!=(const Iterator &it) const
                {
                    return this->element != it.element;
                }

            
                Iterator  operator++(int)
                {
                    element = element->nextelemet;
                    return *this;
                }


                T  operator *() 
                {
                    return *(element->value);
                }


        };
    
        int getLength()
        {
            return length;
        }

        Iterator begin()
        {
            
            Iterator itr;
            if(length > 0)
            {
                
                itr.setElement(firstelementofturn);
                return itr;
            }
            else
            {
                itr.setElement(nullptr);
                return itr;

            }
            

        }
        Iterator end()
        {
            Iterator itr;
            if(length > 0)
            {
                
                itr.setElement(lastelemetofturn->nextelemet);
                return itr;
            }
            else
            {
                itr.setElement(nullptr);
                return itr;

            }
            
            

        }
        T* front()
        {
            if(length > 0)
                return firstelementofturn->value;
            else
                return nullptr;
            
        }
        void pop()
        {
            if (length > 0)
            {
                Element* el = firstelementofturn;
                length--;
                firstelementofturn = firstelementofturn->nextelemet;
                delete el;
            }

        }
        void push(T element)
        {
            if(length == 0)
            {
                
                firstelementofturn = new Element;
                firstelementofturn->value = new T {element};
                lastelemetofturn = firstelementofturn;
            } 
            else
            {
                lastelemetofturn->nextelemet = new Element;
                lastelemetofturn = lastelemetofturn->nextelemet;
                lastelemetofturn->value = new T {element};
            }
            
            length++;
        }

        bool IsEmpty()
        {
            return length > 0 ? true : false; 

        }
        ~Turn()
        {
            Element* el;
            for(int i = 0; i < length - 1; i++)
            {
                el = firstelementofturn->nextelemet;
                delete firstelementofturn;
                firstelementofturn = el;

            }
            delete firstelementofturn;

        }

};

int main()
{
    Turn<int> array;
    array.push(10);
    //cout << array.front() << endl;
    array.push(10);
    array.push(11);
    for (auto it =  array.begin(); it != array.end() ; it++)
    {
        cout << *it << endl;
    }
    array.pop();
    for (auto it =  array.begin(); it != array.end() ; it++)
    {
        cout << *it << endl;
    }
    
   
    return 0;
}
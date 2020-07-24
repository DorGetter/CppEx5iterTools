//
// Created by dor on 22/07/2020.
//

#ifndef UNTITLED11_FILTERFALSE_HPP
#define UNTITLED11_FILTERFALSE_HPP
#include <iostream>
#include <vector>
namespace itertools{

    template <typename FUNCTION , typename CONTAINER>
    class filterfalse{
        FUNCTION function1;
        CONTAINER& container1;
        typedef typename CONTAINER::value_type value_type;
    public:
        filterfalse(FUNCTION function , CONTAINER& container):function1(function),container1(container){}
        filterfalse(FUNCTION function, CONTAINER&& container):function1(function),container1(container){}
        class iterator{
            typename CONTAINER::iterator   begin_iter1;
            typename CONTAINER::iterator   end_iter1;
            FUNCTION function1;
        public:
            explicit iterator(typename CONTAINER::iterator begin,
                              typename CONTAINER::iterator end,
                              FUNCTION function):
                              begin_iter1(begin),end_iter1(end),function1(function){
                while(begin_iter1 != end_iter1 && function(*begin_iter1))
                    ++begin_iter1;
            }

            iterator& operator=(const iterator &other){
                if(this != &other) {
                    this->begin_iter1  = other.begin_iter1;
                    this->end_iter1    = other.end_iter1;
                    this->function1    = other.function1;
                }
                return *this;
            };
            //first increment then return value. ++i
            iterator& operator++(){
                ++begin_iter1;
               while(begin_iter1 != end_iter1 && function1(*begin_iter1)) {
                   ++begin_iter1;
               }
               return *this;
            };

            //return value before icrement. i++
            iterator operator++(int) {iterator temp_ = *this; ++(*this); return temp_;      };
            bool operator==(const iterator& other ){return begin_iter1 == other.begin_iter1;}
            bool operator!=(const iterator& other ){return begin_iter1 != other.begin_iter1;}
            auto operator *()                       {return *begin_iter1;}
        };
        iterator begin() const {return iterator(container1.begin(), container1.end(), function1);}
        iterator end()   const {return iterator(container1.end(), container1.end(), function1);}
    };




}




#endif //UNTITLED11_FILTERFALSE_HPP

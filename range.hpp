//
// Created by dor on 22/07/2020.
//

#ifndef UNTITLED11_RANGE_HPP
#define UNTITLED11_RANGE_HPP
#include <iostream>
namespace itertools{
    /**
     * Class range:
     * input - start, end
     * Represents range of numbers [start,end) in "like-container" form AKA iterable.
     */
    class range{
        int s_range; //staring index of range.
        int e_range; //ending  index of range.
    public:
        /**
         * cptr
         * @param s - start of the range
         * @param e -   end of the range
         */
        range(int s , int e ): s_range(s),e_range(e){}

        /**
         * inner class - iterator.
         * Need to implement:
         * **. operator: =        copy cptr (xxx not needed here since there is no actual data.)
         *
         * 1. operator: ++       increment
         * 2. operator: == , !=  compare
         * 3. operator: *        access value
         */
        class iterator{
            int cur_ind; // current pointer.
        public:
            explicit iterator(int it = 0):cur_ind(it){};
            iterator(const iterator& other) = default;  /// see why its needed
            // ()++
            // increment and then return the value.
            // returns a reference of the class obj.
            iterator& operator++(){cur_ind++; return *this;};
            // ++()
            // return a copy of the current state of this class object and increment the actual
            // class object. returns a copy of iterator before incrementing.
            iterator operator++(int) { iterator temp_it = *this; cur_ind++; return temp_it;};
            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->cur_ind = other.cur_ind;
                }   return *this;
            };
            bool operator==(const iterator& other )const{return cur_ind == other.cur_ind;}
            bool operator!=(const iterator& other )const{return cur_ind != other.cur_ind;}
            int operator *()                       const{return cur_ind;}

        };


        iterator begin() const {return iterator(s_range);}
        iterator end  () const {return iterator(e_range);}
        typedef int	value_type; //used to determine the value type of range which is int.
    };
}
#endif //UNTITLED11_RANGE_HPP

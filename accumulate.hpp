//
// Created by dor on 22/07/2020.
//

#ifndef UNTITLED11_ACCUMULATE_HPP
#define UNTITLED11_ACCUMULATE_HPP


namespace itertools {
    /**
     * function adds two types of values.
     */
    typedef struct {
    public:
        template<typename P>
        P operator() (P p1 ,P p2) const {return p1+p2;} //default set to adds two template values.
    } Plus;


    template<typename CONTAINER,typename FUNCTION = Plus>
    /**
     *
     * @tparam CONTAINER - type of container.
     * @tparam FUNCTION  - function Plus.
     */
    class accumulate{
        CONTAINER& container;
        FUNCTION&  function;
        //getting the value type of elements in the container .
        typedef typename CONTAINER::value_type value_type;
    public:
        explicit accumulate(CONTAINER& cont ,  FUNCTION func = Plus()):container(cont),function(func){}
        explicit accumulate(CONTAINER&& cont,  FUNCTION func = Plus()):container(cont),function(func){}
        //creating iterator class-> making accumulate iterable.
        /**
         * inner class - iterator.
         * Need to implement:
           ------------------
         * 1. operator: ++       increment
         * 2. operator: == , !=  compare
         * 3. operator: *        access value
         * 4. operator: =        copy
         */
        class iterator{
            typename CONTAINER::iterator   begin_iter;
            typename CONTAINER::iterator   end_iter;
            typename CONTAINER::value_type sum;
            FUNCTION function;
        public:
            // cstr getting the container begin, end iterator pointer.
            // assign sum to be equal to the value of the container first element.
            explicit iterator(typename CONTAINER::iterator begin_iter,
                              typename CONTAINER::iterator end_iter,
                              FUNCTION function):begin_iter(begin_iter),end_iter(end_iter),function(function){
                if(begin_iter!=end_iter) {
                    this->sum = *begin_iter; // container is not empty. -> set sum to first element value.

                }
            };


            //first increment then return value. ++i
            iterator& operator++(){
                ++begin_iter;
                if(begin_iter != end_iter)
                    sum = function(sum, *begin_iter);
                return *this;
            };
            //return value before icrement. i++
            iterator operator++(int) {iterator temp_it = *this; ++(*this); return temp_it;    };
            bool operator==(const iterator& other )const{return begin_iter == other.begin_iter;}
            bool operator!=(const iterator& other )const{return begin_iter != other.begin_iter;}
            auto operator *()                       {return sum;}
            iterator& operator=(const iterator &other){
                if(this != &other) {
                    this->sum         = other.sum;
                    this->begin_iter  = other.begin_iter;
                    this->end_iter    = other.end_iter;
                    this->function    = other.function;
                }
                return *this;
            }
        };

        iterator begin() const {return iterator(container.begin(), container.end(), function);}
        iterator end()   const {return iterator(container.end(), container.end(), function);}
    };
}

#endif //UNTITLED11_ACCUMULATE_HPP

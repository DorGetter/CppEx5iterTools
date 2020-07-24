//
// Created by dor on 22/07/2020.
//

#ifndef UNTITLED11_COMPRESS_HPP
#define UNTITLED11_COMPRESS_HPP
namespace itertools{

    template <typename CONTAINER , typename CONTAINER_B>
    class compress{

        CONTAINER& container1;
        CONTAINER_B& container_b;
        typedef typename CONTAINER::value_type value_type;
    public:
        compress(CONTAINER&  container1 , CONTAINER_B&  container_b ) :container1(container1),container_b(container_b){}
        compress(CONTAINER&  container1 , CONTAINER_B&& container_b ) :container1(container1),container_b(container_b){}
        compress(CONTAINER&& container1 , CONTAINER_B&  container_b ) :container1(container1),container_b(container_b){}
        compress(CONTAINER&& container1 , CONTAINER_B&& container_b ) :container1(container1),container_b(container_b){}

        class iterator{
            typename CONTAINER::iterator   cont_begin_iter1;
            typename CONTAINER::iterator   cont_end_iter1;
            typename CONTAINER_B::iterator bool_begin_iter1;

        public:
            explicit iterator(typename CONTAINER::iterator begin,
                              typename CONTAINER::iterator end,
                              typename CONTAINER_B::iterator b_begin):
                    cont_begin_iter1(begin),cont_end_iter1(end),bool_begin_iter1(b_begin){
                while(cont_begin_iter1 != cont_end_iter1 && !(*bool_begin_iter1)){
                    ++cont_begin_iter1;++bool_begin_iter1;}

            };

            iterator& operator=(const iterator &other){
                if(this != &other)
                    this->cont_begin_iter1  = other.cont_begin_iter1;
                return *this;
            };
            //first increment then return value. ++i
            iterator& operator++(){
                ++cont_begin_iter1; ++bool_begin_iter1;
                while(cont_begin_iter1 != cont_end_iter1 && !(*bool_begin_iter1)){
                    ++cont_begin_iter1;++bool_begin_iter1;}
                return *this;
            };

            //return value before icrement. i++
            iterator operator++(int) {iterator temp_ = *this; ++(*this); return temp_;      };
            bool operator==(const iterator& other ){return cont_begin_iter1 == other.cont_begin_iter1;}
            bool operator!=(const iterator& other ){return cont_begin_iter1 != other.cont_begin_iter1;}
            auto operator *()                       {return *cont_begin_iter1;}
        };
        iterator begin() const {return iterator(container1.begin(), container1.end(), container_b.begin());}
        iterator end()   const {return iterator(container1.end(), container1.end(), container_b.end());}
    };




}



#endif //UNTITLED11_COMPRESS_HPP

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include "exceptions.h"

    const unsigned int SHRINKAGE_RATE = 2;
    const unsigned int EXPANSION_RATE = 2;
    const unsigned int INITIAL_CAPACITY = 10;

    template <class T>
    struct DynArray
    {
        T *array;
        unsigned int capacity;
        unsigned int occupancy;
        const unsigned int expansion_rate;

        explicit DynArray(const unsigned int &expansion_rate)
            : array(new T[INITIAL_CAPACITY]),
              capacity(INITIAL_CAPACITY),
              occupancy(0),
              expansion_rate(expansion_rate){};
        ~DynArray() { delete[] array; }

        DynArray(const DynArray &other) : array(new T[other.capacity]),
                                    capacity(other.capacity),
                                    occupancy(other.occupancy),
                                    expansion_rate(other.expansion_rate)

        {
            for (unsigned int i = 0; i < other.occupancy; i++)
            {
                array[i] = other.array[i];
            }
        }

        DynArray &operator=(const DynArray &other) = delete;

        T insert(const T &data);


        // friend std::ostream &operator<<(std::ostream &os, const DynArray &dyn_array)
        // {

        //     return os;
        // }
    };
    template <class T>
    T DynArray<T>::insert(const T &data)
    {
        if (occupancy == capacity - 1)
        { // About to expand

            T *new_array = new T[capacity * expansion_rate];
            for (unsigned int i = 0; i < occupancy; i++)
            {
                //try
                //{
                    new_array[i] = array[i]; // might throw bad alloc
                //}
                //catch (const std::bad_alloc &e)
                //{
                //     delete[] new_array;
                //     throw e;
                // }
            }
            delete[] array;
            array = new_array;

            //Allocated successfully
            capacity *= expansion_rate;
        }
        array[occupancy] = data;
        occupancy++;
        return array[(occupancy-1)];
    }

#endif //DYNAMIC_ARRAY_H
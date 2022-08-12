#include<iostream>
#include <memory>
#include<string>

#include"VectorString.h"

using namespace pic10b;

VectorString::VectorString() : vec_size(0), vec_capacity(1), ptr(new std::string[1]{ "\0" })
{
    //vector size set to zero, vector capacity set to one, and the string array with one input (the vec_capacity)
}


VectorString::VectorString(size_t x) : vec_size(x), vec_capacity(2 * x), ptr(new std::string[vec_capacity])
{
    //vector size set to the size_t input, vector capacity set to two times the input, 
    // and the string array with all the string variables set to the empty string
    for (size_t i = 0; i < vec_size; ++i)
    {
        ptr[i] = "";
    }
}


VectorString::VectorString(size_t x, std::string vec) : vec_size(x), vec_capacity(2 * x), ptr(new std::string[vec_capacity])
{
    vec_capacity = 2 * vec_capacity;
    //vector size set to the size_t input, vector capacity set to two times the input, 
    // and the string array storing all the string variables to the input string
    for (size_t i = 0; i < vec_size; ++i)
    {
        ptr[i] = vec;
    }

}


VectorString::VectorString(const VectorString& copyvec) : vec_size(copyvec.vec_size), vec_capacity(copyvec.vec_capacity)
{
    // to create the copy constructor, initialize the vec_size variable to the 
    // new size of the copy, capacity to the new vec_capacity the pointer to a new dynaimic array of 
    // size vec_capacity of the copy then copy over all strings including the null
    for (size_t i = 0; i < copyvec.vec_size; ++i)
    {
        ptr[i] = copyvec.ptr[i];
    }
}

VectorString::VectorString(VectorString&& copyvec) : VectorString() // invoke default constructor
{
    //For the move constructor, we simply swap the copies with the original pointer, vec_size, and vec_capacity
    std::swap(ptr, copyvec.ptr);
    std::swap(vec_size, copyvec.vec_size);
    std::swap(vec_capacity, copyvec.vec_capacity);
}

VectorString& VectorString::operator=(const VectorString& copyvec)
{
    if (this == &copyvec)
    {
        return *this; // self-assign, do nothing
    }
    auto old = std::make_unique<std::string[]>(vec_capacity);
    // allocate new array
    for (size_t i = 0; i < vec_size; ++i)
    { // copy over all chars including the null
        old[i] = ptr[i];
    }
    ptr.reset(new std::string[copyvec.vec_capacity]);
    for (size_t i = 0; i < copyvec.vec_size; ++i)
    { // copy over all chars including the null
        ptr[i] = copyvec.ptr[i];
    }
    vec_size = copyvec.vec_size; // update the size
    vec_capacity = copyvec.vec_capacity; //update the vec_capacity
    return *this;
}

VectorString& VectorString::operator=(VectorString&& copyvec)
{
    // just swap the state of the two objects,
    // assigned-to object takes ownership of rhs.ptr memory
    std::swap(ptr, copyvec.ptr);
    std::swap(vec_size, copyvec.vec_size);
    std::swap(vec_capacity, copyvec.vec_capacity);
    return *this;
}


/**THE FOLLOWING ARE MEMBER FUNCTION DEFINITIONS**/

size_t VectorString::size() const
{
    //For size we simpy return the vec_size variable of type int
    return vec_size;
}

size_t VectorString::capacity() const
{
    //For capacity we sipmly return the vec_capacity variable of type int
    return vec_capacity;
}

void VectorString::push_back(std::string element)
{
    //since a new element is being added when the push_back function is used, we have to make sure that we add one
    //to the vec_size for every element added
    vec_size++;
    //IMPORTANT NOTICE FROM ASSIGNMENT SHEET:
    // "Note that when the size exceeds the capacity then the elements are relocated to a
    // larger block of memory with twice the former capacity! The vector is indexed from 0."
    if (vec_size < vec_capacity) //IF statment for when the size of the vector is less than the capacity
    {
        //In this case, the push_back function works as it normally would
        ptr[vec_size - 1] = element;
    }
    else //ELSE statemtent for all other possibilities, including the possibility that vec_size > vec_capacity
    {
        std::unique_ptr<std::string[]> newptr(new std::string[2 * vec_capacity]); //create a new smart pointer to store more memory than the former
        //for loop to store the elements into the new array of larger memory
        for (size_t i = 0; i < vec_capacity; ++i)
        {
            newptr[i] = ptr[i];
        }
        // Then move all the elements over and add the new element (directly from assignment sheet)
        ptr = move(newptr);
        ptr[vec_size - 1] = element;
    }
}

void VectorString::pop_back()
{
    //(the value will remain there in memory but by changing the size, you 
    //can logically overwrite it if there is another insertion);
    //Therefore, all we do here is negatively increment from the size since 
    //the element will still be stored in memory

    vec_size--;
}

void VectorString::deleteAt(int index)
{
    //if the index is less than or equat to the vec_size, then remove the element at the requested index
    if (index <= vec_size)
    {
        for (int i = index; i < vec_size - 1; ++i)
        {
            ptr[i] = ptr[i + 1];
        }
    }
    else//simple exit return statement for all other cases (index should always be less than vec_size anyways)
    {
        return;
    }
    vec_size--; // decremement in the vec_size since we are removing an element.
}

void VectorString::insertAt(int index, std::string element)
{
    vec_size++; //when this function is called, we are adding an element, so the size increases each time
    if (vec_size < vec_capacity)
    {
        std::unique_ptr<std::string[]> newptr(new std::string[vec_capacity]); //create the new pointer and swap it with the original
        swap(ptr, newptr);
        for (int i = 0; i < index; ++i)
        {
            ptr[i] = newptr[i]; //inser all of the elements into the new array 
        }
        for (int i = index; i < vec_size - 1; ++i)
        {
            ptr[i + 1] = newptr[i];//then add the element at the requested index, while keeping the memory in the other array
        }
        ptr[index] = element;
    }
    else // for all other possibilities, the capacity of the new array is two times the old one, however the method to add the element remains the same
    {
        std::unique_ptr<std::string[]> newptr(new std::string[2 * vec_capacity]);
        swap(ptr, newptr);
        for (int i = 0; i < index; ++i)
        {
            ptr[i] = newptr[i];
        }
        for (int i = index; i < vec_size - 1; ++i)
        {
            ptr[i + 1] = newptr[i];
        }
        ptr[index] = element;//add the element at the given index
    }
}

const std::string& VectorString::at(int index) const
{
    return ptr[index]; // for both at functions just return the array index, whether it is const or not, but we have to cover both cases
}

std::string& VectorString::at(int index)
{
    return ptr[index]; // return the array index
}
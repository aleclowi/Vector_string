#ifndef _SPELLCHECK_
#define _SPELLCHECK_

#include <iostream>
#include <memory>
#include <string>

namespace pic10b
{
	class VectorString
	{
	public:

		/**
		Default constructor: that allocates a dynamic array of std::string of one element
		(so vec capacity is 1), but which has a vec size of 0.

		@param none
		*/
		VectorString();


		/**
		This constructor allocates a dynamic array of twice the input size

		@param accepts a variable of size_t as the input size
		*/
		VectorString(size_t x);


		/**
		This constructor that does the same as the above constructor with the input size and capacity,
		but which initializes all the string variables to the input string

		@param accepts a size and input string value
		*/
		VectorString(size_t x, std::string vec);


		/**
		Copy construtor: creating a newly constructed object into a copy of another

		@param accepts constructor reference
		*/
		VectorString(const VectorString& copyec);


		/**
		Move constructor: able to modify the value of the object

		@param accepts constructor reference
		*/
		VectorString(VectorString&& copyvec);

		VectorString& operator=(const VectorString& copyvec);//copy assignment

		VectorString& operator=(VectorString&& copyvec);//move assignemnt operator

		/**
		Destructor: clears up all of the object resources

		@param none
		*/
		//~VectorString();


		/**
		This function returns the size of the vector, same way as .size()

		@param none
		@return returns an int value of the size of the vector
		*/
		size_t size()const;

		/**
		This function returns the capacity of the vector, should be the same as size

		@param none
		@return returns an int value of the capacity of the vector
		*/
		size_t capacity() const;

		/**
		This function accepts a string that adds an element to the end of the vector if the
		capacity allows and otherwise creates a new dynamic array of twice the former capacity,
		moving all the elements over and adding the new element;

		@param the element of the vector type string
		@return type void, modifies the vector
		*/
		void push_back(std::string element);

		/**
		This function that ”removes” the last element of the vector by
		updating its vec size value (the value will remain there in memory but by changing
		the size, you can logically overwrite it if there is another insertion)

		@param requires call from the class, doesn't accept a value
		@return type void, modifies the vector
		*/
		void pop_back();

		/**
		This function that accepts an index value that removes the element at
		the given index from the vector, shifting elements backwards as appropriate (once
		again, the ”last” value will still be there in memory but can be overwritten);

		@param accepts a certain index value of the vector of type int
		@return type void, modifies the vector
		*/
		void deleteAt(int index);

		/**
		accepting an index and std::string value that inserts
		an element at the input position, moving elements (including the element previously
		there) forward and when this would push the vector size above the capacity then
		all the elements should be moved over to a new dynamic array of twice the former
		capacity before this process

		@param index of the vector of type int, and the type string element of the vector
		@return type void, modifies the vector
		*/
		void insertAt(int index, std::string element);

		/**
		This function, overloaded on const, accepts an index value that
		returns the element at the given index by reference / reference to const.

		@param the index value of the vector of type int
		@return the element of the string vector at the given index.
		*/
		const std::string& at(int index) const;

		std::string& at(int index);

	private:
		//the following variables are member variables representing certain facts about the vector array
		size_t vec_size; //size of the vector
		size_t vec_capacity; //size of underlying dynamic arry in memory
		std::unique_ptr<std::string[]> ptr; //member variable storing a smart pointer variable to the dynamic array

	};

};



#endif


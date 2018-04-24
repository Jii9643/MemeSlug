#pragma once
template <typename T>

class dArr
{
public: 
	dArr(unsigned cap = 5);
	dArr(const dArr& obj);
	~dArr();

	T& operator[](int index);
	void operator = (const T& obj);

	void add(const T element);
	void remove(int index);
	unsigned size() const; 
	void clear();



private:
	
	unsigned cap;                      //Dimensione array.
	unsigned nOfEl;                   
	T* *arr;

	void initialize(unsigned from);
	void expand();

};




template <typename T>
dArr<T>::dArr(unsigned cap)
{
	this->cap = cap;
	this->nOfEl = 0;
	this->arr = new T*[this->cap];

	this->initialize(0);
}

//Deep copying
template <typename T>
dArr<T>::dArr(const dArr& obj)
{
	this->cap = obj.cap;
	this->nOfEl = obj.nOfEl;
	this->arr = new T*[this->cap];

	for (size_t i = 0; i < this->nOfEl; i++)
	{
		this->arr[i] = new T(*obj.arr[i]);
	}

	this->initialize(this->nOfEl);
}

template <typename T>
dArr<T>::~dArr()
{
	for (size_t i = 0; i < this->nOfEl; i++)
	{
		delete this->arr[i];
	}
	delete[]this->arr;
}

template <typename T>
 T& dArr<T>::operator[](int index)
{
	 if (index < 0 || index >= this->nOfEl)
		 throw ("OUT OF BOUNDS EXEPTION!");

	 return *this->arr[index];
}

 template <typename T>
 void dArr<T>::operator = (const T& obj)
 {
	 for (size_t i = 0; i < this->nOfEl; i++)
	 {
		 delete this->arr[i];
	 }
	 delete[]this->arr;

	 this->cap = obj.cap;
	 this->nOfEl = obj.nOfEl;
	 this->arr = new T*[this->cap];

	 for (size_t i = 0; i < this->nOfEl; i++)
	 {
		 this->arr[i] = new T(*obj.arr[i]);
	 }

	 this->initialize(this->nOfEl);


 }

template <typename T>
void dArr<T>::initialize(unsigned from)
{
	for (size_t i = from; i < this->cap; i++)
	{
		this->arr[i] = nullptr;
	}
}

template <typename T>
void dArr<T>::expand()
{
	this->cap *= 2;

	T* *tempArr = new T*[this->cap];

	for (size_t i = 0; i < this->nOfEl; i++)
	{
		tempArr[i] = this->arr[i];
	}

	delete[]this->arr;

	this->arr = tempArr;

	initialize(this->nOfEl);
}

template <typename T>
void dArr<T>::add(const T element)
{
	if (this->nOfEl >= this->cap)
		this->expand();

	this->arr[this->nOfEl++] = new T(element);
}

template <typename T>
void dArr<T>::remove(int index)
{
	if (index < 0 || index >= this->nOfEl)
		throw ("OUT OF BOUNDS EXEPTION!");

	delete this->arr[index];

	this->arr[index] = this->arr[this->nOfEl - 1];

    this->arr[--nOfEl] = nullptr;
}

template <typename T>
unsigned dArr<T>::size() const
{
	return this->nOfEl;
}

template <typename T>
void dArr<T>::clear() 
{
	for (size_t i = 0; i < this->nOfEl; i++)
	{
		delete this->arr[i];
	}

	initialize(0);

	this->nOfEl = 0;
}
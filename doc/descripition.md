# Objective

- The objective of this page is to design and describe the class.


# Design a class for the first implementation

- The class has to have method to insert and find in multi_container

```cpp
   template< typename T >
   void insert( const T& object );

   template< typename T >
   std::optional< T > find( const T& filter );
```

- Probably will be necessary create a method to initialize the container inside multimap in the future

# Objective

 - Create a multiple container type because when it's necessary access multiple containers types or storage multiple type classes on cache, it's need pass all then by argument or create a class to group then together, the multiple type container will minimize this.
- The idea it's search and insert in container only by the value type on container.

## [Pipeline](./doc/pipeline.md)

## Usage
 - Initializing containers:

```CPP

   fsk::MultiContainer multiContainer;
   multiContainer.InsertTypeSlot< std::set< int8_t > >();
   multiContainer.InsertTypeSlot< std::unordered_set< int32_t > >();

```

- Insert new elements in, like in int8_t container:

```CPP

   multiContainer.Insert< int8_t >( 3 );
   multiContainer.Insert< int8_t >( 5 );
   multiContainer.Insert< int8_t >( 12 );

```

- Search for  elements in int8_t container for example:

```CPP

   const std::optinal< int32_t > value = multiContainer.Find< int8_t >( 3 );

```

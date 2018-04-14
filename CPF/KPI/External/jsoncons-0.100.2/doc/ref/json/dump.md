### `jsoncons::json::dump`, `jsoncons::json::dump_fragment`

```c++
template <class SAllocator>
void dump(std::basic_string<char_type,char_traits_type,SAllocator>& s) const; // (1)

template <class SAllocator>
void dump(std::basic_string<char_type,char_traits_type,SAllocator>& s, 
          const serialization_options& options) const; // (2)

void dump(std::ostream& os) const; // (3)

void dump(std::ostream<CharT> os, bool pprint) const; // (4)

void dump(std::ostream<CharT> os, const serialization_options& options) const; // (5)

void dump(std::ostream<CharT> os, const serialization_options& options, bool pprint) const; // (6)

void dump(basic_json_output_handler<char_type>& output_handler) const; // (7)

void dump_fragment(json_output_handler& handler) const; // (8)
```

(1) Inserts json value into string using default serialization_options.

(2) Inserts json value into string using specified [serialization_options](../serialization_options.md). 

(3) Inserts json value into stream with default serialization options. 

(4) Inserts json value into stream using default serialization options and pretty print flag. 

(5) Inserts json value into stream using specified [serialization_options](../serialization_options.md). 

(6) Inserts json value into stream using specified [serialization_options](../serialization_options.md) and pretty print flag. 

(7) Calls `begin_json()` on [output_handler](../json_output_handler.md), emits json value to the [output_handler](../json_output_handler.md), and calls `end_json()` on [output_handler](../json_output_handler.md). 

(8) Emits json value to the [output_handler](../json_output_handler.md) (does not call `begin_json()` or `end_json()`.)

### Examples

#### Dump json value to csv file

```c++
#include <jsoncons/json.hpp>
#include <jsoncons_ext/csv/csv_serializer.hpp>

using namespace jsoncons;

int main()
{
    const json books = json::parse(R"(
    [
        {
            "title" : "Kafka on the Shore",
            "author" : "Haruki Murakami",
            "price" : 25.17
        },
        {
            "title" : "Women: A Novel",
            "author" : "Charles Bukowski",
            "price" : 12.00
        },
        {
            "title" : "Cutter's Way",
            "author" : "Ivan Passer"
        }
    ]
    )");

    csv_parameters params;
    params.column_names("author,title,price");

    csv_serializer serializer(std::cout, params);

    books.dump(serializer);
}
```

Output:

```csv
author,title,price
Haruki Murakami,Kafka on the Shore,25.17
Charles Bukowski,Women: A Novel,12.0
Ivan Passer,Cutter's Way,
```

#### Dump json fragments into a larger document

```c++
#include <jsoncons/json.hpp>

using namespace jsoncons;

int main()
{
    const json some_books = json::parse(R"(
    [
        {
            "title" : "Kafka on the Shore",
            "author" : "Haruki Murakami",
            "price" : 25.17
        },
        {
            "title" : "Women: A Novel",
            "author" : "Charles Bukowski",
            "price" : 12.00
        }
    ]
    )");

    const json more_books = json::parse(R"(
    [
        {
            "title" : "A Wild Sheep Chase: A Novel",
            "author" : "Haruki Murakami",
            "price" : 9.01
        },
        {
            "title" : "Cutter's Way",
            "author" : "Ivan Passer",
            "price" : 8.00
        }
    ]
    )");

    json_serializer serializer(std::cout, true); // pretty print
    serializer.begin_json();
    serializer.begin_array();
    for (const auto& book : some_books.array_range())
    {
        book.dump_fragment(serializer);
    }
    for (const auto& book : more_books.array_range())
    {
        book.dump_fragment(serializer);
    }
    serializer.end_array();
    serializer.end_json();
}
```

Output:

```json
[
    {
        "author": "Haruki Murakami",
        "price": 25.17,
        "title": "Kafka on the Shore"
    },
    {
        "author": "Charles Bukowski",
        "price": 12.0,
        "title": "Women: A Novel"
    },
    {
        "author": "Haruki Murakami",
        "price": 9.01,
        "title": "A Wild Sheep Chase: A Novel"
    },
    {
        "author": "Ivan Passer",
        "price": 8.0,
        "title": "Cutter's Way"
    }
]
```

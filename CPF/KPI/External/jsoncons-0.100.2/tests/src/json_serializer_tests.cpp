// Copyright 2013 Daniel Parker
// Distributed under Boost license

#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <jsoncons/json.hpp>
#include <jsoncons/json_serializer.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>

using namespace jsoncons;
using boost::numeric::ublas::matrix;

BOOST_AUTO_TEST_SUITE(json_serializer_tests)

BOOST_AUTO_TEST_CASE(test_byte_string_serialization)
{
    const uint8_t bs[] = {'H','e','l','l','o'};
    json j(bs,sizeof(bs));

    std::ostringstream os;
    os << j;

    std::string expected; 
    expected.push_back('\"');
    encode_base64url(bs,bs+sizeof(bs),expected);
    expected.push_back('\"');

    //std::cout << expected << " " << os.str() << std::endl;

    BOOST_CHECK(expected == os.str());
}

BOOST_AUTO_TEST_CASE(test_direct_serialization)
{
    matrix<double> A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    serialization_options options;

    std::ostringstream os1;

    json_serializer os(os1, options, true); // pretty printing
    os.begin_json();
    os.begin_array();
    for (size_t i = 0; i < A.size1(); ++i)
    {
        os.begin_array();
        for (size_t j = 0; j < A.size2(); ++j)
        {
            os.double_value(A(i, j));
        }
        os.end_array();
    }
    os.end_array();
    os.end_json();

    std::string expected1 = R"([
    [1.0,2.0],
    [3.0,4.0]
])";
    BOOST_CHECK_EQUAL(expected1,os1.str());
}

BOOST_AUTO_TEST_CASE(test_serialization_1)
{
    json val = json::parse(R"(
    {
        "header" : {"properties": {}},
        "data":
        {
            "tags" : [],
            "id" : [1,2,3],
            "item": [[1,2,3]]    
        }
    }
)");

    std::string expected1 = R"({
    "data": {
        "id": [1,2,3],
        "item": [
            [1,2,3]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os1;
    os1 << pretty_print(val);
    BOOST_CHECK_EQUAL(expected1,os1.str());

    serialization_options options2 ;
    options2 .array_array_split_lines(line_split_kind::same_line);
    std::string expected2 = R"({
    "data": {
        "id": [1,2,3],
        "item": [[1,2,3]],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os2;
    os2 << pretty_print(val,options2 );
    BOOST_CHECK_EQUAL(expected2,os2.str());

    serialization_options options3;
    options3.array_array_split_lines(line_split_kind::new_line);
    std::string expected3 = R"({
    "data": {
        "id": [1,2,3],
        "item": [
            [1,2,3]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os3;
    os3 << pretty_print(val,options3);
    BOOST_CHECK_EQUAL(expected3,os3.str());

    serialization_options options4;
    options4.array_array_split_lines(line_split_kind::multi_line);
    std::string expected4 = R"({
    "data": {
        "id": [1,2,3],
        "item": [
            [
                1,
                2,
                3
            ]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os4;
    os4 << pretty_print(val,options4);
    BOOST_CHECK_EQUAL(expected4,os4.str());

    serialization_options options5;
    options5.object_array_split_lines(line_split_kind::same_line);
    std::string expected5 = R"({
    "data": {
        "id": [1,2,3],
        "item": [
            [1,2,3]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os5;
    os5 << pretty_print(val,options5);
    BOOST_CHECK_EQUAL(expected5,os5.str());

    serialization_options options6;
    options6.object_array_split_lines(line_split_kind::new_line);
    std::string expected6 = R"({
    "data": {
        "id": [
            1,2,3
        ],
        "item": [
            [1,2,3]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os6;
    os6 << pretty_print(val,options6);
    BOOST_CHECK_EQUAL(expected6,os6.str());

    serialization_options options7;
    options7.object_array_split_lines(line_split_kind::multi_line);
    std::string expected7 = R"({
    "data": {
        "id": [
            1,
            2,
            3
        ],
        "item": [
            [1,2,3]
        ],
        "tags": []
    },
    "header": {
        "properties": {}
    }
})";
    std::ostringstream os7;
    os7 << pretty_print(val,options7);
    BOOST_CHECK_EQUAL(expected7,os7.str());
}

BOOST_AUTO_TEST_SUITE_END()



// Copyright 2017 Daniel Parker
// Distributed under Boost license

#ifdef __linux__
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <ctime>
#include <new>
#include <codecvt>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>

using namespace jsoncons;

BOOST_AUTO_TEST_SUITE(jsonpointer_tests)

// Example from RFC 6901
const json example = json::parse(R"(
   {
      "foo": ["bar", "baz"],
      "": 0,
      "a/b": 1,
      "c%d": 2,
      "e^f": 3,
      "g|h": 4,
      "i\\j": 5,
      "k\"l": 6,
      " ": 7,
      "m~n": 8
   }
)");

void check_get(const std::string& pointer, const json& expected)
{

    json result;
    jsonpointer::jsonpointer_errc ec;

    std::tie(result,ec) = jsonpointer::get(example,pointer);
    BOOST_CHECK_EQUAL(ec,jsonpointer::jsonpointer_errc());
    BOOST_CHECK_EQUAL(expected,result);
}

void check_contains(const std::string& pointer, bool expected)
{

    bool result = jsonpointer::contains(example,pointer);
    BOOST_CHECK_EQUAL(expected,result);
}

void check_add(json& example, const std::string& path, const json& value, const json& expected)
{
    jsonpointer::jsonpointer_errc ec = jsonpointer::insert_or_assign(example, path, value);
    BOOST_CHECK_EQUAL(ec,jsonpointer::jsonpointer_errc());
    BOOST_CHECK_EQUAL(expected, example);
}

void check_replace(json& example, const std::string& path, const json& value, const json& expected)
{
    jsonpointer::jsonpointer_errc ec = jsonpointer::replace(example, path, value);
    BOOST_CHECK_EQUAL(ec,jsonpointer::jsonpointer_errc());
    BOOST_CHECK_EQUAL(expected, example);
}

void check_remove(json& example, const std::string& path, const json& expected)
{
    jsonpointer::jsonpointer_errc ec = jsonpointer::remove(example, path);
    BOOST_CHECK_EQUAL(ec,jsonpointer::jsonpointer_errc());
    BOOST_CHECK_EQUAL(expected, example);
}

BOOST_AUTO_TEST_CASE(test_jsonpointer)
{
    check_contains("",true);
    check_contains("/foo",true);
    check_contains("/foo/0",true);
    check_contains("/",true);
    check_contains("/a~1b",true);
    check_contains("/c%d",true);
    check_contains("/e^f",true);
    check_contains("/g|h",true);
    check_contains("/i\\j",true);
    check_contains("/k\"l",true);
    check_contains("/ ",true);
    check_contains("/m~0n",true);

    check_get("",example);
    check_get("/foo",json::parse("[\"bar\", \"baz\"]"));
    check_get("/foo/0",json("bar"));
    check_get("/",json(0));
    check_get("/a~1b",json(1));
    check_get("/c%d",json(2));
    check_get("/e^f",json(3));
    check_get("/g|h",json(4));
    check_get("/i\\j",json(5));
    check_get("/k\"l",json(6));
    check_get("/ ",json(7));
    check_get("/m~0n",json(8));
}

// add

BOOST_AUTO_TEST_CASE(test_add_object_member)
{
    json example = json::parse(R"(
    { "foo": "bar"}
    )");

    const json expected = json::parse(R"(
    { "foo": "bar", "baz" : "qux"}
    )");

    check_add(example,"/baz", json("qux"), expected);
}

BOOST_AUTO_TEST_CASE(test_add_array_element)
{
    json example = json::parse(R"(
    { "foo": [ "bar", "baz" ] }
    )");

    const json expected = json::parse(R"(
    { "foo": [ "bar", "qux", "baz" ] }
    )");

    check_add(example,"/foo/1", json("qux"), expected);
}

BOOST_AUTO_TEST_CASE(test_add_array_value)
{
    json example = json::parse(R"(
     { "foo": ["bar"] }
    )");

    const json expected = json::parse(R"(
    { "foo": ["bar", ["abc", "def"]] }
    )");

    check_add(example,"/foo/-", json::array({"abc", "def"}), expected);
}

// remove

BOOST_AUTO_TEST_CASE(test_remove_object_member)
{
    json example = json::parse(R"(
    { "foo": "bar", "baz" : "qux"}
    )");

    const json expected = json::parse(R"(
        { "foo": "bar"}
    )");

    check_remove(example,"/baz", expected);
}

BOOST_AUTO_TEST_CASE(test_remove_array_element)
{
    json example = json::parse(R"(
        { "foo": [ "bar", "qux", "baz" ] }
    )");

    const json expected = json::parse(R"(
        { "foo": [ "bar", "baz" ] }
    )");

    check_remove(example,"/foo/1", expected);
}

// replace

BOOST_AUTO_TEST_CASE(test_replace_object_value)
{
    json example = json::parse(R"(
        {
          "baz": "qux",
          "foo": "bar"
        }
    )");

    const json expected = json::parse(R"(
        {
          "baz": "boo",
          "foo": "bar"
        }
    )");

    check_replace(example,"/baz", json("boo"), expected);
}

BOOST_AUTO_TEST_CASE(test_replace_array_value)
{
    json example = json::parse(R"(
        { "foo": [ "bar", "baz" ] }
    )");

    const json expected = json::parse(R"(
        { "foo": [ "bar", "qux" ] }
    )");

    check_replace(example,"/foo/1", json("qux"), expected);
}

BOOST_AUTO_TEST_SUITE_END()





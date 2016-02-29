#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

[type:Human]
    [field:name:string:""]
    [field:age:int:0]
    
[human]
    [name:"steve"]
    [age:10]

namespace lex = boost::spirit::lex;

template <typename Lexer>
struct derp : lex::lexer<Lexer>
{
    derp()
        : word("[^ \t\n]+")
        , eol("\n")
        , any(".")
    {
        using boost::spirit::lex::_start;
        using boost::spirit::lex::_end;
        using boost::phoenix::ref;

        // associate tokens with the lexer
        this->self
            =   word  [++ref(w), ref(c) += distance(_start, _end)]
            |   eol   [++ref(c), ++ref(l)]
            |   any   [++ref(c)]
            ;
    }
        
    lex::token_def<> word, eol, any;
};

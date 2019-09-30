
#ifndef TOKENENUM_H
#define TOKENENUM_H

#include <string>

class TokenEnum
{
public:
	enum Type
	{ 
		voidKeyTk,		  // void
		intKeyTk,    	  // int
		returnKeyTk, 	  // return
		printKeyTk,  	  // print
		scanKeyTk, 		  // scan
		programKeyTk,	  // program
		iterKeyTk,		  // iter
		varKeyTk,		  // var
		condKeyTk,		  // cond
		thenKeyTk,		  // then
		letKeyTk,		  // let
		eq_tk,            // =
		lt_tk,            // <
		lgt_tk,           // >
		colon_tk,         // :
		plus_tk,          // +
		minus_tk,         // -
		asterisk_tk,      // *
		slash_tk,         // /
		pct_tk,           // %
		dot_tk,           // .
		lpar_tk,          // (
		rpar_tk,          // )
		comma_tk,         // ,
		lbrace_tk,        // {
		rbrace_tk,        // }
		semicln_tk,       // ;
		lbkt_tk,          // [
		rbkt_tk,          // ]
		id_tk,            // (identifier)
		int_tk,           // (integer)
		commentTk,        // (comment) start(&) 
		eofTk             // End of File 
	};
	Type t_;
	TokenEnum(Type t) : t_(t) {}
	operator Type () const { return t_; }
	static std::string getTokenEnumString(TokenEnum type);
	static TokenEnum getTokenEnumFromString(std::string str);
	static TokenEnum getTokenEnum(std::string str);
	std::string toString();
};

static bool check_alpha(std::string);
static bool is_id(std::string);
static bool is_int(std::string);


#endif /* TOKENENUM_H */

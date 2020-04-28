# Blue Print Grammar

## EBNF

expr = (identifier “=“ ) equality

equality = relation ( “&&” relation | “||” relation)

relation = sum ( [ "==", <", "<=", ">=", ">" ] sum )*

sum = mul ( “+” mul | “-“ mul )*

mul = primary ( “*” unary | “/“  unary | “%” unary )*

unary = ( "+" | "-" ) primary

primary = identifier ( “.” identifier( “(“ args “)” ) )* | “(“ equality “)”

args = sum ( “,” sum )*

identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ "f"? )
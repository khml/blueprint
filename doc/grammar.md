# Blue Print Grammar

## EBNF

expr = (identifier “=“ ) equality

equality = relation ( “&&” relation | “||” relation)

relation = sum (“比較演算子“ sum )*

sum = mul ( “+” mul | “-“ mul )*

mul = primary ( “*” unary | “/“  unary | “%” unary )*

unary = ( "+" | "-" ) primary

primary = identifier ( “.” identifier( “(“ args “)” ) )* | “(“ equality “)”

args = sum ( “,” sum )*
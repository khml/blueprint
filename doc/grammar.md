# Blue Print Grammar

## EBNF

expr = mul ( “+” mul | “-“ mul )* | identifier “=“ expr

mul = primary ( “*” primary | “/“  primary | “%” primary )*

primary = identifier ( “.” identifier( “(“ args “)” ) )* | “(“ expr “)”


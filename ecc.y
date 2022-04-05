%{
#include <stdio.h>
#include <math.h>
#include <string.h>

int yylex();
void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
%}

%union {
    char _char;
    short _short;
    int _int;
    long _long;
    float _float;
    double _double;
}

%token NUMBER
%type<command> 

%%

command :
    | '\n'
    | exp {
    if ($1.type == INTEGER) {
        printf("%lld\n", $1.val.intval);
    } else if ($1.type == FLOAT) {
        char buf[0x10] = {0};
        sprintf(buf, "%lf", $1.val.floatval);
        for(int i = strlen(buf) - 1; buf[i] == '0'; i--)
            buf[i] = '\0';
        printf("%s\n", buf);
    }
};

exp : exp '+' term {
    if ($1.type == INTEGER && $3.type == INTEGER) {
        $$.type = INTEGER;
        $$.val.intval = $1.val.intval + $3.val.intval;
    } else if ($1.type == INTEGER && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.intval + $3.val.floatval;
    } else if ($1.type == FLOAT && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval + $3.val.intval;
    } else if ($1.type == FLOAT && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval + $3.val.floatval;
    }
}
    | exp '-' term {
    if ($1.type == INTEGER && $3.type == INTEGER) {
        $$.type = INTEGER;
        $$.val.intval = $1.val.intval - $3.val.intval;
    } else if ($1.type == INTEGER && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.intval - $3.val.floatval;
    } else if ($1.type == FLOAT && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval - $3.val.intval;
    } else if ($1.type == FLOAT && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval - $3.val.floatval;
    }
}
    | term { $$ = $1; }
    ;

term : term '*' power {
    if ($1.type == INTEGER && $3.type == INTEGER) {
        $$.type = INTEGER;
        $$.val.intval = $1.val.intval * $3.val.intval;
    } else if ($1.type == INTEGER && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.intval * $3.val.floatval;
    } else if ($1.type == FLOAT && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval * $3.val.intval;
    } else if ($1.type == FLOAT && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval * $3.val.floatval;
    }
}
    | term '/' power {
    if ($1.type == INTEGER && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = 1.0 * $1.val.intval / $3.val.intval;
    } else if ($1.type == INTEGER && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.intval / $3.val.floatval;
    } else if ($1.type == FLOAT && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval / $3.val.intval;
    } else if ($1.type == FLOAT && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = $1.val.floatval / $3.val.floatval;
    }
}
    | power { $$ = $1;}
    ;

power: factor '^' power {
    if ($1.type == INTEGER && $3.type == INTEGER) {
        $$.type = INTEGER;
        $$.val.intval = pow($1.val.intval, $3.val.intval);
    } else if ($1.type == INTEGER && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = pow($1.val.intval, $3.val.floatval);
    } else if ($1.type == FLOAT && $3.type == INTEGER) {
        $$.type = FLOAT;
        $$.val.floatval = pow($1.val.floatval, $3.val.intval);
    } else if ($1.type == FLOAT && $3.type == FLOAT) {
        $$.type = FLOAT;
        $$.val.floatval = pow($1.val.floatval, $3.val.floatval);
    }
}
    | factor { $$ = $1; }
    ;

factor : NUMBER { $$ = $1; }
    | '(' exp ')' { $$ = $2; }
    ;

%%

int main ()
{
    while(1)
        yyparse();
    return 0;
}
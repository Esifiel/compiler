; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@stdin = external global i8*
@MAXLEN = private global i32 1000
@MAXN = private global i32 100

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @puts(i8*)

declare i32 @strlen(i8*)

declare i32 @strcmp(i8*, i8*)

declare i8* @strcpy(i8*, i8*)

declare i8* @calloc(i64, i64)

declare i64 @read(i32, i8*, i64)

declare i8* @fgets(i8*, i64, i8*)

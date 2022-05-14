; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@stdin = external global i8*
@a = private global i32 1
@"%d\0A" = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @puts(i8*)

declare i32 @strlen(i8*)

declare i32 @strcmp(i8*, i8*)

declare i8* @strcpy(i8*, i8*)

declare i8* @calloc(i64, i64)

declare i8* @malloc(i64)

declare i64 @read(i32, i8*, i64)

declare i8* @fgets(i8*, i64, i8*)

declare i32 @atoi(i8*)

declare void @free(i8*)

declare i32 @exit(i32)

define i32 @main() {
entry:
  %0 = load i32, i32* @a
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%d\0A", i32 0, i32 0), i32 %0)
  ret i32 0
}

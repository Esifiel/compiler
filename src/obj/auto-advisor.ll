; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

%stu = type { i32, double, [16 x i8] }

@stdin = external global i8*
@"hello, world" = private constant [13 x i8] c"hello, world\00"
@mingming = private constant [9 x i8] c"mingming\00"
@"%d\0A%lf\0A%s\0A" = private constant [11 x i8] c"%d\0A%lf\0A%s\0A\00"

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

define i32 @main() {
entry:
  %hello = alloca i8*
  store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @"hello, world", i32 0, i32 0), i8** %hello
  %buf = alloca [16 x i8]
  %xiaoming = alloca %stu*
  %0 = call i8* @malloc(i64 32)
  %1 = bitcast i8* %0 to %stu*
  store %stu* %1, %stu** %xiaoming
  %2 = load %stu*, %stu** %xiaoming
  %3 = getelementptr %stu, %stu* %2, i32 0, i32 0
  store i32 2333, i32* %3
  %4 = load %stu*, %stu** %xiaoming
  %5 = getelementptr %stu, %stu* %4, i32 0, i32 1
  store double 3.500000e+00, double* %5
  %6 = load %stu*, %stu** %xiaoming
  %7 = getelementptr %stu, %stu* %6, i32 0, i32 2
  %8 = getelementptr [16 x i8], [16 x i8]* %7, i32 0, i32 0
  %9 = call i8* @strcpy(i8* %8, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @mingming, i32 0, i32 0))
  %10 = load %stu*, %stu** %xiaoming
  %11 = getelementptr %stu, %stu* %10, i32 0, i32 0
  %12 = load i32, i32* %11
  %13 = load %stu*, %stu** %xiaoming
  %14 = getelementptr %stu, %stu* %13, i32 0, i32 1
  %15 = load double, double* %14
  %16 = load %stu*, %stu** %xiaoming
  %17 = getelementptr %stu, %stu* %16, i32 0, i32 2
  %18 = getelementptr [16 x i8], [16 x i8]* %17, i32 0, i32 0
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"%d\0A%lf\0A%s\0A", i32 0, i32 0), i32 %12, double %15, i8* %18)
  %20 = getelementptr [16 x i8], [16 x i8]* %buf, i64 0, i64 1
  store i8 99, i8* %20
  ret i32 0
}

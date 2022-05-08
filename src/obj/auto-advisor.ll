; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

%stu = type { i32, double, [16 x i8] }

@stdin = external global i8*
@"hello, world" = private constant [13 x i8] c"hello, world\00"
@mingming = private constant [9 x i8] c"mingming\00"
@"not mingming" = private constant [13 x i8] c"not mingming\00"
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
  %i = alloca i32
  %xiaoming = alloca [16 x %stu]
  %0 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 0
  %1 = getelementptr %stu, %stu* %0, i32 0, i32 0
  store i32 2333, i32* %1
  %2 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 1
  %3 = getelementptr %stu, %stu* %2, i32 0, i32 1
  store double 3.500000e+00, double* %3
  %4 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 2
  %5 = getelementptr %stu, %stu* %4, i32 0, i32 2
  %6 = getelementptr [16 x i8], [16 x i8]* %5, i32 0, i32 0
  %7 = call i8* @strcpy(i8* %6, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @mingming, i32 0, i32 0))
  %8 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 1
  %9 = getelementptr %stu, %stu* %8, i32 0, i32 2
  %10 = getelementptr [16 x i8], [16 x i8]* %9, i32 0, i32 0
  %11 = call i8* @strcpy(i8* %10, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @"not mingming", i32 0, i32 0))
  %12 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 0
  %13 = getelementptr %stu, %stu* %12, i32 0, i32 0
  %14 = load i32, i32* %13
  %15 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 1
  %16 = getelementptr %stu, %stu* %15, i32 0, i32 1
  %17 = load double, double* %16
  %18 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 2
  %19 = getelementptr %stu, %stu* %18, i32 0, i32 2
  %20 = getelementptr [16 x i8], [16 x i8]* %19, i32 0, i32 0
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"%d\0A%lf\0A%s\0A", i32 0, i32 0), i32 %14, double %17, i8* %20)
  %22 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 2
  %23 = getelementptr %stu, %stu* %22, i32 0, i32 0
  %24 = load i32, i32* %23
  %25 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 0
  %26 = getelementptr %stu, %stu* %25, i32 0, i32 1
  %27 = load double, double* %26
  %28 = getelementptr [16 x %stu], [16 x %stu]* %xiaoming, i64 0, i64 1
  %29 = getelementptr %stu, %stu* %28, i32 0, i32 2
  %30 = getelementptr [16 x i8], [16 x i8]* %29, i32 0, i32 0
  %31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"%d\0A%lf\0A%s\0A", i32 0, i32 0), i32 %24, double %27, i8* %30)
  %32 = getelementptr [16 x i8], [16 x i8]* %buf, i64 0, i64 1
  store i8 99, i8* %32
  ret i32 0
}

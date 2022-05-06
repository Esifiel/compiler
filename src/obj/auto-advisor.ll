; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@stdin = external global i8*
@MAXLEN = private constant i32 1000
@MAXN = private constant i32 100
@name = private global [100 x [10 x i8]] zeroinitializer
@credit = private global [100 x i32] zeroinitializer
@grade = private global [100 x i8] zeroinitializer
@0 = private constant [1 x i8] zeroinitializer
@"GPA: %.1f\0A" = private constant [11 x i8] c"GPA: %.1f\0A\00"
@"Hours Attempted: %u\0A" = private constant [21 x i8] c"Hours Attempted: %u\0A\00"
@"Hours Completed: %u\0A" = private constant [21 x i8] c"Hours Completed: %u\0A\00"
@"Credits Remaining: %u\0A\0A" = private constant [24 x i8] c"Credits Remaining: %u\0A\0A\00"
@"Possible Courses to Take Next" = private constant [30 x i8] c"Possible Courses to Take Next\00"
@"None - Congratulations!" = private constant [24 x i8] c"None - Congratulations!\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @puts(i8*)

declare i32 @strlen(i8*)

declare i32 @strcmp(i8*, i8*)

declare i8* @strcpy(i8*, i8*)

declare i8* @calloc(i64, i64)

declare i64 @read(i32, i8*, i64)

declare i8* @fgets(i8*, i64, i8*)

declare i32 @atoi(i8*)

define i32 @split(i8* %src, i8 %delim, i8** %vec) {
entry:
  %src1 = alloca i8*
  store i8* %src, i8** %src1
  %delim2 = alloca i8
  store i8 %delim, i8* %delim2
  %vec3 = alloca i8**
  store i8** %vec, i8*** %vec3
  %cnt = alloca i32
  store i32 0, i32* %cnt
  %len = alloca i32
  %0 = load i8*, i8** %src1
  %1 = call i32 @strlen(i8* %0)
  store i32 %1, i32* %len
  %p = alloca i32
  store i32 0, i32* %p
  %q = alloca i32
  store i32 0, i32* %q
  br label %while.cond

while.cond:                                       ; preds = %while.out6, %entry
  %2 = load i32, i32* %len
  %3 = load i32, i32* %p
  %4 = icmp slt i32 %3, %2
  %5 = load i32, i32* %len
  %6 = load i32, i32* %q
  %7 = icmp slt i32 %6, %5
  %8 = zext i1 %7 to i64
  %9 = icmp ne i64 %8, 0
  %10 = zext i1 %4 to i64
  %11 = icmp ne i64 %10, 0
  %12 = and i1 %11, %9
  br i1 %12, label %while.loop, label %while.out

while.loop:                                       ; preds = %while.cond
  br label %while.cond4

while.out:                                        ; preds = %while.cond
  %13 = load i32, i32* %cnt
  ret i32 %13

while.cond4:                                      ; preds = %while.loop5, %while.loop
  %14 = load i8, i8* %delim2
  %15 = load i8*, i8** %src1
  %16 = load i32, i32* %q
  %17 = getelementptr i8, i8* %15, i32 %16
  %18 = load i8, i8* %17
  %19 = icmp ne i8 %18, %14
  %20 = load i32, i32* %len
  %21 = load i32, i32* %q
  %22 = icmp slt i32 %21, %20
  %23 = zext i1 %22 to i64
  %24 = icmp ne i64 %23, 0
  %25 = zext i1 %19 to i64
  %26 = icmp ne i64 %25, 0
  %27 = and i1 %26, %24
  br i1 %27, label %while.loop5, label %while.out6

while.loop5:                                      ; preds = %while.cond4
  %28 = load i32, i32* %q
  %29 = add i32 %28, 1
  store i32 %29, i32* %q
  br label %while.cond4

while.out6:                                       ; preds = %while.cond4
  %30 = load i8*, i8** %src1
  %31 = load i32, i32* %q
  %32 = getelementptr i8, i8* %30, i32 %31
  store i8 0, i8* %32
  %33 = load i8**, i8*** %vec3
  %34 = load i32, i32* %cnt
  %35 = add i32 %34, 1
  store i32 %35, i32* %cnt
  %36 = getelementptr i8*, i8** %33, i32 %34
  %37 = load i8*, i8** %src1
  %38 = load i32, i32* %p
  %39 = getelementptr i8, i8* %37, i32 %38
  store i8* %39, i8** %36
  %40 = load i32, i32* %q
  %41 = zext i32 %40 to i64
  %42 = add i64 %41, 1
  %43 = trunc i64 %42 to i32
  store i32 %43, i32* %p
  br label %while.cond
}

define void @extract([1000 x i8]* %pyfa, i32 %n) {
entry:
  %pyfa1 = alloca [1000 x i8]*
  store [1000 x i8]* %pyfa, [1000 x i8]** %pyfa1
  %n2 = alloca i32
  store i32 %n, i32* %n2
  %vec = alloca [100 x i8*]
  %i = alloca i32
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %0 = load i32, i32* %n2
  %1 = load i32, i32* %i
  %2 = icmp slt i32 %1, %0
  br i1 %2, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  %cnt = alloca i32
  %3 = load [1000 x i8]*, [1000 x i8]** %pyfa1
  %4 = load i32, i32* %i
  %5 = getelementptr [1000 x i8], [1000 x i8]* %3, i32 %4
  %6 = load [1000 x i8], [1000 x i8]* %5
  %7 = load [1000 x i8]*, [1000 x i8]** %pyfa1
  %8 = load i32, i32* %i
  %9 = getelementptr [1000 x i8], [1000 x i8]* %7, i32 %8
  %10 = getelementptr [1000 x i8], [1000 x i8]* %9, i64 0, i64 0
  %11 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 0
  %12 = call i32 @split(i8* %10, i8 124, i8** %11)
  store i32 %12, i32* %cnt
  %13 = load i32, i32* %i
  %14 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %13
  %15 = load [10 x i8], [10 x i8]* %14
  %16 = load i32, i32* %i
  %17 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %16
  %18 = getelementptr [10 x i8], [10 x i8]* %17, i64 0, i64 0
  %19 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 0
  %20 = load i8*, i8** %19
  %21 = call i8* @strcpy(i8* %18, i8* %20)
  %22 = load i32, i32* %i
  %23 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %22
  %24 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 1
  %25 = load i8*, i8** %24
  %26 = call i32 @atoi(i8* %25)
  store i32 %26, i32* %23
  br label %if.cond

for.end:                                          ; preds = %if.out6
  %27 = load i32, i32* %i
  %28 = add i32 %27, 1
  store i32 %28, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  ret void

if.cond:                                          ; preds = %for.loop
  %29 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 2
  %30 = load i8*, i8** %29
  %31 = getelementptr i8, i8* %30, i64 0
  %32 = load i8, i8* %31
  %33 = icmp ne i8 %32, 0
  br i1 %33, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %subvec1 = alloca [1000 x i8*]
  %subvec2 = alloca [1000 x i8*]
  br label %if.out

if.else:                                          ; preds = %if.cond
  br label %if.out

if.out:                                           ; preds = %if.else, %if.then
  br label %if.cond3

if.cond3:                                         ; preds = %if.out
  %34 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %35 = load i8*, i8** %34
  %36 = getelementptr i8, i8* %35, i64 0
  %37 = load i8, i8* %36
  %38 = icmp ne i8 %37, 0
  br i1 %38, label %if.then4, label %if.else5

if.then4:                                         ; preds = %if.cond3
  %39 = load i32, i32* %i
  %40 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %39
  %41 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %42 = load i8*, i8** %41
  %43 = getelementptr i8, i8* %42, i64 0
  %44 = load i8, i8* %43
  store i8 %44, i8* %40
  br label %if.out6

if.else5:                                         ; preds = %if.cond3
  br label %if.out6

if.out6:                                          ; preds = %if.else5, %if.then4
  br label %for.end
}

define i32 @main() {
entry:
  %gpa = alloca double
  store double 0.000000e+00, double* %gpa
  %total = alloca i32
  store i32 0, i32* %total
  %try = alloca i32
  store i32 0, i32* %try
  %taken = alloca i32
  store i32 0, i32* %taken
  %remaining = alloca i32
  store i32 0, i32* %remaining
  %pyfa = alloca [100 x [1000 x i8]]
  %cnt = alloca i32
  %i = alloca i32
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %cnt
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %0 = load i32, i32* %cnt
  %1 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 %0
  %2 = load [1000 x i8], [1000 x i8]* %1
  %3 = load i32, i32* %cnt
  %4 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 %3
  %5 = getelementptr [1000 x i8], [1000 x i8]* %4, i64 0, i64 0
  %6 = load i8*, i8** @stdin
  %7 = call i8* @fgets(i8* %5, i64 999, i8* %6)
  %8 = load i32, i32* %cnt
  %9 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 %8
  %10 = load [1000 x i8], [1000 x i8]* %9
  %11 = load i32, i32* %cnt
  %12 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 %11
  %13 = getelementptr [1000 x i8], [1000 x i8]* %12, i64 0, i64 0
  %14 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @0, i32 0, i32 0))
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  br label %for.end

for.end:                                          ; preds = %for.loop
  %16 = load i32, i32* %cnt
  %17 = add i32 %16, 1
  store i32 %17, i32* %cnt
  br label %for.cond

for.out:                                          ; preds = %for.cond
  %18 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i64 0, i64 0
  %19 = load i32, i32* %cnt
  call void @extract([1000 x i8]* %18, i32 %19)
  br label %for.init1

for.init1:                                        ; preds = %for.out
  store i32 0, i32* %i
  br label %for.cond2

for.cond2:                                        ; preds = %for.end4, %for.init1
  %20 = load i32, i32* %cnt
  %21 = load i32, i32* %i
  %22 = icmp slt i32 %21, %20
  br i1 %22, label %for.loop3, label %for.out5

for.loop3:                                        ; preds = %for.cond2
  %23 = load i32, i32* %total
  %24 = load i32, i32* %i
  %25 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %24
  %26 = load i32, i32* %25
  %27 = add i32 %23, %26
  store i32 %27, i32* %total
  br label %if.cond

for.end4:                                         ; preds = %if.out
  %28 = load i32, i32* %i
  %29 = add i32 %28, 1
  store i32 %29, i32* %i
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  %30 = load i32, i32* %try
  %31 = load i32, i32* %taken
  %32 = add i32 %30, %31
  store i32 %32, i32* %try
  %33 = load i32, i32* %taken
  %34 = load i32, i32* %total
  %35 = sub i32 %34, %33
  store i32 %35, i32* %remaining
  br label %if.cond10

if.cond:                                          ; preds = %for.loop3
  %36 = load i32, i32* %i
  %37 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %36
  %38 = load i8, i8* %37
  %39 = load i32, i32* %i
  %40 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %39
  %41 = load i8, i8* %40
  %42 = icmp ne i8 %41, 70
  %43 = zext i1 %42 to i64
  %44 = icmp ne i64 %43, 0
  %45 = zext i8 %38 to i64
  %46 = icmp ne i64 %45, 0
  %47 = and i1 %46, %44
  br i1 %47, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %48 = load i32, i32* %taken
  %49 = load i32, i32* %i
  %50 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %49
  %51 = load i32, i32* %50
  %52 = add i32 %48, %51
  store i32 %52, i32* %taken
  br label %if.out

if.else:                                          ; preds = %if.cond
  br label %if.cond6

if.out:                                           ; preds = %if.out9, %if.then
  br label %for.end4

if.cond6:                                         ; preds = %if.else
  %53 = load i32, i32* %i
  %54 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %53
  %55 = load i8, i8* %54
  %56 = icmp eq i8 %55, 70
  br i1 %56, label %if.then7, label %if.else8

if.then7:                                         ; preds = %if.cond6
  %57 = load i32, i32* %try
  %58 = load i32, i32* %i
  %59 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %58
  %60 = load i32, i32* %59
  %61 = add i32 %57, %60
  store i32 %61, i32* %try
  br label %if.out9

if.else8:                                         ; preds = %if.cond6
  br label %if.out9

if.out9:                                          ; preds = %if.else8, %if.then7
  br label %if.out

if.cond10:                                        ; preds = %for.out5
  %62 = load i32, i32* %try
  %63 = zext i32 %62 to i64
  %64 = icmp ne i64 %63, 0
  br i1 %64, label %if.then11, label %if.else12

if.then11:                                        ; preds = %if.cond10
  %65 = load double, double* %gpa
  %66 = load i32, i32* %try
  %67 = sitofp i32 %66 to double
  %68 = fdiv double %65, %67
  store double %68, double* %gpa
  br label %if.out13

if.else12:                                        ; preds = %if.cond10
  store double 0.000000e+00, double* %gpa
  br label %if.out13

if.out13:                                         ; preds = %if.else12, %if.then11
  %69 = load double, double* %gpa
  %70 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"GPA: %.1f\0A", i32 0, i32 0), double %69)
  %71 = load i32, i32* %try
  %72 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Attempted: %u\0A", i32 0, i32 0), i32 %71)
  %73 = load i32, i32* %taken
  %74 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Completed: %u\0A", i32 0, i32 0), i32 %73)
  %75 = load i32, i32* %remaining
  %76 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"Credits Remaining: %u\0A\0A", i32 0, i32 0), i32 %75)
  %77 = call i32 @puts(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @"Possible Courses to Take Next", i32 0, i32 0))
  br label %if.cond14

if.cond14:                                        ; preds = %if.out13
  %78 = load i32, i32* %remaining
  %79 = zext i32 %78 to i64
  %80 = icmp eq i64 %79, 0
  br i1 %80, label %if.then15, label %if.else16

if.then15:                                        ; preds = %if.cond14
  %81 = call i32 @puts(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"None - Congratulations!", i32 0, i32 0))
  br label %if.out17

if.else16:                                        ; preds = %if.cond14
  br label %if.out17

if.out17:                                         ; preds = %if.else16, %if.then15
  ret i32 0
}

; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

%dep = type { [10 x i8], %dep*, %dep* }

@stdin = external global i8*
@MAXLEN = private constant i32 1000
@MAXN = private constant i32 100
@name = private global [100 x [10 x i8]] zeroinitializer
@credit = private global [100 x i32] zeroinitializer
@dependency = private global [100 x %dep*] zeroinitializer
@grade = private global [100 x i8] zeroinitializer
@0 = private constant [1 x i8] zeroinitializer
@"GPA: %.1f\0A" = private constant [11 x i8] c"GPA: %.1f\0A\00"
@"Hours Attempted: %u\0A" = private constant [21 x i8] c"Hours Attempted: %u\0A\00"
@"Hours Completed: %u\0A" = private constant [21 x i8] c"Hours Completed: %u\0A\00"
@"Credits Remaining: %u\0A\0A" = private constant [24 x i8] c"Credits Remaining: %u\0A\0A\00"
@"Possible Courses to Take Next" = private constant [30 x i8] c"Possible Courses to Take Next\00"
@"None - Congratulations!" = private constant [24 x i8] c"None - Congratulations!\00"
@"%s\0A" = private constant [4 x i8] c"%s\0A\00"

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
  %11 = getelementptr [100 x i8*], [100 x i8*]* %vec, i32 0, i32 0
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
  %p = alloca %dep*
  %tmp = alloca %dep*
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
  %j = alloca i32
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
  %18 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 0
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
  %p = alloca %dep*
  %prev = alloca %dep*
  %cur = alloca %dep*
  %tmp = alloca %dep*
  br label %for.init18

if.out17:                                         ; preds = %for.out54, %if.then15
  ret i32 0

for.init18:                                       ; preds = %if.else16
  store i32 0, i32* %i
  br label %for.cond19

for.cond19:                                       ; preds = %for.end21, %for.init18
  %82 = load i32, i32* %cnt
  %83 = load i32, i32* %i
  %84 = icmp slt i32 %83, %82
  br i1 %84, label %for.loop20, label %for.out22

for.loop20:                                       ; preds = %for.cond19
  br label %if.cond23

for.end21:                                        ; preds = %if.out26
  %85 = load i32, i32* %i
  %86 = add i32 %85, 1
  store i32 %86, i32* %i
  br label %for.cond19

for.out22:                                        ; preds = %for.cond19
  br label %for.init50

if.cond23:                                        ; preds = %for.loop20
  %87 = load i32, i32* %i
  %88 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %87
  %89 = load i8, i8* %88
  %90 = load i32, i32* %i
  %91 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %90
  %92 = load i8, i8* %91
  %93 = icmp ne i8 %92, 70
  %94 = zext i1 %93 to i64
  %95 = icmp ne i64 %94, 0
  %96 = zext i8 %89 to i64
  %97 = icmp ne i64 %96, 0
  %98 = and i1 %97, %95
  br i1 %98, label %if.then24, label %if.else25

if.then24:                                        ; preds = %if.cond23
  br label %for.init27

if.else25:                                        ; preds = %if.cond23
  br label %if.out26

if.out26:                                         ; preds = %if.else25, %for.out31
  br label %for.end21

for.init27:                                       ; preds = %if.then24
  store i32 0, i32* %j
  br label %for.cond28

for.cond28:                                       ; preds = %for.end30, %for.init27
  %99 = load i32, i32* %cnt
  %100 = load i32, i32* %j
  %101 = icmp slt i32 %100, %99
  br i1 %101, label %for.loop29, label %for.out31

for.loop29:                                       ; preds = %for.cond28
  br label %if.cond32

for.end30:                                        ; preds = %if.out35
  %102 = load i32, i32* %j
  %103 = add i32 %102, 1
  store i32 %103, i32* %j
  br label %for.cond28

for.out31:                                        ; preds = %for.cond28
  br label %if.out26

if.cond32:                                        ; preds = %for.loop29
  %104 = load i32, i32* %j
  %105 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %104
  %106 = load %dep*, %dep** %105
  %107 = ptrtoint %dep* %106 to i64
  %108 = sub i64 %107, 0
  %109 = sdiv exact i64 %108, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %110 = icmp ne i64 %109, 0
  br i1 %110, label %if.then33, label %if.else34

if.then33:                                        ; preds = %if.cond32
  br label %for.init36

if.else34:                                        ; preds = %if.cond32
  br label %if.out35

if.out35:                                         ; preds = %if.else34, %for.out40
  br label %for.end30

for.init36:                                       ; preds = %if.then33
  %111 = load i32, i32* %j
  %112 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %111
  %113 = load %dep*, %dep** %112
  %114 = getelementptr %dep, %dep* %113, i32 0, i32 1
  %115 = load %dep*, %dep** %114
  store %dep* %115, %dep** %p
  br label %for.cond37

for.cond37:                                       ; preds = %for.end39, %for.init36
  %116 = load %dep*, %dep** %p
  %117 = ptrtoint %dep* %116 to i64
  %118 = sub i64 %117, 0
  %119 = sdiv exact i64 %118, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %120 = icmp ne i64 %119, 0
  br i1 %120, label %for.loop38, label %for.out40

for.loop38:                                       ; preds = %for.cond37
  br label %for.init41

for.end39:                                        ; preds = %for.out45
  %121 = load %dep*, %dep** %p
  %122 = getelementptr %dep, %dep* %121, i32 0, i32 1
  %123 = load %dep*, %dep** %122
  store %dep* %123, %dep** %p
  br label %for.cond37

for.out40:                                        ; preds = %for.cond37
  br label %if.out35

for.init41:                                       ; preds = %for.loop38
  %124 = load %dep*, %dep** %p
  store %dep* %124, %dep** %prev
  %125 = load %dep*, %dep** %p
  %126 = getelementptr %dep, %dep* %125, i32 0, i32 2
  %127 = load %dep*, %dep** %126
  store %dep* %127, %dep** %cur
  br label %for.cond42

for.cond42:                                       ; preds = %for.end44, %for.init41
  %128 = load %dep*, %dep** %cur
  %129 = ptrtoint %dep* %128 to i64
  %130 = sub i64 %129, 0
  %131 = sdiv exact i64 %130, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %132 = icmp ne i64 %131, 0
  br i1 %132, label %for.loop43, label %for.out45

for.loop43:                                       ; preds = %for.cond42
  br label %if.cond46

for.end44:                                        ; preds = %if.out49
  br label %for.cond42

for.out45:                                        ; preds = %if.then47, %for.cond42
  br label %for.end39

if.cond46:                                        ; preds = %for.loop43
  %133 = load %dep*, %dep** %cur
  %134 = getelementptr %dep, %dep* %133, i32 0, i32 0
  %135 = getelementptr [10 x i8], [10 x i8]* %134, i32 0, i32 0
  %136 = load i32, i32* %i
  %137 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %136
  %138 = load [10 x i8], [10 x i8]* %137
  %139 = load i32, i32* %i
  %140 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %139
  %141 = getelementptr [10 x i8], [10 x i8]* %140, i64 0, i64 0
  %142 = call i32 @strcmp(i8* %135, i8* %141)
  %143 = zext i32 %142 to i64
  %144 = icmp eq i64 %143, 0
  br i1 %144, label %if.then47, label %if.else48

if.then47:                                        ; preds = %if.cond46
  %145 = load %dep*, %dep** %prev
  %146 = getelementptr %dep, %dep* %145, i32 0, i32 2
  %147 = load %dep*, %dep** %cur
  %148 = getelementptr %dep, %dep* %147, i32 0, i32 2
  %149 = load %dep*, %dep** %148
  store %dep* %149, %dep** %146
  %150 = load %dep*, %dep** %cur
  store %dep* %150, %dep** %tmp
  %151 = load %dep*, %dep** %cur
  %152 = getelementptr %dep, %dep* %151, i32 0, i32 2
  %153 = load %dep*, %dep** %152
  store %dep* %153, %dep** %cur
  %154 = load %dep*, %dep** %tmp
  %155 = bitcast %dep* %154 to i8*
  call void @free(i8* %155)
  br label %for.out45

if.else48:                                        ; preds = %if.cond46
  %156 = load %dep*, %dep** %cur
  store %dep* %156, %dep** %prev
  %157 = load %dep*, %dep** %cur
  %158 = getelementptr %dep, %dep* %157, i32 0, i32 2
  %159 = load %dep*, %dep** %158
  store %dep* %159, %dep** %cur
  br label %if.out49

if.out49:                                         ; preds = %if.else48
  br label %for.end44

for.init50:                                       ; preds = %for.out22
  store i32 0, i32* %i
  br label %for.cond51

for.cond51:                                       ; preds = %for.end53, %for.init50
  %160 = load i32, i32* %cnt
  %161 = load i32, i32* %i
  %162 = icmp slt i32 %161, %160
  br i1 %162, label %for.loop52, label %for.out54

for.loop52:                                       ; preds = %for.cond51
  br label %if.cond55

for.end53:                                        ; preds = %if.out58
  %163 = load i32, i32* %i
  %164 = add i32 %163, 1
  store i32 %164, i32* %i
  br label %for.cond51

for.out54:                                        ; preds = %for.cond51
  br label %if.out17

if.cond55:                                        ; preds = %for.loop52
  %165 = load i32, i32* %i
  %166 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %165
  %167 = load i8, i8* %166
  %168 = zext i8 %167 to i64
  %169 = icmp eq i64 %168, 0
  %170 = load i32, i32* %i
  %171 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %170
  %172 = load i8, i8* %171
  %173 = icmp eq i8 %172, 70
  %174 = zext i1 %173 to i64
  %175 = icmp ne i64 %174, 0
  %176 = zext i1 %169 to i64
  %177 = icmp ne i64 %176, 0
  %178 = or i1 %177, %175
  br i1 %178, label %if.then56, label %if.else57

if.then56:                                        ; preds = %if.cond55
  br label %if.cond59

if.else57:                                        ; preds = %if.cond55
  br label %if.out58

if.out58:                                         ; preds = %if.else57, %if.out62
  br label %for.end53

if.cond59:                                        ; preds = %if.then56
  %179 = load i32, i32* %i
  %180 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %179
  %181 = load %dep*, %dep** %180
  %182 = ptrtoint %dep* %181 to i64
  %183 = sub i64 %182, 0
  %184 = sdiv exact i64 %183, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %185 = icmp eq i64 %184, 0
  br i1 %185, label %if.then60, label %if.else61

if.then60:                                        ; preds = %if.cond59
  %186 = load i32, i32* %i
  %187 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %186
  %188 = load [10 x i8], [10 x i8]* %187
  %189 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), [10 x i8] %188)
  br label %if.out62

if.else61:                                        ; preds = %if.cond59
  br label %for.init63

if.out62:                                         ; preds = %for.out67, %if.then60
  br label %if.out58

for.init63:                                       ; preds = %if.else61
  %190 = load i32, i32* %i
  %191 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %190
  %192 = load %dep*, %dep** %191
  %193 = getelementptr %dep, %dep* %192, i32 0, i32 1
  %194 = load %dep*, %dep** %193
  store %dep* %194, %dep** %p
  br label %for.cond64

for.cond64:                                       ; preds = %for.end66, %for.init63
  %195 = load %dep*, %dep** %p
  %196 = ptrtoint %dep* %195 to i64
  %197 = sub i64 %196, 0
  %198 = sdiv exact i64 %197, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %199 = icmp ne i64 %198, 0
  br i1 %199, label %for.loop65, label %for.out67

for.loop65:                                       ; preds = %for.cond64
  br label %if.cond68

for.end66:                                        ; preds = %if.out71
  %200 = load %dep*, %dep** %p
  %201 = getelementptr %dep, %dep* %200, i32 0, i32 1
  %202 = load %dep*, %dep** %201
  store %dep* %202, %dep** %p
  br label %for.cond64

for.out67:                                        ; preds = %if.then69, %for.cond64
  br label %if.out62

if.cond68:                                        ; preds = %for.loop65
  %203 = load %dep*, %dep** %p
  %204 = getelementptr %dep, %dep* %203, i32 0, i32 2
  %205 = load %dep*, %dep** %204
  %206 = ptrtoint %dep* %205 to i64
  %207 = sub i64 %206, 0
  %208 = sdiv exact i64 %207, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %209 = icmp eq i64 %208, 0
  br i1 %209, label %if.then69, label %if.else70

if.then69:                                        ; preds = %if.cond68
  %210 = load i32, i32* %i
  %211 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %210
  %212 = load [10 x i8], [10 x i8]* %211
  %213 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), [10 x i8] %212)
  br label %for.out67

if.else70:                                        ; preds = %if.cond68
  br label %if.out71

if.out71:                                         ; preds = %if.else70
  br label %for.end66
}

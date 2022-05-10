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
@"course %s:\09credit: %d\09grade: %c\0A" = private constant [33 x i8] c"course %s:\09credit: %d\09grade: %c\0A\00"
@"choice %d: " = private constant [12 x i8] c"choice %d: \00"
@"%s " = private constant [4 x i8] c"%s \00"
@0 = private constant [1 x i8] zeroinitializer
@"no courses required ahead" = private constant [26 x i8] c"no courses required ahead\00"
@-------------------------------------------- = private constant [45 x i8] c"--------------------------------------------\00"
@"\0A" = private constant [2 x i8] c"\0A\00"
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
  %15 = getelementptr [10 x i8], [10 x i8]* %14, i64 0, i64 0
  %16 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 0
  %17 = load i8*, i8** %16
  %18 = call i8* @strcpy(i8* %15, i8* %17)
  %19 = load i32, i32* %i
  %20 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %19
  %21 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 1
  %22 = load i8*, i8** %21
  %23 = call i32 @atoi(i8* %22)
  store i32 %23, i32* %20
  br label %if.cond

for.end:                                          ; preds = %if.out16
  %24 = load i32, i32* %i
  %25 = add i32 %24, 1
  store i32 %25, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  ret void

if.cond:                                          ; preds = %for.loop
  %26 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 2
  %27 = load i8*, i8** %26
  %28 = getelementptr i8, i8* %27, i64 0
  %29 = load i8, i8* %28
  %30 = icmp ne i8 %29, 0
  br i1 %30, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %subvec1 = alloca [1000 x i8*]
  %subvec2 = alloca [1000 x i8*]
  %p = alloca %dep*
  %tmp = alloca %dep*
  %groups = alloca i32
  %items = alloca i32
  %ii = alloca i32
  %jj = alloca i32
  %31 = load i32, i32* %i
  %32 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %31
  %33 = call i8* @calloc(i64 26, i64 1)
  %34 = bitcast i8* %33 to %dep*
  store %dep* %34, %dep** %32
  %35 = load i32, i32* %i
  %36 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %35
  %37 = load %dep*, %dep** %36
  store %dep* %37, %dep** %p
  %38 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 2
  %39 = load i8*, i8** %38
  %40 = getelementptr [1000 x i8*], [1000 x i8*]* %subvec1, i32 0, i32 0
  %41 = call i32 @split(i8* %39, i8 59, i8** %40)
  store i32 %41, i32* %groups
  br label %for.init3

if.else:                                          ; preds = %if.cond
  br label %if.out

if.out:                                           ; preds = %if.else, %for.out7
  br label %if.cond13

for.init3:                                        ; preds = %if.then
  store i32 0, i32* %ii
  br label %for.cond4

for.cond4:                                        ; preds = %for.end6, %for.init3
  %42 = load i32, i32* %groups
  %43 = load i32, i32* %ii
  %44 = icmp slt i32 %43, %42
  br i1 %44, label %for.loop5, label %for.out7

for.loop5:                                        ; preds = %for.cond4
  %45 = load %dep*, %dep** %p
  %46 = getelementptr %dep, %dep* %45, i32 0, i32 1
  %47 = call i8* @calloc(i64 26, i64 1)
  %48 = bitcast i8* %47 to %dep*
  store %dep* %48, %dep** %46
  %49 = load %dep*, %dep** %p
  %50 = getelementptr %dep, %dep* %49, i32 0, i32 1
  %51 = load %dep*, %dep** %50
  store %dep* %51, %dep** %tmp
  %52 = load i32, i32* %ii
  %53 = getelementptr [1000 x i8*], [1000 x i8*]* %subvec1, i32 0, i32 %52
  %54 = load i8*, i8** %53
  %55 = getelementptr [1000 x i8*], [1000 x i8*]* %subvec2, i32 0, i32 0
  %56 = call i32 @split(i8* %54, i8 44, i8** %55)
  store i32 %56, i32* %items
  br label %for.init8

for.end6:                                         ; preds = %for.out12
  %57 = load i32, i32* %ii
  %58 = add i32 %57, 1
  store i32 %58, i32* %ii
  br label %for.cond4

for.out7:                                         ; preds = %for.cond4
  br label %if.out

for.init8:                                        ; preds = %for.loop5
  store i32 0, i32* %jj
  br label %for.cond9

for.cond9:                                        ; preds = %for.end11, %for.init8
  %59 = load i32, i32* %items
  %60 = load i32, i32* %jj
  %61 = icmp slt i32 %60, %59
  br i1 %61, label %for.loop10, label %for.out12

for.loop10:                                       ; preds = %for.cond9
  %62 = load %dep*, %dep** %tmp
  %63 = getelementptr %dep, %dep* %62, i32 0, i32 2
  %64 = call i8* @calloc(i64 26, i64 1)
  %65 = bitcast i8* %64 to %dep*
  store %dep* %65, %dep** %63
  %66 = load %dep*, %dep** %tmp
  %67 = getelementptr %dep, %dep* %66, i32 0, i32 2
  %68 = load %dep*, %dep** %67
  %69 = getelementptr %dep, %dep* %68, i32 0, i32 0
  %70 = getelementptr [10 x i8], [10 x i8]* %69, i32 0, i32 0
  %71 = load i32, i32* %jj
  %72 = getelementptr [1000 x i8*], [1000 x i8*]* %subvec2, i32 0, i32 %71
  %73 = load i8*, i8** %72
  %74 = call i8* @strcpy(i8* %70, i8* %73)
  %75 = load %dep*, %dep** %tmp
  %76 = getelementptr %dep, %dep* %75, i32 0, i32 2
  %77 = load %dep*, %dep** %76
  store %dep* %77, %dep** %tmp
  br label %for.end11

for.end11:                                        ; preds = %for.loop10
  %78 = load i32, i32* %jj
  %79 = add i32 %78, 1
  store i32 %79, i32* %jj
  br label %for.cond9

for.out12:                                        ; preds = %for.cond9
  %80 = load %dep*, %dep** %p
  %81 = getelementptr %dep, %dep* %80, i32 0, i32 1
  %82 = load %dep*, %dep** %81
  store %dep* %82, %dep** %p
  br label %for.end6

if.cond13:                                        ; preds = %if.out
  %83 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %84 = load i8*, i8** %83
  %85 = getelementptr i8, i8* %84, i64 0
  %86 = load i8, i8* %85
  %87 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %88 = load i8*, i8** %87
  %89 = getelementptr i8, i8* %88, i64 0
  %90 = load i8, i8* %89
  %91 = icmp ne i8 %90, 10
  %92 = zext i1 %91 to i64
  %93 = icmp ne i64 %92, 0
  %94 = zext i8 %86 to i64
  %95 = icmp ne i64 %94, 0
  %96 = and i1 %95, %93
  br i1 %96, label %if.then14, label %if.else15

if.then14:                                        ; preds = %if.cond13
  %97 = load i32, i32* %i
  %98 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %97
  %99 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %100 = load i8*, i8** %99
  %101 = getelementptr i8, i8* %100, i64 0
  %102 = load i8, i8* %101
  store i8 %102, i8* %98
  br label %if.out16

if.else15:                                        ; preds = %if.cond13
  br label %if.out16

if.out16:                                         ; preds = %if.else15, %if.then14
  br label %for.end
}

define void @dump(i32 %index) {
entry:
  %index1 = alloca i32
  store i32 %index, i32* %index1
  %p = alloca %dep*
  %tmp = alloca %dep*
  %0 = load i32, i32* %index1
  %1 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %0
  %2 = getelementptr [10 x i8], [10 x i8]* %1, i64 0, i64 0
  %3 = load i32, i32* %index1
  %4 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %3
  %5 = load i32, i32* %4
  %6 = load i32, i32* %index1
  %7 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %6
  %8 = load i8, i8* %7
  %9 = zext i8 %8 to i64
  %10 = icmp ne i64 %9, 0
  %11 = load i32, i32* %index1
  %12 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %11
  %13 = load i8, i8* %12
  %14 = select i1 %10, i8 %13, i8 32
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @"course %s:\09credit: %d\09grade: %c\0A", i32 0, i32 0), i8* %2, i32 %5, i8 %14)
  br label %if.cond

if.cond:                                          ; preds = %entry
  %16 = load i32, i32* %index1
  %17 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %16
  %18 = load %dep*, %dep** %17
  %19 = ptrtoint %dep* %18 to i64
  %20 = sub i64 %19, 0
  %21 = sdiv exact i64 %20, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %22 = icmp ne i64 %21, 0
  br i1 %22, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %cnt = alloca i32
  store i32 0, i32* %cnt
  br label %for.init

if.else:                                          ; preds = %if.cond
  %23 = call i32 @puts(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @"no courses required ahead", i32 0, i32 0))
  br label %if.out

if.out:                                           ; preds = %if.else, %for.out
  %24 = call i32 @puts(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @--------------------------------------------, i32 0, i32 0))
  ret void

for.init:                                         ; preds = %if.then
  %25 = load i32, i32* %index1
  %26 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %25
  %27 = load %dep*, %dep** %26
  %28 = getelementptr %dep, %dep* %27, i32 0, i32 1
  %29 = load %dep*, %dep** %28
  store %dep* %29, %dep** %p
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %30 = load %dep*, %dep** %p
  %31 = ptrtoint %dep* %30 to i64
  %32 = sub i64 %31, 0
  %33 = sdiv exact i64 %32, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %34 = icmp ne i64 %33, 0
  br i1 %34, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  %35 = load i32, i32* %cnt
  %36 = add i32 %35, 1
  store i32 %36, i32* %cnt
  %37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @"choice %d: ", i32 0, i32 0), i32 %35)
  br label %for.init2

for.end:                                          ; preds = %for.out6
  %38 = load %dep*, %dep** %p
  %39 = getelementptr %dep, %dep* %38, i32 0, i32 1
  %40 = load %dep*, %dep** %39
  store %dep* %40, %dep** %p
  br label %for.cond

for.out:                                          ; preds = %for.cond
  br label %if.out

for.init2:                                        ; preds = %for.loop
  %41 = load %dep*, %dep** %p
  %42 = getelementptr %dep, %dep* %41, i32 0, i32 2
  %43 = load %dep*, %dep** %42
  store %dep* %43, %dep** %tmp
  br label %for.cond3

for.cond3:                                        ; preds = %for.end5, %for.init2
  %44 = load %dep*, %dep** %tmp
  %45 = ptrtoint %dep* %44 to i64
  %46 = sub i64 %45, 0
  %47 = sdiv exact i64 %46, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %48 = icmp ne i64 %47, 0
  br i1 %48, label %for.loop4, label %for.out6

for.loop4:                                        ; preds = %for.cond3
  %49 = load %dep*, %dep** %tmp
  %50 = getelementptr %dep, %dep* %49, i32 0, i32 0
  %51 = getelementptr [10 x i8], [10 x i8]* %50, i32 0, i32 0
  %52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s ", i32 0, i32 0), i8* %51)
  br label %for.end5

for.end5:                                         ; preds = %for.loop4
  %53 = load %dep*, %dep** %tmp
  %54 = getelementptr %dep, %dep* %53, i32 0, i32 2
  %55 = load %dep*, %dep** %54
  store %dep* %55, %dep** %tmp
  br label %for.cond3

for.out6:                                         ; preds = %for.cond3
  %56 = call i32 @puts(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @0, i32 0, i32 0))
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
  %2 = getelementptr [1000 x i8], [1000 x i8]* %1, i64 0, i64 0
  %3 = load i8*, i8** @stdin
  %4 = call i8* @fgets(i8* %2, i64 999, i8* %3)
  %5 = load i32, i32* %cnt
  %6 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 %5
  %7 = getelementptr [1000 x i8], [1000 x i8]* %6, i64 0, i64 0
  %8 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @"\0A", i32 0, i32 0))
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  br label %for.end

for.end:                                          ; preds = %for.loop
  %10 = load i32, i32* %cnt
  %11 = add i32 %10, 1
  store i32 %11, i32* %cnt
  br label %for.cond

for.out:                                          ; preds = %for.cond
  %12 = getelementptr [100 x [1000 x i8]], [100 x [1000 x i8]]* %pyfa, i32 0, i32 0
  %13 = load i32, i32* %cnt
  call void @extract([1000 x i8]* %12, i32 %13)
  br label %for.init1

for.init1:                                        ; preds = %for.out
  store i32 0, i32* %i
  br label %for.cond2

for.cond2:                                        ; preds = %for.end4, %for.init1
  %14 = load i32, i32* %cnt
  %15 = load i32, i32* %i
  %16 = icmp slt i32 %15, %14
  br i1 %16, label %for.loop3, label %for.out5

for.loop3:                                        ; preds = %for.cond2
  %17 = load i32, i32* %total
  %18 = load i32, i32* %i
  %19 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %18
  %20 = load i32, i32* %19
  %21 = add i32 %17, %20
  store i32 %21, i32* %total
  br label %if.cond

for.end4:                                         ; preds = %if.out
  %22 = load i32, i32* %i
  %23 = add i32 %22, 1
  store i32 %23, i32* %i
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  %24 = load i32, i32* %try
  %25 = load i32, i32* %taken
  %26 = add i32 %24, %25
  store i32 %26, i32* %try
  %27 = load i32, i32* %total
  %28 = load i32, i32* %taken
  %29 = sub i32 %27, %28
  store i32 %29, i32* %remaining
  br label %if.cond13

if.cond:                                          ; preds = %for.loop3
  %30 = load i32, i32* %i
  %31 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %30
  %32 = load i8, i8* %31
  %33 = load i32, i32* %i
  %34 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %33
  %35 = load i8, i8* %34
  %36 = icmp ne i8 %35, 70
  %37 = zext i1 %36 to i64
  %38 = icmp ne i64 %37, 0
  %39 = zext i8 %32 to i64
  %40 = icmp ne i64 %39, 0
  %41 = and i1 %40, %38
  br i1 %41, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %42 = load i32, i32* %taken
  %43 = load i32, i32* %i
  %44 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %43
  %45 = load i32, i32* %44
  %46 = add i32 %42, %45
  store i32 %46, i32* %taken
  br label %switch.cond

if.else:                                          ; preds = %if.cond
  br label %if.cond9

if.out:                                           ; preds = %if.out12, %switch.out
  br label %for.end4

switch.cond:                                      ; preds = %if.then
  %47 = load i32, i32* %i
  %48 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %47
  %49 = load i8, i8* %48
  switch i8 %49, label %switch.default [
    i8 65, label %switch.case
    i8 66, label %switch.case6
    i8 67, label %switch.case7
    i8 68, label %switch.case8
  ]

switch.out:                                       ; preds = %switch.default, %switch.case8, %switch.case7, %switch.case6, %switch.case
  br label %if.out

switch.case:                                      ; preds = %switch.cond
  %50 = load double, double* %gpa
  %51 = load i32, i32* %i
  %52 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %51
  %53 = load i32, i32* %52
  %54 = zext i32 %53 to i64
  %55 = mul i64 %54, 4
  %56 = sitofp i64 %55 to double
  %57 = fadd double %50, %56
  store double %57, double* %gpa
  br label %switch.out

switch.case6:                                     ; preds = %switch.cond
  %58 = load double, double* %gpa
  %59 = load i32, i32* %i
  %60 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %59
  %61 = load i32, i32* %60
  %62 = zext i32 %61 to i64
  %63 = mul i64 %62, 3
  %64 = sitofp i64 %63 to double
  %65 = fadd double %58, %64
  store double %65, double* %gpa
  br label %switch.out

switch.case7:                                     ; preds = %switch.cond
  %66 = load double, double* %gpa
  %67 = load i32, i32* %i
  %68 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %67
  %69 = load i32, i32* %68
  %70 = zext i32 %69 to i64
  %71 = mul i64 %70, 2
  %72 = sitofp i64 %71 to double
  %73 = fadd double %66, %72
  store double %73, double* %gpa
  br label %switch.out

switch.case8:                                     ; preds = %switch.cond
  %74 = load double, double* %gpa
  %75 = load i32, i32* %i
  %76 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %75
  %77 = load i32, i32* %76
  %78 = zext i32 %77 to i64
  %79 = mul i64 %78, 1
  %80 = sitofp i64 %79 to double
  %81 = fadd double %74, %80
  store double %81, double* %gpa
  br label %switch.out

switch.default:                                   ; preds = %switch.cond
  br label %switch.out

if.cond9:                                         ; preds = %if.else
  %82 = load i32, i32* %i
  %83 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %82
  %84 = load i8, i8* %83
  %85 = icmp eq i8 %84, 70
  br i1 %85, label %if.then10, label %if.else11

if.then10:                                        ; preds = %if.cond9
  %86 = load i32, i32* %try
  %87 = load i32, i32* %i
  %88 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %87
  %89 = load i32, i32* %88
  %90 = add i32 %86, %89
  store i32 %90, i32* %try
  br label %if.out12

if.else11:                                        ; preds = %if.cond9
  br label %if.out12

if.out12:                                         ; preds = %if.else11, %if.then10
  br label %if.out

if.cond13:                                        ; preds = %for.out5
  %91 = load i32, i32* %try
  %92 = zext i32 %91 to i64
  %93 = icmp ne i64 %92, 0
  br i1 %93, label %if.then14, label %if.else15

if.then14:                                        ; preds = %if.cond13
  %94 = load double, double* %gpa
  %95 = load i32, i32* %try
  %96 = sitofp i32 %95 to double
  %97 = fdiv double %94, %96
  store double %97, double* %gpa
  br label %if.out16

if.else15:                                        ; preds = %if.cond13
  store double 0.000000e+00, double* %gpa
  br label %if.out16

if.out16:                                         ; preds = %if.else15, %if.then14
  %98 = load double, double* %gpa
  %99 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"GPA: %.1f\0A", i32 0, i32 0), double %98)
  %100 = load i32, i32* %try
  %101 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Attempted: %u\0A", i32 0, i32 0), i32 %100)
  %102 = load i32, i32* %taken
  %103 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Completed: %u\0A", i32 0, i32 0), i32 %102)
  %104 = load i32, i32* %remaining
  %105 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"Credits Remaining: %u\0A\0A", i32 0, i32 0), i32 %104)
  %106 = call i32 @puts(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @"Possible Courses to Take Next", i32 0, i32 0))
  br label %if.cond17

if.cond17:                                        ; preds = %if.out16
  %107 = load i32, i32* %remaining
  %108 = zext i32 %107 to i64
  %109 = icmp eq i64 %108, 0
  br i1 %109, label %if.then18, label %if.else19

if.then18:                                        ; preds = %if.cond17
  %110 = call i32 @puts(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"None - Congratulations!", i32 0, i32 0))
  br label %if.out20

if.else19:                                        ; preds = %if.cond17
  %p = alloca %dep*
  %prev = alloca %dep*
  %cur = alloca %dep*
  %tmp = alloca %dep*
  br label %for.init21

if.out20:                                         ; preds = %for.out57, %if.then18
  ret i32 0

for.init21:                                       ; preds = %if.else19
  store i32 0, i32* %i
  br label %for.cond22

for.cond22:                                       ; preds = %for.end24, %for.init21
  %111 = load i32, i32* %cnt
  %112 = load i32, i32* %i
  %113 = icmp slt i32 %112, %111
  br i1 %113, label %for.loop23, label %for.out25

for.loop23:                                       ; preds = %for.cond22
  br label %if.cond26

for.end24:                                        ; preds = %if.out29
  %114 = load i32, i32* %i
  %115 = add i32 %114, 1
  store i32 %115, i32* %i
  br label %for.cond22

for.out25:                                        ; preds = %for.cond22
  br label %for.init53

if.cond26:                                        ; preds = %for.loop23
  %116 = load i32, i32* %i
  %117 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %116
  %118 = load i8, i8* %117
  %119 = load i32, i32* %i
  %120 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %119
  %121 = load i8, i8* %120
  %122 = icmp ne i8 %121, 70
  %123 = zext i1 %122 to i64
  %124 = icmp ne i64 %123, 0
  %125 = zext i8 %118 to i64
  %126 = icmp ne i64 %125, 0
  %127 = and i1 %126, %124
  br i1 %127, label %if.then27, label %if.else28

if.then27:                                        ; preds = %if.cond26
  br label %for.init30

if.else28:                                        ; preds = %if.cond26
  br label %if.out29

if.out29:                                         ; preds = %if.else28, %for.out34
  br label %for.end24

for.init30:                                       ; preds = %if.then27
  store i32 0, i32* %j
  br label %for.cond31

for.cond31:                                       ; preds = %for.end33, %for.init30
  %128 = load i32, i32* %cnt
  %129 = load i32, i32* %j
  %130 = icmp slt i32 %129, %128
  br i1 %130, label %for.loop32, label %for.out34

for.loop32:                                       ; preds = %for.cond31
  br label %if.cond35

for.end33:                                        ; preds = %if.out38
  %131 = load i32, i32* %j
  %132 = add i32 %131, 1
  store i32 %132, i32* %j
  br label %for.cond31

for.out34:                                        ; preds = %for.cond31
  br label %if.out29

if.cond35:                                        ; preds = %for.loop32
  %133 = load i32, i32* %j
  %134 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %133
  %135 = load %dep*, %dep** %134
  %136 = ptrtoint %dep* %135 to i64
  %137 = sub i64 %136, 0
  %138 = sdiv exact i64 %137, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %139 = icmp ne i64 %138, 0
  br i1 %139, label %if.then36, label %if.else37

if.then36:                                        ; preds = %if.cond35
  br label %for.init39

if.else37:                                        ; preds = %if.cond35
  br label %if.out38

if.out38:                                         ; preds = %if.else37, %for.out43
  br label %for.end33

for.init39:                                       ; preds = %if.then36
  %140 = load i32, i32* %j
  %141 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %140
  %142 = load %dep*, %dep** %141
  %143 = getelementptr %dep, %dep* %142, i32 0, i32 1
  %144 = load %dep*, %dep** %143
  store %dep* %144, %dep** %p
  br label %for.cond40

for.cond40:                                       ; preds = %for.end42, %for.init39
  %145 = load %dep*, %dep** %p
  %146 = ptrtoint %dep* %145 to i64
  %147 = sub i64 %146, 0
  %148 = sdiv exact i64 %147, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %149 = icmp ne i64 %148, 0
  br i1 %149, label %for.loop41, label %for.out43

for.loop41:                                       ; preds = %for.cond40
  br label %for.init44

for.end42:                                        ; preds = %for.out48
  %150 = load %dep*, %dep** %p
  %151 = getelementptr %dep, %dep* %150, i32 0, i32 1
  %152 = load %dep*, %dep** %151
  store %dep* %152, %dep** %p
  br label %for.cond40

for.out43:                                        ; preds = %for.cond40
  br label %if.out38

for.init44:                                       ; preds = %for.loop41
  %153 = load %dep*, %dep** %p
  store %dep* %153, %dep** %prev
  %154 = load %dep*, %dep** %p
  %155 = getelementptr %dep, %dep* %154, i32 0, i32 2
  %156 = load %dep*, %dep** %155
  store %dep* %156, %dep** %cur
  br label %for.cond45

for.cond45:                                       ; preds = %for.end47, %for.init44
  %157 = load %dep*, %dep** %cur
  %158 = ptrtoint %dep* %157 to i64
  %159 = sub i64 %158, 0
  %160 = sdiv exact i64 %159, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %161 = icmp ne i64 %160, 0
  br i1 %161, label %for.loop46, label %for.out48

for.loop46:                                       ; preds = %for.cond45
  br label %if.cond49

for.end47:                                        ; preds = %if.out52
  br label %for.cond45

for.out48:                                        ; preds = %if.then50, %for.cond45
  br label %for.end42

if.cond49:                                        ; preds = %for.loop46
  %162 = load %dep*, %dep** %cur
  %163 = getelementptr %dep, %dep* %162, i32 0, i32 0
  %164 = getelementptr [10 x i8], [10 x i8]* %163, i32 0, i32 0
  %165 = load i32, i32* %i
  %166 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %165
  %167 = getelementptr [10 x i8], [10 x i8]* %166, i64 0, i64 0
  %168 = call i32 @strcmp(i8* %164, i8* %167)
  %169 = zext i32 %168 to i64
  %170 = icmp eq i64 %169, 0
  br i1 %170, label %if.then50, label %if.else51

if.then50:                                        ; preds = %if.cond49
  %171 = load %dep*, %dep** %prev
  %172 = getelementptr %dep, %dep* %171, i32 0, i32 2
  %173 = load %dep*, %dep** %cur
  %174 = getelementptr %dep, %dep* %173, i32 0, i32 2
  %175 = load %dep*, %dep** %174
  store %dep* %175, %dep** %172
  %176 = load %dep*, %dep** %cur
  store %dep* %176, %dep** %tmp
  %177 = load %dep*, %dep** %cur
  %178 = getelementptr %dep, %dep* %177, i32 0, i32 2
  %179 = load %dep*, %dep** %178
  store %dep* %179, %dep** %cur
  %180 = load %dep*, %dep** %tmp
  %181 = bitcast %dep* %180 to i8*
  call void @free(i8* %181)
  br label %for.out48

if.else51:                                        ; preds = %if.cond49
  %182 = load %dep*, %dep** %cur
  store %dep* %182, %dep** %prev
  %183 = load %dep*, %dep** %cur
  %184 = getelementptr %dep, %dep* %183, i32 0, i32 2
  %185 = load %dep*, %dep** %184
  store %dep* %185, %dep** %cur
  br label %if.out52

if.out52:                                         ; preds = %if.else51
  br label %for.end47

for.init53:                                       ; preds = %for.out25
  store i32 0, i32* %i
  br label %for.cond54

for.cond54:                                       ; preds = %for.end56, %for.init53
  %186 = load i32, i32* %cnt
  %187 = load i32, i32* %i
  %188 = icmp slt i32 %187, %186
  br i1 %188, label %for.loop55, label %for.out57

for.loop55:                                       ; preds = %for.cond54
  br label %if.cond58

for.end56:                                        ; preds = %if.out61
  %189 = load i32, i32* %i
  %190 = add i32 %189, 1
  store i32 %190, i32* %i
  br label %for.cond54

for.out57:                                        ; preds = %for.cond54
  br label %if.out20

if.cond58:                                        ; preds = %for.loop55
  %191 = load i32, i32* %i
  %192 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %191
  %193 = load i8, i8* %192
  %194 = zext i8 %193 to i64
  %195 = icmp eq i64 %194, 0
  %196 = load i32, i32* %i
  %197 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %196
  %198 = load i8, i8* %197
  %199 = icmp eq i8 %198, 70
  %200 = zext i1 %199 to i64
  %201 = icmp ne i64 %200, 0
  %202 = zext i1 %195 to i64
  %203 = icmp ne i64 %202, 0
  %204 = or i1 %203, %201
  br i1 %204, label %if.then59, label %if.else60

if.then59:                                        ; preds = %if.cond58
  br label %if.cond62

if.else60:                                        ; preds = %if.cond58
  br label %if.out61

if.out61:                                         ; preds = %if.else60, %if.out65
  br label %for.end56

if.cond62:                                        ; preds = %if.then59
  %205 = load i32, i32* %i
  %206 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %205
  %207 = load %dep*, %dep** %206
  %208 = ptrtoint %dep* %207 to i64
  %209 = sub i64 %208, 0
  %210 = sdiv exact i64 %209, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %211 = icmp eq i64 %210, 0
  br i1 %211, label %if.then63, label %if.else64

if.then63:                                        ; preds = %if.cond62
  %212 = load i32, i32* %i
  %213 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %212
  %214 = getelementptr [10 x i8], [10 x i8]* %213, i64 0, i64 0
  %215 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), i8* %214)
  br label %if.out65

if.else64:                                        ; preds = %if.cond62
  br label %for.init66

if.out65:                                         ; preds = %for.out70, %if.then63
  br label %if.out61

for.init66:                                       ; preds = %if.else64
  %216 = load i32, i32* %i
  %217 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %216
  %218 = load %dep*, %dep** %217
  %219 = getelementptr %dep, %dep* %218, i32 0, i32 1
  %220 = load %dep*, %dep** %219
  store %dep* %220, %dep** %p
  br label %for.cond67

for.cond67:                                       ; preds = %for.end69, %for.init66
  %221 = load %dep*, %dep** %p
  %222 = ptrtoint %dep* %221 to i64
  %223 = sub i64 %222, 0
  %224 = sdiv exact i64 %223, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %225 = icmp ne i64 %224, 0
  br i1 %225, label %for.loop68, label %for.out70

for.loop68:                                       ; preds = %for.cond67
  br label %if.cond71

for.end69:                                        ; preds = %if.out74
  %226 = load %dep*, %dep** %p
  %227 = getelementptr %dep, %dep* %226, i32 0, i32 1
  %228 = load %dep*, %dep** %227
  store %dep* %228, %dep** %p
  br label %for.cond67

for.out70:                                        ; preds = %if.then72, %for.cond67
  br label %if.out65

if.cond71:                                        ; preds = %for.loop68
  %229 = load %dep*, %dep** %p
  %230 = getelementptr %dep, %dep* %229, i32 0, i32 2
  %231 = load %dep*, %dep** %230
  %232 = ptrtoint %dep* %231 to i64
  %233 = sub i64 %232, 0
  %234 = sdiv exact i64 %233, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %235 = icmp eq i64 %234, 0
  br i1 %235, label %if.then72, label %if.else73

if.then72:                                        ; preds = %if.cond71
  %236 = load i32, i32* %i
  %237 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %236
  %238 = getelementptr [10 x i8], [10 x i8]* %237, i64 0, i64 0
  %239 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), i8* %238)
  br label %for.out70

if.else73:                                        ; preds = %if.cond71
  br label %if.out74

if.out74:                                         ; preds = %if.else73
  br label %for.end69
}

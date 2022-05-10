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
  br label %if.cond10

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
  br label %if.out

if.else:                                          ; preds = %if.cond
  br label %if.cond6

if.out:                                           ; preds = %if.out9, %if.then
  br label %for.end4

if.cond6:                                         ; preds = %if.else
  %47 = load i32, i32* %i
  %48 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %47
  %49 = load i8, i8* %48
  %50 = icmp eq i8 %49, 70
  br i1 %50, label %if.then7, label %if.else8

if.then7:                                         ; preds = %if.cond6
  %51 = load i32, i32* %try
  %52 = load i32, i32* %i
  %53 = getelementptr [100 x i32], [100 x i32]* @credit, i32 0, i32 %52
  %54 = load i32, i32* %53
  %55 = add i32 %51, %54
  store i32 %55, i32* %try
  br label %if.out9

if.else8:                                         ; preds = %if.cond6
  br label %if.out9

if.out9:                                          ; preds = %if.else8, %if.then7
  br label %if.out

if.cond10:                                        ; preds = %for.out5
  %56 = load i32, i32* %try
  %57 = zext i32 %56 to i64
  %58 = icmp ne i64 %57, 0
  br i1 %58, label %if.then11, label %if.else12

if.then11:                                        ; preds = %if.cond10
  %59 = load double, double* %gpa
  %60 = load i32, i32* %try
  %61 = sitofp i32 %60 to double
  %62 = fdiv double %59, %61
  store double %62, double* %gpa
  br label %if.out13

if.else12:                                        ; preds = %if.cond10
  store double 0.000000e+00, double* %gpa
  br label %if.out13

if.out13:                                         ; preds = %if.else12, %if.then11
  %63 = load double, double* %gpa
  %64 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @"GPA: %.1f\0A", i32 0, i32 0), double %63)
  %65 = load i32, i32* %try
  %66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Attempted: %u\0A", i32 0, i32 0), i32 %65)
  %67 = load i32, i32* %taken
  %68 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @"Hours Completed: %u\0A", i32 0, i32 0), i32 %67)
  %69 = load i32, i32* %remaining
  %70 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"Credits Remaining: %u\0A\0A", i32 0, i32 0), i32 %69)
  %71 = call i32 @puts(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @"Possible Courses to Take Next", i32 0, i32 0))
  br label %if.cond14

if.cond14:                                        ; preds = %if.out13
  %72 = load i32, i32* %remaining
  %73 = zext i32 %72 to i64
  %74 = icmp eq i64 %73, 0
  br i1 %74, label %if.then15, label %if.else16

if.then15:                                        ; preds = %if.cond14
  %75 = call i32 @puts(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"None - Congratulations!", i32 0, i32 0))
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
  %76 = load i32, i32* %cnt
  %77 = load i32, i32* %i
  %78 = icmp slt i32 %77, %76
  br i1 %78, label %for.loop20, label %for.out22

for.loop20:                                       ; preds = %for.cond19
  br label %if.cond23

for.end21:                                        ; preds = %if.out26
  %79 = load i32, i32* %i
  %80 = add i32 %79, 1
  store i32 %80, i32* %i
  br label %for.cond19

for.out22:                                        ; preds = %for.cond19
  br label %for.init50

if.cond23:                                        ; preds = %for.loop20
  %81 = load i32, i32* %i
  %82 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %81
  %83 = load i8, i8* %82
  %84 = load i32, i32* %i
  %85 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %84
  %86 = load i8, i8* %85
  %87 = icmp ne i8 %86, 70
  %88 = zext i1 %87 to i64
  %89 = icmp ne i64 %88, 0
  %90 = zext i8 %83 to i64
  %91 = icmp ne i64 %90, 0
  %92 = and i1 %91, %89
  br i1 %92, label %if.then24, label %if.else25

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
  %93 = load i32, i32* %cnt
  %94 = load i32, i32* %j
  %95 = icmp slt i32 %94, %93
  br i1 %95, label %for.loop29, label %for.out31

for.loop29:                                       ; preds = %for.cond28
  br label %if.cond32

for.end30:                                        ; preds = %if.out35
  %96 = load i32, i32* %j
  %97 = add i32 %96, 1
  store i32 %97, i32* %j
  br label %for.cond28

for.out31:                                        ; preds = %for.cond28
  br label %if.out26

if.cond32:                                        ; preds = %for.loop29
  %98 = load i32, i32* %j
  %99 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %98
  %100 = load %dep*, %dep** %99
  %101 = ptrtoint %dep* %100 to i64
  %102 = sub i64 %101, 0
  %103 = sdiv exact i64 %102, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %104 = icmp ne i64 %103, 0
  br i1 %104, label %if.then33, label %if.else34

if.then33:                                        ; preds = %if.cond32
  br label %for.init36

if.else34:                                        ; preds = %if.cond32
  br label %if.out35

if.out35:                                         ; preds = %if.else34, %for.out40
  br label %for.end30

for.init36:                                       ; preds = %if.then33
  %105 = load i32, i32* %j
  %106 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %105
  %107 = load %dep*, %dep** %106
  %108 = getelementptr %dep, %dep* %107, i32 0, i32 1
  %109 = load %dep*, %dep** %108
  store %dep* %109, %dep** %p
  br label %for.cond37

for.cond37:                                       ; preds = %for.end39, %for.init36
  %110 = load %dep*, %dep** %p
  %111 = ptrtoint %dep* %110 to i64
  %112 = sub i64 %111, 0
  %113 = sdiv exact i64 %112, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %114 = icmp ne i64 %113, 0
  br i1 %114, label %for.loop38, label %for.out40

for.loop38:                                       ; preds = %for.cond37
  br label %for.init41

for.end39:                                        ; preds = %for.out45
  %115 = load %dep*, %dep** %p
  %116 = getelementptr %dep, %dep* %115, i32 0, i32 1
  %117 = load %dep*, %dep** %116
  store %dep* %117, %dep** %p
  br label %for.cond37

for.out40:                                        ; preds = %for.cond37
  br label %if.out35

for.init41:                                       ; preds = %for.loop38
  %118 = load %dep*, %dep** %p
  store %dep* %118, %dep** %prev
  %119 = load %dep*, %dep** %p
  %120 = getelementptr %dep, %dep* %119, i32 0, i32 2
  %121 = load %dep*, %dep** %120
  store %dep* %121, %dep** %cur
  br label %for.cond42

for.cond42:                                       ; preds = %for.end44, %for.init41
  %122 = load %dep*, %dep** %cur
  %123 = ptrtoint %dep* %122 to i64
  %124 = sub i64 %123, 0
  %125 = sdiv exact i64 %124, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %126 = icmp ne i64 %125, 0
  br i1 %126, label %for.loop43, label %for.out45

for.loop43:                                       ; preds = %for.cond42
  br label %if.cond46

for.end44:                                        ; preds = %if.out49
  br label %for.cond42

for.out45:                                        ; preds = %if.then47, %for.cond42
  br label %for.end39

if.cond46:                                        ; preds = %for.loop43
  %127 = load %dep*, %dep** %cur
  %128 = getelementptr %dep, %dep* %127, i32 0, i32 0
  %129 = getelementptr [10 x i8], [10 x i8]* %128, i32 0, i32 0
  %130 = load i32, i32* %i
  %131 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %130
  %132 = getelementptr [10 x i8], [10 x i8]* %131, i64 0, i64 0
  %133 = call i32 @strcmp(i8* %129, i8* %132)
  %134 = zext i32 %133 to i64
  %135 = icmp eq i64 %134, 0
  br i1 %135, label %if.then47, label %if.else48

if.then47:                                        ; preds = %if.cond46
  %136 = load %dep*, %dep** %prev
  %137 = getelementptr %dep, %dep* %136, i32 0, i32 2
  %138 = load %dep*, %dep** %cur
  %139 = getelementptr %dep, %dep* %138, i32 0, i32 2
  %140 = load %dep*, %dep** %139
  store %dep* %140, %dep** %137
  %141 = load %dep*, %dep** %cur
  store %dep* %141, %dep** %tmp
  %142 = load %dep*, %dep** %cur
  %143 = getelementptr %dep, %dep* %142, i32 0, i32 2
  %144 = load %dep*, %dep** %143
  store %dep* %144, %dep** %cur
  %145 = load %dep*, %dep** %tmp
  %146 = bitcast %dep* %145 to i8*
  call void @free(i8* %146)
  br label %for.out45

if.else48:                                        ; preds = %if.cond46
  %147 = load %dep*, %dep** %cur
  store %dep* %147, %dep** %prev
  %148 = load %dep*, %dep** %cur
  %149 = getelementptr %dep, %dep* %148, i32 0, i32 2
  %150 = load %dep*, %dep** %149
  store %dep* %150, %dep** %cur
  br label %if.out49

if.out49:                                         ; preds = %if.else48
  br label %for.end44

for.init50:                                       ; preds = %for.out22
  store i32 0, i32* %i
  br label %for.cond51

for.cond51:                                       ; preds = %for.end53, %for.init50
  %151 = load i32, i32* %cnt
  %152 = load i32, i32* %i
  %153 = icmp slt i32 %152, %151
  br i1 %153, label %for.loop52, label %for.out54

for.loop52:                                       ; preds = %for.cond51
  br label %if.cond55

for.end53:                                        ; preds = %if.out58
  %154 = load i32, i32* %i
  %155 = add i32 %154, 1
  store i32 %155, i32* %i
  br label %for.cond51

for.out54:                                        ; preds = %for.cond51
  br label %if.out17

if.cond55:                                        ; preds = %for.loop52
  %156 = load i32, i32* %i
  %157 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %156
  %158 = load i8, i8* %157
  %159 = zext i8 %158 to i64
  %160 = icmp eq i64 %159, 0
  %161 = load i32, i32* %i
  %162 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %161
  %163 = load i8, i8* %162
  %164 = icmp eq i8 %163, 70
  %165 = zext i1 %164 to i64
  %166 = icmp ne i64 %165, 0
  %167 = zext i1 %160 to i64
  %168 = icmp ne i64 %167, 0
  %169 = or i1 %168, %166
  br i1 %169, label %if.then56, label %if.else57

if.then56:                                        ; preds = %if.cond55
  br label %if.cond59

if.else57:                                        ; preds = %if.cond55
  br label %if.out58

if.out58:                                         ; preds = %if.else57, %if.out62
  br label %for.end53

if.cond59:                                        ; preds = %if.then56
  %170 = load i32, i32* %i
  %171 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %170
  %172 = load %dep*, %dep** %171
  %173 = ptrtoint %dep* %172 to i64
  %174 = sub i64 %173, 0
  %175 = sdiv exact i64 %174, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %176 = icmp eq i64 %175, 0
  br i1 %176, label %if.then60, label %if.else61

if.then60:                                        ; preds = %if.cond59
  %177 = load i32, i32* %i
  %178 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %177
  %179 = getelementptr [10 x i8], [10 x i8]* %178, i64 0, i64 0
  %180 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), i8* %179)
  br label %if.out62

if.else61:                                        ; preds = %if.cond59
  br label %for.init63

if.out62:                                         ; preds = %for.out67, %if.then60
  br label %if.out58

for.init63:                                       ; preds = %if.else61
  %181 = load i32, i32* %i
  %182 = getelementptr [100 x %dep*], [100 x %dep*]* @dependency, i32 0, i32 %181
  %183 = load %dep*, %dep** %182
  %184 = getelementptr %dep, %dep* %183, i32 0, i32 1
  %185 = load %dep*, %dep** %184
  store %dep* %185, %dep** %p
  br label %for.cond64

for.cond64:                                       ; preds = %for.end66, %for.init63
  %186 = load %dep*, %dep** %p
  %187 = ptrtoint %dep* %186 to i64
  %188 = sub i64 %187, 0
  %189 = sdiv exact i64 %188, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %190 = icmp ne i64 %189, 0
  br i1 %190, label %for.loop65, label %for.out67

for.loop65:                                       ; preds = %for.cond64
  br label %if.cond68

for.end66:                                        ; preds = %if.out71
  %191 = load %dep*, %dep** %p
  %192 = getelementptr %dep, %dep* %191, i32 0, i32 1
  %193 = load %dep*, %dep** %192
  store %dep* %193, %dep** %p
  br label %for.cond64

for.out67:                                        ; preds = %if.then69, %for.cond64
  br label %if.out62

if.cond68:                                        ; preds = %for.loop65
  %194 = load %dep*, %dep** %p
  %195 = getelementptr %dep, %dep* %194, i32 0, i32 2
  %196 = load %dep*, %dep** %195
  %197 = ptrtoint %dep* %196 to i64
  %198 = sub i64 %197, 0
  %199 = sdiv exact i64 %198, ptrtoint (%dep* getelementptr (%dep, %dep* null, i32 1) to i64)
  %200 = icmp eq i64 %199, 0
  br i1 %200, label %if.then69, label %if.else70

if.then69:                                        ; preds = %if.cond68
  %201 = load i32, i32* %i
  %202 = getelementptr [100 x [10 x i8]], [100 x [10 x i8]]* @name, i32 0, i32 %201
  %203 = getelementptr [10 x i8], [10 x i8]* %202, i64 0, i64 0
  %204 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%s\0A", i32 0, i32 0), i8* %203)
  br label %for.out67

if.else70:                                        ; preds = %if.cond68
  br label %if.out71

if.out71:                                         ; preds = %if.else70
  br label %for.end66
}

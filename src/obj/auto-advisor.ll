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

for.end:                                          ; preds = %if.out6
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
  br label %if.out

if.else:                                          ; preds = %if.cond
  br label %if.out

if.out:                                           ; preds = %if.else, %if.then
  br label %if.cond3

if.cond3:                                         ; preds = %if.out
  %31 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %32 = load i8*, i8** %31
  %33 = getelementptr i8, i8* %32, i64 0
  %34 = load i8, i8* %33
  %35 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %36 = load i8*, i8** %35
  %37 = getelementptr i8, i8* %36, i64 0
  %38 = load i8, i8* %37
  %39 = icmp ne i8 %38, 10
  %40 = zext i1 %39 to i64
  %41 = icmp ne i64 %40, 0
  %42 = zext i8 %34 to i64
  %43 = icmp ne i64 %42, 0
  %44 = and i1 %43, %41
  br i1 %44, label %if.then4, label %if.else5

if.then4:                                         ; preds = %if.cond3
  %45 = load i32, i32* %i
  %46 = getelementptr [100 x i8], [100 x i8]* @grade, i32 0, i32 %45
  %47 = getelementptr [100 x i8*], [100 x i8*]* %vec, i64 0, i64 3
  %48 = load i8*, i8** %47
  %49 = getelementptr i8, i8* %48, i64 0
  %50 = load i8, i8* %49
  store i8 %50, i8* %46
  br label %if.out6

if.else5:                                         ; preds = %if.cond3
  br label %if.out6

if.out6:                                          ; preds = %if.else5, %if.then4
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
  %17 = load i32, i32* %i
  call void @dump(i32 %17)
  br label %for.end4

for.end4:                                         ; preds = %for.loop3
  %18 = load i32, i32* %i
  %19 = add i32 %18, 1
  store i32 %19, i32* %i
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  ret i32 0
}

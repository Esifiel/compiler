; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@"%d" = private constant [3 x i8] c"%d\00"
@"%d\0A" = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @puts(i8*)

define void @quicksort(i32* %A, i32 %len) {
entry:
  %A1 = alloca i32*
  store i32* %A, i32** %A1
  %len2 = alloca i32
  store i32 %len, i32* %len2
  %i = alloca i32
  %j = alloca i32
  %pivot = alloca i32
  %temp = alloca i32
  br label %if.cond

if.cond:                                          ; preds = %entry
  %0 = load i32, i32* %len2
  %1 = zext i32 %0 to i64
  %2 = icmp slt i64 %1, 2
  br i1 %2, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  ret void

if.else:                                          ; preds = %if.cond
  br label %if.out

if.out:                                           ; preds = %if.else
  %3 = load i32*, i32** %A1
  %4 = load i32, i32* %len2
  %5 = zext i32 %4 to i64
  %6 = sdiv i64 %5, 2
  %7 = getelementptr i32, i32* %3, i64 %6
  %8 = load i32, i32* %7
  store i32 %8, i32* %pivot
  br label %for.init

for.init:                                         ; preds = %if.out
  store i32 0, i32* %i
  %9 = load i32, i32* %len2
  %10 = zext i32 %9 to i64
  %11 = sub i64 %10, 1
  %12 = trunc i64 %11 to i32
  store i32 %12, i32* %j
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  br label %for.loop

for.loop:                                         ; preds = %for.cond
  br label %while.cond

for.end:                                          ; preds = %if.out9
  %13 = load i32, i32* %i
  %14 = add i32 %13, 1
  store i32 %14, i32* %i
  %15 = load i32, i32* %j
  %16 = sub i32 %15, 1
  store i32 %16, i32* %j
  br label %for.cond

for.out:                                          ; preds = %if.then7
  %17 = load i32*, i32** %A1
  %18 = load i32, i32* %i
  call void @quicksort(i32* %17, i32 %18)
  %19 = load i32*, i32** %A1
  %20 = load i32, i32* %i
  %21 = getelementptr i32, i32* %19, i32 %20
  %22 = load i32, i32* %i
  %23 = load i32, i32* %len2
  %24 = sub i32 %23, %22
  call void @quicksort(i32* %21, i32 %24)
  ret void

while.cond:                                       ; preds = %while.loop, %for.loop
  %25 = load i32, i32* %pivot
  %26 = load i32*, i32** %A1
  %27 = load i32, i32* %i
  %28 = getelementptr i32, i32* %26, i32 %27
  %29 = load i32, i32* %28
  %30 = icmp slt i32 %29, %25
  br i1 %30, label %while.loop, label %while.out

while.loop:                                       ; preds = %while.cond
  %31 = load i32, i32* %i
  %32 = add i32 %31, 1
  store i32 %32, i32* %i
  br label %while.cond

while.out:                                        ; preds = %while.cond
  br label %while.cond3

while.cond3:                                      ; preds = %while.loop4, %while.out
  %33 = load i32, i32* %pivot
  %34 = load i32*, i32** %A1
  %35 = load i32, i32* %j
  %36 = getelementptr i32, i32* %34, i32 %35
  %37 = load i32, i32* %36
  %38 = icmp sgt i32 %37, %33
  br i1 %38, label %while.loop4, label %while.out5

while.loop4:                                      ; preds = %while.cond3
  %39 = load i32, i32* %j
  %40 = sub i32 %39, 1
  store i32 %40, i32* %j
  br label %while.cond3

while.out5:                                       ; preds = %while.cond3
  br label %if.cond6

if.cond6:                                         ; preds = %while.out5
  %41 = load i32, i32* %j
  %42 = load i32, i32* %i
  %43 = icmp sge i32 %42, %41
  br i1 %43, label %if.then7, label %if.else8

if.then7:                                         ; preds = %if.cond6
  br label %for.out

if.else8:                                         ; preds = %if.cond6
  br label %if.out9

if.out9:                                          ; preds = %if.else8
  %44 = load i32*, i32** %A1
  %45 = load i32, i32* %i
  %46 = getelementptr i32, i32* %44, i32 %45
  %47 = load i32, i32* %46
  store i32 %47, i32* %temp
  %48 = load i32*, i32** %A1
  %49 = load i32, i32* %i
  %50 = getelementptr i32, i32* %48, i32 %49
  %51 = load i32*, i32** %A1
  %52 = load i32, i32* %j
  %53 = getelementptr i32, i32* %51, i32 %52
  %54 = load i32, i32* %53
  store i32 %54, i32* %50
  %55 = load i32*, i32** %A1
  %56 = load i32, i32* %j
  %57 = getelementptr i32, i32* %55, i32 %56
  %58 = load i32, i32* %temp
  store i32 %58, i32* %57
  br label %for.end
}

define i32 @main() {
entry:
  %A = alloca [10010 x i32]
  %n = alloca i32
  %i = alloca i32
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @"%d", i32 0, i32 0), i32* %n)
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %1 = load i32, i32* %n
  %2 = load i32, i32* %i
  %3 = icmp slt i32 %2, %1
  br i1 %3, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  %4 = load i32, i32* %i
  %5 = getelementptr [10010 x i32], [10010 x i32]* %A, i32 0, i32 %4
  %6 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @"%d", i32 0, i32 0), i32* %5)
  br label %for.end

for.end:                                          ; preds = %for.loop
  %7 = load i32, i32* %i
  %8 = add i32 %7, 1
  store i32 %8, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  %9 = getelementptr [10010 x i32], [10010 x i32]* %A, i64 0, i64 0
  %10 = load i32, i32* %n
  call void @quicksort(i32* %9, i32 %10)
  br label %for.init1

for.init1:                                        ; preds = %for.out
  store i32 0, i32* %i
  br label %for.cond2

for.cond2:                                        ; preds = %for.end4, %for.init1
  %11 = load i32, i32* %n
  %12 = load i32, i32* %i
  %13 = icmp slt i32 %12, %11
  br i1 %13, label %for.loop3, label %for.out5

for.loop3:                                        ; preds = %for.cond2
  %14 = load i32, i32* %i
  %15 = getelementptr [10010 x i32], [10010 x i32]* %A, i32 0, i32 %14
  %16 = load i32, i32* %15
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%d\0A", i32 0, i32 0), i32 %16)
  br label %for.end4

for.end4:                                         ; preds = %for.loop3
  %18 = load i32, i32* %i
  %19 = add i32 %18, 1
  store i32 %19, i32* %i
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  ret i32 0
}

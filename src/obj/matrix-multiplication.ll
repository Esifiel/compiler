; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@a = private global [30 x [40 x i32]] zeroinitializer
@b = private global [30 x [40 x i32]] zeroinitializer
@c = private global [30 x [40 x i32]] zeroinitializer
@"%d %d" = private constant [6 x i8] c"%d %d\00"
@"%d" = private constant [3 x i8] c"%d\00"
@"Incompatible Dimensions" = private constant [24 x i8] c"Incompatible Dimensions\00"
@"%10d" = private constant [5 x i8] c"%10d\00"
@0 = private constant [1 x i8] zeroinitializer

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @puts(i8*)

define i32 @main() {
entry:
  %ma = alloca i32
  %na = alloca i32
  %mb = alloca i32
  %nb = alloca i32
  %i = alloca i32
  %j = alloca i32
  %k = alloca i32
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @"%d %d", i32 0, i32 0), i32* %ma, i32* %na)
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %1 = load i32, i32* %ma
  %2 = load i32, i32* %i
  %3 = icmp slt i32 %2, %1
  br i1 %3, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  br label %for.init1

for.end:                                          ; preds = %for.out5
  %4 = load i32, i32* %i
  %5 = add i32 %4, 1
  store i32 %5, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  %6 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @"%d %d", i32 0, i32 0), i32* %mb, i32* %nb)
  br label %for.init6

for.init1:                                        ; preds = %for.loop
  store i32 0, i32* %j
  br label %for.cond2

for.cond2:                                        ; preds = %for.end4, %for.init1
  %7 = load i32, i32* %na
  %8 = load i32, i32* %j
  %9 = icmp slt i32 %8, %7
  br i1 %9, label %for.loop3, label %for.out5

for.loop3:                                        ; preds = %for.cond2
  %10 = load i32, i32* %i
  %11 = getelementptr [30 x [40 x i32]], [30 x [40 x i32]]* @a, i32 0, i32 %10
  %12 = load i32, i32* %j
  %13 = getelementptr [40 x i32], [40 x i32]* %11, i32 0, i32 %12
  %14 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @"%d", i32 0, i32 0), i32* %13)
  br label %for.end4

for.end4:                                         ; preds = %for.loop3
  %15 = load i32, i32* %j
  %16 = add i32 %15, 1
  store i32 %16, i32* %j
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  br label %for.end

for.init6:                                        ; preds = %for.out
  store i32 0, i32* %i
  br label %for.cond7

for.cond7:                                        ; preds = %for.end9, %for.init6
  %17 = load i32, i32* %mb
  %18 = load i32, i32* %i
  %19 = icmp slt i32 %18, %17
  br i1 %19, label %for.loop8, label %for.out10

for.loop8:                                        ; preds = %for.cond7
  br label %for.init11

for.end9:                                         ; preds = %for.out15
  %20 = load i32, i32* %i
  %21 = add i32 %20, 1
  store i32 %21, i32* %i
  br label %for.cond7

for.out10:                                        ; preds = %for.cond7
  br label %if.cond

for.init11:                                       ; preds = %for.loop8
  store i32 0, i32* %j
  br label %for.cond12

for.cond12:                                       ; preds = %for.end14, %for.init11
  %22 = load i32, i32* %nb
  %23 = load i32, i32* %j
  %24 = icmp slt i32 %23, %22
  br i1 %24, label %for.loop13, label %for.out15

for.loop13:                                       ; preds = %for.cond12
  %25 = load i32, i32* %i
  %26 = getelementptr [30 x [40 x i32]], [30 x [40 x i32]]* @b, i32 0, i32 %25
  %27 = load i32, i32* %j
  %28 = getelementptr [40 x i32], [40 x i32]* %26, i32 0, i32 %27
  %29 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @"%d", i32 0, i32 0), i32* %28)
  br label %for.end14

for.end14:                                        ; preds = %for.loop13
  %30 = load i32, i32* %j
  %31 = add i32 %30, 1
  store i32 %31, i32* %j
  br label %for.cond12

for.out15:                                        ; preds = %for.cond12
  br label %for.end9

if.cond:                                          ; preds = %for.out10
  %32 = load i32, i32* %mb
  %33 = load i32, i32* %na
  %34 = icmp ne i32 %33, %32
  br i1 %34, label %if.then, label %if.else

if.then:                                          ; preds = %if.cond
  %35 = call i32 @puts(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"Incompatible Dimensions", i32 0, i32 0))
  br label %if.out

if.else:                                          ; preds = %if.cond
  br label %for.init16

if.out:                                           ; preds = %for.out20, %if.then
  br label %for.init26

for.init16:                                       ; preds = %if.else
  store i32 0, i32* %i
  br label %for.cond17

for.cond17:                                       ; preds = %for.end19, %for.init16
  %36 = load i32, i32* %ma
  %37 = load i32, i32* %i
  %38 = icmp slt i32 %37, %36
  br i1 %38, label %for.loop18, label %for.out20

for.loop18:                                       ; preds = %for.cond17
  br label %for.init21

for.end19:                                        ; preds = %for.out25
  %39 = load i32, i32* %i
  %40 = add i32 %39, 1
  store i32 %40, i32* %i
  br label %for.cond17

for.out20:                                        ; preds = %for.cond17
  br label %if.out

for.init21:                                       ; preds = %for.loop18
  store i32 0, i32* %j
  br label %for.cond22

for.cond22:                                       ; preds = %for.end24, %for.init21
  %41 = load i32, i32* %nb
  %42 = load i32, i32* %j
  %43 = icmp slt i32 %42, %41
  br i1 %43, label %for.loop23, label %for.out25

for.loop23:                                       ; preds = %for.cond22
  br label %for.end24

for.end24:                                        ; preds = %for.loop23
  %44 = load i32, i32* %j
  %45 = add i32 %44, 1
  store i32 %45, i32* %j
  br label %for.cond22

for.out25:                                        ; preds = %for.cond22
  br label %for.end19

for.init26:                                       ; preds = %if.out
  store i32 0, i32* %i
  br label %for.cond27

for.cond27:                                       ; preds = %for.end29, %for.init26
  %46 = load i32, i32* %ma
  %47 = load i32, i32* %i
  %48 = icmp slt i32 %47, %46
  br i1 %48, label %for.loop28, label %for.out30

for.loop28:                                       ; preds = %for.cond27
  br label %for.init31

for.end29:                                        ; preds = %for.out35
  %49 = load i32, i32* %i
  %50 = add i32 %49, 1
  store i32 %50, i32* %i
  br label %for.cond27

for.out30:                                        ; preds = %for.cond27
  ret i32 0

for.init31:                                       ; preds = %for.loop28
  store i32 0, i32* %j
  br label %for.cond32

for.cond32:                                       ; preds = %for.end34, %for.init31
  %51 = load i32, i32* %nb
  %52 = load i32, i32* %j
  %53 = icmp slt i32 %52, %51
  br i1 %53, label %for.loop33, label %for.out35

for.loop33:                                       ; preds = %for.cond32
  %54 = load i32, i32* %i
  %55 = getelementptr [30 x [40 x i32]], [30 x [40 x i32]]* @c, i32 0, i32 %54
  %56 = load i32, i32* %j
  %57 = getelementptr [40 x i32], [40 x i32]* %55, i32 0, i32 %56
  %58 = load i32, i32* %57
  %59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @"%10d", i32 0, i32 0), i32 %58)
  br label %for.end34

for.end34:                                        ; preds = %for.loop33
  %60 = load i32, i32* %j
  %61 = add i32 %60, 1
  store i32 %61, i32* %j
  br label %for.cond32

for.out35:                                        ; preds = %for.cond32
  %62 = call i32 @puts(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @0, i32 0, i32 0))
  br label %for.end29
}

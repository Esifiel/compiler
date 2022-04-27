; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@"%d\0A" = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i32 @main() {
entry:
  %sum = alloca i32
  %i = alloca i32
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.loop, %for.init
  %0 = load i32, i32* %i
  %1 = zext i32 %0 to i64
  %2 = icmp slt i64 %1, 100
  br i1 %2, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  %3 = load i32, i32* %sum
  %4 = load i32, i32* %i
  %5 = add i32 %3, %4
  store i32 %5, i32* %sum
  %6 = load i32, i32* %i
  %7 = add i32 %6, 1
  store i32 %7, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  %8 = load i32, i32* %sum
  %9 = zext i32 %8 to i64
  %10 = sub i64 %9, 1
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%d\0A", i32 0, i32 0), i64 %10)
  ret i32 0
}

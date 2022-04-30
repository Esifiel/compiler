; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@"%d" = private constant [3 x i8] c"%d\00"
@"%d\0A" = private constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define i32 @main() {
entry:
  %a = alloca [16 x i32]
  %i = alloca i32
  br label %for.init

for.init:                                         ; preds = %entry
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.end, %for.init
  %0 = load i32, i32* %i
  %1 = zext i32 %0 to i64
  %2 = icmp slt i64 %1, 16
  br i1 %2, label %for.loop, label %for.out

for.loop:                                         ; preds = %for.cond
  %3 = load i32, i32* %i
  %4 = getelementptr [16 x i32], [16 x i32]* %a, i32 0, i32 %3
  %5 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @"%d", i32 0, i32 0), i32* %4)
  br label %for.end

for.end:                                          ; preds = %for.loop
  %6 = load i32, i32* %i
  %7 = add i32 %6, 1
  store i32 %7, i32* %i
  br label %for.cond

for.out:                                          ; preds = %for.cond
  br label %for.init1

for.init1:                                        ; preds = %for.out
  store i32 0, i32* %i
  br label %for.cond2

for.cond2:                                        ; preds = %for.end4, %for.init1
  %8 = load i32, i32* %i
  %9 = zext i32 %8 to i64
  %10 = icmp slt i64 %9, 16
  br i1 %10, label %for.loop3, label %for.out5

for.loop3:                                        ; preds = %for.cond2
  %11 = load i32, i32* %i
  %12 = getelementptr [16 x i32], [16 x i32]* %a, i32 0, i32 %11
  %13 = load i32, i32* %12
  %14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%d\0A", i32 0, i32 0), i32 %13)
  br label %for.end4

for.end4:                                         ; preds = %for.loop3
  %15 = load i32, i32* %i
  %16 = add i32 %15, 1
  store i32 %16, i32* %i
  br label %for.cond2

for.out5:                                         ; preds = %for.cond2
  ret i32 0
}

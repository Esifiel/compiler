; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@a = private global i32 0

define void @quicksort() {
entry:
  %i = alloca i32
  %j = alloca i32
  ret void
}

define i32 @main() {
entry:
  %sum = alloca i32
  %i = alloca i32
  store i32 0, i32* %sum
  br label %forinit

forinit:                                          ; preds = %entry
  store i32 0, i32* %i
  br label %forcond

forcond:                                          ; preds = %forloop, %forinit
  %0 = load i32, i32* %i
  %1 = zext i32 %0 to i64
  %2 = icmp sle i64 %1, 100
  br i1 %2, label %forloop, label %forout

forloop:                                          ; preds = %forcond
  %3 = load i32, i32* %sum
  %4 = load i32, i32* %i
  %5 = add i32 %3, %4
  store i32 %5, i32* %sum
  %6 = load i32, i32* %i
  %7 = zext i32 %6 to i64
  %8 = add i64 %7, 1
  %9 = trunc i64 %8 to i32
  store i32 %9, i32* %i
  br label %forcond

forout:                                           ; preds = %forcond
  ret i32 0
}

;;startofbash
;filename="$1"
;rm -f output.o
;rm -f test_program
;cat "$filename"
;llc -filetype=obj "$filename" -o output.o
;ls
;clang output.o -o test_program -no-pie
;ls
;./test_program
;;endofbash
; ModuleID = 'MyModule'

source_filename = "MyModule"

@0 = private unnamed_addr constant [28 x i8] c"\1B[31mThis text is red!\1B[0m\0A\00", align 1

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @0, i32 0, i32 0))
  ret i32 0
}

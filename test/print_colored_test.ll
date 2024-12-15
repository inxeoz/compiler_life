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

; ModuleID = 'color_printing.ll'
source_filename = "color_printing.ll"

@fmt = private constant [30 x i8] c"\033[31mThis text is red!\033[0m\0A\00", align 1

declare i32 @printf(i8*, ...) #1

define i32 @main() {
entry:
  ; Get the pointer to the formatted string
  %str = getelementptr inbounds [30 x i8], [30 x i8]* @fmt, i32 0, i32 0

  ; Call printf to print the formatted string (red text)
  call i32 (i8*, ...) @printf(i8* %str)

  ret i32 0
}

attributes #1 = { noinline nounwind }

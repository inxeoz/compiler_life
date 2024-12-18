;;startofbash
;rm -f output.o
;rm -f test_program
;cat test.ll
;llc -filetype=obj test.ll -o output.o
;ls
;clang output.o -o test_program -no-pie
;ls
;./test_program
;;endofbash



; ModuleID = 'hello'
source_filename = "hello.ll"

declare i32 @printf(i8*, ...)

@.str = private constant [6 x i8] c"hello\00"

define i32 @main() {
entry:
    %i = alloca i32, align 4
    store i32 0, i32* %i, align 4
    br label %loop

loop:
    %count = load i32, i32* %i, align 4
    %cmp = icmp slt i32 %count, 5
    br i1 %cmp, label %body, label %end

body:
    %print = call i32 (i8*, ...) @printf(i8* getelementptr ([6 x i8], [6 x i8]* @.str, i32 0, i32 0))
    %next = add i32 %count, 1
    store i32 %next, i32* %i, align 4
    br label %loop

end:
    ret i32 0
}
